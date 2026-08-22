#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compatibility.h"
#include "error.h"
#include "gc.h"
#include "macros.h"
#include "unity.h"

//Simulate calculator heap
static void *test_mem;
static void *test_mem_aligned;
static struct ErrorType e;

void setUp()
{
    //Allocate memory to simulate calculator memory
    test_mem=malloc(HEAP_SIZE+sizeof(uint32_t));
    uintptr_t mem_align=(uintptr_t)test_mem;

    //Align memory to unit32_t
    mem_align+=sizeof(uint32_t)-mem_align%sizeof(uint32_t);
    test_mem_aligned=(void *)mem_align;

    //Check that memory allocated correctly
    TEST_ASSERT_NOT_EQUAL(NULL,test_mem);

    //Fill memory with test value
    const int test_val=42;
    for (int i=0;i<HEAP_SIZE;i++)
        ((char *)test_mem_aligned)[i]=test_val;

    //Initialize error object
    error_reset(&e);
}

void tearDown()
{
    //Deallocate memory simulating calculator memory
    free(test_mem);
}

void test_gc_get_header()   //1
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error for ID out of range
    struct GC_Header *header=gc_get_header(GC_TABLE_ELEMENTS,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_ID_RANGE,e.code);
    error_reset(&e);
    
    //Assert no error for header for ID table
    header=gc_get_header(GC_TABLE_ID,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error for all other IDs since should be unassigned
    for (int i=1;i<GC_TABLE_ELEMENTS;i++)
    {
        header=gc_get_header(i,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_ID_UNASSIGNED,e.code);
        error_reset(&e);
    }

    //Assert correct pointers for allocated items
    const int test_count=GC_TABLE_ELEMENTS;
    for (int i=1;i<test_count;i++)
    {
        //Allocate test object
        int id=gc_alloc(i*GC_OBJ_ALIGN,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Assert all IDs in test range correct
        header=gc_next_header((struct GC_Header *)test_mem_aligned,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=1;j<test_count;j++)
        {
            if (j<=i)
            {
                //Assert header pointer is correct
                struct GC_Header *test_header=gc_get_header(j,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                TEST_ASSERT_EQUAL_PTR(header,test_header);
                header=(struct GC_Header *)((uintptr_t)header+(j+1)*GC_OBJ_ALIGN);
            }
            else
            {
                //Assert no object assigned
                struct GC_Header *test_header=gc_get_header(j,&e);
                TEST_ASSERT_EQUAL(GC_ERROR_ID_UNASSIGNED,e.code);
                error_reset(&e);
            }
        }
    }
}

void test_gc_next_header()  //2
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Alocate test objects
    const int test_objs=5;
    const int test_multiple=4;
    for (int i=1;i<=test_objs;i++)
    {
        int id=gc_alloc(i*test_multiple,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    //Test various types of heap corruption
    const int test_count=4;
    for (int test=0;test<test_count;test++)
    {
        for (int i=1;i<=test_objs;i++)
        {
            //Assert gc_next_header works with no heap corruption
            struct GC_Header *header=gc_get_header(1,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            for (int j=1;j<=test_objs;j++)
            {
                header=gc_next_header(header,&e);
            }
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            //Purposely corrupt heap
            struct GC_Header *test_header=gc_get_header(i,&e);
            uint32_t old_size=test_header->size;
            if (test==0) test_header->size=0;
            else if (test==1) test_header->size=-GC_OBJ_ALIGN;
            else if (test==2) test_header->size=HEAP_SIZE;
            else if (test==3) test_header->size++;

            //Assert error caught after purposely corrupting heap
            header=gc_get_header(1,&e);
            for (int j=1;j<=test_objs;j++)
            {
                header=gc_next_header(header,&e);
            }
            if (test==0) TEST_ASSERT_EQUAL(GC_ERROR_EMPTY_HEADER,e.code);
            else if (test==1) TEST_ASSERT_EQUAL(GC_ERROR_HEADER_SIZE,e.code);
            else if (test==2) TEST_ASSERT_EQUAL(GC_ERROR_HEADER_OVERFLOW,e.code);
            else if (test==2) TEST_ASSERT_EQUAL(GC_ERROR_OBJ_ALIGNMENT,e.code);
            error_reset(&e);

            //Undo heap corruption for next check
            test_header->size=old_size;
        }
    }
}

void test_gc_init()     //3
{
    //Assert heap size is multiple of alignment
    TEST_ASSERT_EQUAL(0,HEAP_SIZE%GC_OBJ_ALIGN);

    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert header for GC table of IDs is correct
    uint32_t table_size=gc_obj_size(sizeof(struct GC_Header *)*GC_TABLE_ELEMENTS);
    struct GC_Header *header=(struct GC_Header *)test_mem_aligned;
    TEST_ASSERT_EQUAL(table_size,header->size);
    TEST_ASSERT_FALSE(header->free);
    TEST_ASSERT_EQUAL(0,header->pid);
    TEST_ASSERT_EQUAL(0,header->lock_count);
    TEST_ASSERT_EQUAL(header,((struct GC_Header **)header->data)[0]);
    TEST_ASSERT_EACH_EQUAL_PTR(NULL,&((struct GC_Header **)header->data)[1],GC_TABLE_ELEMENTS-1);

    //Assert empty object marking end of heap is correct
    uint32_t marker_size=GC_OBJ_ALIGN;
    header=(struct GC_Header *)((uintptr_t)test_mem_aligned+HEAP_SIZE-marker_size);
    TEST_ASSERT_EQUAL(marker_size,header->size);
    TEST_ASSERT_FALSE(header->free);
    TEST_ASSERT_EQUAL(0,header->pid);
    TEST_ASSERT_EQUAL(1,header->lock_count);

    //Assert memory ready to be allocated
    uint32_t free_size=HEAP_SIZE-table_size-marker_size;
    header=(struct GC_Header *)test_mem_aligned;
    header=gc_next_header(header,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(free_size,header->size);
    TEST_ASSERT_TRUE(header->free);
}

void test_gc_alloc()    //4
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Allocate 0 size object - not allowed
    int id=gc_alloc(0,&e);

    //Assert 0 size object allocation fails
    TEST_ASSERT_EQUAL(GC_ERROR_OBJ_SIZE,e.code);
    error_reset(&e);

    //Test object size alignment
    for (int i=1;i<8;i++)
    {
        //Allocate memory
        int id=gc_alloc(i,&e);
        struct GC_Header *header=gc_get_header(id,&e);

        //Assert no errors in allocation or fetching header
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Assert rounded up correctly
        if (i<=GC_OBJ_ALIGN-sizeof(struct GC_Header)) TEST_ASSERT_EQUAL(GC_OBJ_ALIGN,header->size);
        else TEST_ASSERT_EQUAL(2*GC_OBJ_ALIGN,header->size);

        //Assert ID assigned correctly
        TEST_ASSERT_EQUAL(i,id);
    }

    //TODO: expand ID table if necessary

    //TODO: test out of memory

    //TODO: test splitting blocks (requires free)
}

void test_gc_realloc()  //5
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error on object size 0
    {
        const uint32_t test_size=1000;
        uint32_t id=gc_alloc(test_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_realloc(id,0,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_OBJ_SIZE,e.code);
        error_reset(&e);
    }

    //Assert error if object locked
    {
        const uint32_t test_size=1000;
        uint32_t id=gc_alloc(test_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_lock(id,&e);
        gc_realloc(id,2*test_size,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_REALLOC_LOCKED,e.code);
        error_reset(&e);
    }

    //Assert no change in address if object size same
    {
        const uint32_t test_size=1000;
        uint32_t id=gc_alloc(test_size,&e);
        struct GC_Header *test1=gc_lock(id,&e);
        gc_unlock(id,&e);
        gc_realloc(id,test_size,&e);
        struct GC_Header *test2=gc_lock(id,&e);
        gc_unlock(id,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(test2,test1);
    }

    //Assert object split if new size is smaller
    {
        const int test_count=16;
        const int test_multiple=4;
        const int test_size=100;

        for (int i=1;i<=test_count;i++)
        {
            //Reinitialize GC
            gc_init(test_mem_aligned,HEAP_SIZE,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            
            //Create objects
            uint32_t test_id=gc_alloc(test_size,&e);
            uint32_t locked_id=gc_alloc(test_size,&e);
            gc_lock(locked_id,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            //Realloc
            uint32_t new_size=test_size-(i+1)*test_multiple;
            uint32_t new_obj_size=gc_obj_size(new_size);
            uint32_t old_obj_size=gc_obj_size(test_size);
            uint32_t free_size=old_obj_size-new_obj_size;
            if (free_size!=0)
            {
                gc_realloc(test_id,new_size,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

                //Check test object
                struct GC_Header *check_header=gc_get_header(test_id,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                TEST_ASSERT_FALSE(check_header->free);
                TEST_ASSERT_EQUAL(new_obj_size,check_header->size);
                //Free object
                check_header=gc_next_header(check_header,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                TEST_ASSERT_TRUE(check_header->free);
                TEST_ASSERT_EQUAL(free_size,check_header->size);
                //Locked object
                check_header=gc_next_header(check_header,&e);
                TEST_ASSERT_FALSE(check_header->free);
                TEST_ASSERT_EQUAL(1,check_header->lock_count);
                TEST_ASSERT_EQUAL(gc_obj_size(test_size),check_header->size);
            }
        }
    }

    //Assert expected addresses for reallocating with memory copying
    {
        //Reinitialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        const uint32_t test_size=0x100000;
        const uint32_t other_size=1000;
        uint32_t test_id=gc_alloc(test_size,&e);
        uint32_t locked_id1=gc_alloc(other_size,&e);
        uint32_t free_id=gc_alloc(other_size,&e);
        uint32_t locked_id2=gc_alloc(other_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_lock(locked_id1,&e);
        gc_free(free_id,&e);
        gc_lock(locked_id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        uint32_t new_size=test_size;

        //Check heap objects
        struct GC_Header *check_header=gc_next_header((struct GC_Header *)test_mem_aligned,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        //Unlocked object
        TEST_ASSERT_FALSE(check_header->free);
        TEST_ASSERT_EQUAL(0,check_header->lock_count);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),check_header->size);
        //Locked object
        check_header=gc_next_header(check_header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_FALSE(check_header->free);
        TEST_ASSERT_EQUAL(1,check_header->lock_count);
        TEST_ASSERT_EQUAL(gc_obj_size(other_size),check_header->size);
        //Free object
        check_header=gc_next_header(check_header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_TRUE(check_header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(other_size),check_header->size);
        //Locked object
        check_header=gc_next_header(check_header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_FALSE(check_header->free);
        TEST_ASSERT_EQUAL(1,check_header->lock_count);
        TEST_ASSERT_EQUAL(gc_obj_size(other_size),check_header->size);
        //Free object
        check_header=gc_next_header(check_header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_TRUE(check_header->free);

        //Check for heap corruption
        gc_check(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Write test data
        uint8_t c=1,step=0;
        uint32_t count=0;
        uint8_t *data=gc_lock(test_id,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++)
        {
            data[i]=(c+step);
            c++;
            if (c==0) step++;
        }
        gc_unlock(test_id,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Realloc and check heap
        const int size_diff=100;
        const int test_count=4;
        for (int i=0;i<test_count;i++)
        {
            //Reallocate
            new_size+=size_diff;
            gc_realloc(test_id,new_size,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            //Check heap objects
            check_header=gc_next_header((struct GC_Header *)test_mem_aligned,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            //Free object
            TEST_ASSERT_TRUE(check_header->free);
            TEST_ASSERT_EQUAL(0,check_header->lock_count);
            TEST_ASSERT_EQUAL(gc_obj_size(test_size),check_header->size);
            //Locked object
            check_header=gc_next_header(check_header,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_FALSE(check_header->free);
            TEST_ASSERT_EQUAL(1,check_header->lock_count);
            TEST_ASSERT_EQUAL(gc_obj_size(other_size),check_header->size);
            //Free object
            check_header=gc_next_header(check_header,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_TRUE(check_header->free);
            TEST_ASSERT_EQUAL(gc_obj_size(other_size),check_header->size);
            //Locked object
            check_header=gc_next_header(check_header,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_FALSE(check_header->free);
            TEST_ASSERT_EQUAL(1,check_header->lock_count);
            TEST_ASSERT_EQUAL(gc_obj_size(other_size),check_header->size);

            //Check free space left by realloced objects
            for (int j=0;j<i;j++)
            {
                check_header=gc_next_header(check_header,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                TEST_ASSERT_TRUE(check_header->free);
                TEST_ASSERT_EQUAL(gc_obj_size(test_size+(j+1)*size_diff),check_header->size);
            }

            //Check test object
            check_header=gc_next_header(check_header,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_FALSE(check_header->free);
            TEST_ASSERT_EQUAL(0,check_header->lock_count);
            TEST_ASSERT_EQUAL(gc_obj_size(test_size+(i+1)*size_diff),check_header->size);
        }
    }

    //Assert memory range sorted correctly for expanding reallocated object
    /*
    Before
    ======
    0. free     1K
    1. unlocked 2K
    2. free     2K
    3. unlocked 4K
    4. unlocked 5K
    5. test     500K
    6. unlocked 3K
    7. free     1K
    8. unlocked 2K
    9. locked 5.4M
    */
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Create objects
        const int test_sizes[]={1000,2000,2000,4000,5000,500000,3000,1000,2000,5400000};
        uint32_t test_ids[ARRAY_LEN(test_sizes)];
        for (int i=0;i<ARRAY_LEN(test_sizes);i++)
        {
            test_ids[i]=gc_alloc(test_sizes[i],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }

        gc_free(test_ids[0],&e);
        gc_free(test_ids[2],&e);
        gc_free(test_ids[7],&e);
        gc_lock(test_ids[9],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //TODO: remove
        ///*
        gc_debug(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        printf("\n");
        //*/

        printf("Before realloc\n");

        //Reallocate test object 1000 bytes larger
        gc_realloc(test_ids[5],501000,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        printf("After realloc\n");

        /*
        //Assert ID table updated correctly
        struct GC_Header *header=(struct GC_Header *)test_mem_aligned;
        struct TestType
        {
            uint32_t size;
            bool free;
            bool locked;
        } test_checks[]=
        {{},
        };

        //TODO: remove
        gc_debug(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        printf("\n");

        */

    }

    //Assert expanding reallocated object works correctly over many combinations
    {
        //TODO
    }
}

void test_gc_free()     //6
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert double free causes error
    const int obj_size=100;
    int id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_ID_UNASSIGNED,e.code);
    error_reset(&e);

    //Assert no error if freeing memory from same PID
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error if freeing from PID 0
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error if freeing from different PID
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(2,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);

    //Assert error if memory is locked
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_FREE_LOCKED,e.code);
    error_reset(&e);
    gc_unlock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
}

void test_gc_lock()     //7
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error if locking memory from same PID
    const int obj_size=100;
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    int id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error if locking from PID 0
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error if locking from different PID
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(2,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);
    
    //Assert no error on max number of locks
    id=gc_alloc(obj_size,&e);
    for (int i=0;i<GC_MAX_LOCKS;i++)
    {
        gc_lock(id,&e);    
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    //Assert error on exceeding max number of locks
    gc_lock(id,&e);    
    TEST_ASSERT_EQUAL(GC_ERROR_LOCK_COUNT,e.code);
    error_reset(&e);

    //Assert data copied to locked objects is correct
    char test_mem[obj_size];
    for (int i=0;i<obj_size;i++) test_mem[i]=i;         //Populate test memory
    const int test_count=5;
    uint32_t test_ids[test_count];
    for (int i=0;i<test_count;i++)
    {
        id=gc_alloc(obj_size,&e);                       //Allocate objects
        test_ids[i]=id;                                 //Save IDs for comparison below
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        void *data=gc_lock(id,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        memcpy(data,test_mem,obj_size);                 //Copy test data to allocated memory
        gc_unlock(id,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<obj_size;j++) test_mem[j]++;     //Modify test memory
    }
    for (int i=0;i<obj_size;i++) test_mem[i]=i;         //Repopulate test memory
    for (int i=0;i<test_count;i++)
    {
        char *data=gc_lock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<obj_size;j++)
        {
            TEST_ASSERT_EQUAL(test_mem[j],data[j]);     //Compare test memory to object
            test_mem[j]++;                              //Modify test memory for next test
        }
        gc_unlock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }
}

void test_gc_unlock()       //8
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error if unlocking memory from same PID
    const int obj_size=100;
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    int id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error if unlocking from PID 0
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error if unlocking from different PID
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(obj_size,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_lock(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(2,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);
    
    //Assert error on unlocking if already unlocked
    id=gc_alloc(obj_size,&e);
    gc_unlock(id,&e);    
    TEST_ASSERT_EQUAL(GC_ERROR_UNLOCK,e.code);
    error_reset(&e);
    gc_lock(id,&e);    
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);    
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_unlock(id,&e);    
    TEST_ASSERT_EQUAL(GC_ERROR_UNLOCK,e.code);
    error_reset(&e);
}

void test_gc_free_bytes()       //9
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    
    //Assert expected size of empty heap
    uint32_t expected_size=HEAP_SIZE-GC_OBJ_ALIGN-gc_obj_size(GC_TABLE_ELEMENTS*sizeof(struct GC_Header *));
    uint32_t size=gc_free_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);

    //Assert size after allocating
    const int test_count=100;
    uint32_t test_ids[test_count];
    for (int i=0;i<test_count;i++)
    {
        uint32_t obj_size=i+1;
        test_ids[i]=gc_alloc(obj_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size-=gc_obj_size(obj_size);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert size after locking
    for (int i=0;i<test_count;i++)
    {
        gc_lock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert size after unlocking
    for (int i=0;i<test_count;i++)
    {
        gc_unlock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert size after freeing
    for (int i=0;i<test_count;i++)
    {
        uint32_t obj_size=i+1;
        gc_free(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size+=gc_obj_size(obj_size);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }
}

void test_gc_allocated_bytes()  //10
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    
    //Assert expected size when heap is empty
    uint32_t expected_size=0;
    uint32_t size=gc_allocated_bytes(false,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);
    size=gc_allocated_bytes(true,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);

    //Allocate test objects
    const int tests[]={2,4,3};
    int test_sizes[ARRAY_LEN(tests)];
    uint32_t test_ids[9];
    uint32_t test_ids_index=0;
    const int test_multiple=4;
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        test_sizes[i]=test*gc_obj_size(test*test_multiple);
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<test;j++)
        {
            test_ids[test_ids_index]=gc_alloc(test*test_multiple,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            test_ids_index++;
        }
    }

    //Assert allocated bytes correct for all objects
    expected_size=0;
    for (int i=0;i<ARRAY_LEN(tests);i++)
        expected_size+=test_sizes[i];
    size=gc_allocated_bytes(false,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);

    //Assert allocated bytes correct for each object
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        expected_size=test_sizes[i];
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        size=gc_allocated_bytes(true,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
        size=gc_allocated_bytes(false,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_NOT_EQUAL(expected_size,size);
        error_reset(&e);
    }

    //Assert allocated bytes correct while freeing
    uint32_t total_size=0;
    for (int i=0;i<ARRAY_LEN(tests);i++)
        total_size+=test_sizes[i];
    test_ids_index=0;
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size=test_sizes[i];
        for (int j=0;j<test;j++)
        {
            uint32_t size=gc_allocated_bytes(true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_size,size);
            size=gc_allocated_bytes(false,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(total_size,size);

            gc_free(test_ids[test_ids_index],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            test_ids_index++;
            expected_size-=gc_obj_size(test*test_multiple);
            total_size-=gc_obj_size(test*test_multiple);

            size=gc_allocated_bytes(true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_size,size);
            size=gc_allocated_bytes(false,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(total_size,size);
        }
    }
}

void test_gc_locked_bytes()  //11
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    
    //Assert expected size when heap is empty
    uint32_t expected_size=0;
    uint32_t size=gc_locked_bytes(false,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);
    size=gc_locked_bytes(true,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);

    //Allocate test objects
    const int tests[]={2,4,3};
    int test_sizes[ARRAY_LEN(tests)];
    uint32_t test_ids[9];
    uint32_t test_ids_index=0;
    const int test_multiple=4;
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        test_sizes[i]=test*gc_obj_size(test*test_multiple);
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<test;j++)
        {
            test_ids[test_ids_index]=gc_alloc(test*test_multiple,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            test_ids_index++;
        }
    }

    //Assert no locked bytes for allocated objects yet
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        size=gc_locked_bytes(false,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(0,size);
    }
    size=gc_locked_bytes(true,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(0,size);

    //Assert byte count correct while locking
    uint32_t total_size=0;
    test_ids_index=0;
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size=0;
        for (int j=0;j<test;j++)
        {
            uint32_t size=gc_locked_bytes(true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_size,size);
            size=gc_locked_bytes(false,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(total_size,size);

            gc_lock(test_ids[test_ids_index],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            test_ids_index++;
            expected_size+=gc_obj_size(test*test_multiple);
            total_size+=gc_obj_size(test*test_multiple);

            size=gc_locked_bytes(true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_size,size);
            size=gc_locked_bytes(false,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(total_size,size);
        }
    }

    //Assert byte count correct while unlocking
    total_size=0;
    for (int i=0;i<ARRAY_LEN(tests);i++)
        total_size+=test_sizes[i];
    test_ids_index=0;
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size=test_sizes[i];
        for (int j=0;j<test;j++)
        {
            uint32_t size=gc_locked_bytes(true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_size,size);
            size=gc_locked_bytes(false,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(total_size,size);

            gc_unlock(test_ids[test_ids_index],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            test_ids_index++;
            expected_size-=gc_obj_size(test*test_multiple);
            total_size-=gc_obj_size(test*test_multiple);

            size=gc_locked_bytes(true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_size,size);
            size=gc_locked_bytes(false,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(total_size,size);
        }
    }
}

void test_gc_lost_bytes()  //12
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no bytes lost before allocating
    const int test_count=10;
    const int test_multiple=4;
    uint32_t test_ids[test_count];
    uint32_t size=gc_lost_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(0,size);

    //Assert no bytes lost while allocating
    for (int i=0;i<test_count;i++)
    {
        int obj_size=(i+1)*test_multiple;
        test_ids[i]=gc_alloc(obj_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        uint32_t size=gc_lost_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(0,size);
    }

    //Assert correct byte count lost while freeing
        //Stop before last object and test separately below
    int expected_size=0;
    for (int i=0;i<test_count-1;i++)
    {
        expected_size+=gc_obj_size((i+1)*test_multiple);
        gc_free(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        uint32_t size=gc_lost_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert no bytes lost after last object freed
    gc_free(test_ids[test_count-1],&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    size=gc_lost_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(0,size);

    //Assert no bytes lost while reallocating
    for (int i=0;i<test_count;i++)
    {
        int obj_size=(i+1)*test_multiple;
        test_ids[i]=gc_alloc(obj_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        uint32_t size=gc_lost_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(0,size);
    }

    //Assert correct byte count lost while freeing with pattern
        //Stop before last object and test separately below
    const int pattern[]={8,0,7,1,6,2,5,3,4};
    expected_size=0;
    for (int i=0;i<test_count-1;i++)
    {
        int index=pattern[i];
        expected_size+=gc_obj_size((index+1)*test_multiple);
        gc_free(test_ids[index],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        uint32_t size=gc_lost_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert no bytes lost after last object freed
    gc_free(test_ids[test_count-1],&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    size=gc_lost_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(0,size);

    //TODO: test after gc_compact is done
}

void test_gc_obj_count()  //13
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert 0 objects before allocating
    uint32_t size=gc_obj_count(false,true,true,true,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(1,size);

    //Allocate test objects
    enum
    {
        STATE_FREE,
        STATE_LOCKED,
        STATE_UNLOCKED
    };
    struct StateType
    {
        int free;
        int locked;
        int unlocked;
    };
    const int states[]={STATE_FREE,STATE_LOCKED,STATE_UNLOCKED};
    uint32_t state_index=0;
    const int states_per_pid=4;
    const int pid_count=3;
    struct StateType state_counts[pid_count];
    uint32_t test_ids[pid_count*states_per_pid];
    uint32_t test_ids_index=0;
    const int test_multiple=4;
    for (int j=0;j<pid_count;j++)
    {
        state_counts[j].free=0;
        state_counts[j].locked=0;
        state_counts[j].unlocked=0;
    }
    for (int i=0;i<pid_count;i++)
    {
        gc_set_pid(i,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<states_per_pid;j++)
        {
            //Make each object slightly larger to prevent memory reuse
                //so that number of free objects is predictable in test
            int obj_size=(i*5+j+1)*GC_OBJ_ALIGN;
            int id=gc_alloc(obj_size,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            int state=states[state_index];
            state_index=(state_index+1)%ARRAY_LEN(states);
            switch (state)
            {
                case STATE_FREE:
                    gc_free(id,&e);
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                    state_counts[i].free++;
                    break;
                case STATE_LOCKED:
                    gc_lock(id,&e);
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                    state_counts[i].locked++;
                    break;
                case STATE_UNLOCKED:
                    state_counts[i].unlocked++;
                    break;
            }
        }
    }

    //Assert counts for various combinations
    for (int i=0;i<16;i++)
    {
        bool pid_only=i&1;
        bool locked=i&2;
        bool unlocked=i&4;
        bool free=i&8;
        for (int j=0;j<pid_count;j++)
        {
            gc_set_pid(j,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            int expected_count=0;
            if (pid_only==false)
            {
                for (int k=0;k<pid_count;k++)
                {
                    if (locked) expected_count+=state_counts[k].locked;
                    if (unlocked) expected_count+=state_counts[k].unlocked;
                }
            }
            else
            {
                if (locked) expected_count+=state_counts[j].locked;
                if (unlocked) expected_count+=state_counts[j].unlocked;
            }
            for (int k=0;k<pid_count;k++)
            {
                if (free) expected_count+=state_counts[k].free;
            }
            //One extra object for unused memory at end of heap
            if (free) expected_count++;
            int count=gc_obj_count(pid_only,locked,unlocked,free,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            TEST_ASSERT_EQUAL(expected_count,count);
        }
    }
}

void test_gc_compact_fast()     //14
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert only one free object before allocating
    uint32_t count=gc_obj_count(false,false,false,true,&e);
    TEST_ASSERT_EQUAL(1,count);

    //Record free space for comparison later
    uint32_t free_space=gc_free_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert only one free object after allocating
    const int obj_count=3;
    const int obj_size=100;
    uint32_t test_ids[obj_count];
    for (int i=0;i<obj_count;i++)
    {
        test_ids[i]=gc_alloc(obj_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }
    count=gc_obj_count(false,false,false,true,&e);
    TEST_ASSERT_EQUAL(1,count);

    //Assert correct number of free objects after freeing
    for (int i=0;i<obj_count;i++)
    {
        gc_free(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }
    count=gc_obj_count(false,false,false,true,&e);
    TEST_ASSERT_EQUAL(obj_count+1,count);

    //Assert one free object after compacting
    gc_compact_fast(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    count=gc_obj_count(false,false,false,true,&e);
    TEST_ASSERT_EQUAL(1,count);

    //Assert same amount of free memory after compacting
    uint32_t new_free_space=gc_free_bytes(&e);
    TEST_ASSERT_EQUAL(free_space,new_free_space);

    //Assert memory compacts unlocked objects of same size - simple case
    {
        //Allocate memory
        const int obj_count=5;
        uint32_t test_ids[obj_count];
        for (int i=0;i<obj_count;i++)
        {
            test_ids[i]=gc_alloc((i+1)*32,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }

        //Create two holes
        gc_free(test_ids[1],&e);
        gc_free(test_ids[3],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Compact
        gc_compact_fast(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Assert one free object left after compacting
        uint32_t count=gc_obj_count(false,false,false,true,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(1,count);

        //Free remaining objects
        gc_free(test_ids[0],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        gc_free(test_ids[2],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        gc_free(test_ids[4],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Assert all memory recovered
        uint32_t allocated=gc_allocated_bytes(false,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(0,allocated);

        //Assert free objects not combined yet
        count=gc_obj_count(false,false,false,true,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(obj_count-2+1,count);

        //Assert compacting combines all free objects
        gc_compact_fast(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        count=gc_obj_count(false,false,false,true,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(1,count);
    }

    //Assert copying objects of different sizes into free slot
    {
        const int slot_size=100;
        const int locked_size=100;
        const int test_multiple=4;
        for (int i=72;i<=100;i+=test_multiple)
        {
            int slot_id=gc_alloc(slot_size,&e);
            int locked_id=gc_alloc(slot_size,&e);
            int moved_id=gc_alloc(i,&e);
            gc_lock(locked_id,&e);
            gc_free(slot_id,&e);
            gc_compact_fast(&e);
            gc_check(&e);
            int count=gc_obj_count(false,true,true,true,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            if (gc_obj_size(slot_size)>gc_obj_size(i))
            {
                //Small free object created in slot
                TEST_ASSERT_EQUAL(4,count);
                int size=gc_lost_bytes(&e);
                TEST_ASSERT_EQUAL(size,GC_OBJ_ALIGN);
            }
            else
            {
                //Not enough room for small free object
                    //Excess added to existing object
                TEST_ASSERT_EQUAL(3,count);
            }
            gc_unlock(locked_id,&e);
            gc_free(locked_id,&e);
            gc_free(moved_id,&e);
            gc_compact_fast(&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }
    }

    //Assert correct compaction of complicated pattern
    /*
        Before
        ======
        0 free        400
        1 unlocked    100
        2 free        600
        3 locked      200
        4 free        400
        5 free        300
        6 unlocked    1200
        7 unlocked    1000
        8 locked      900
        9 free        600
        10 locked     500
        11 unlocked   700
    */
    {
        const int sizes[]={400,100,600,200,400,300,1200,1000,900,600,500,700};
        int ids[ARRAY_LEN(sizes)];
        for (int i=0;i<ARRAY_LEN(ids);i++)
        {
            //Allocate
            ids[i]=gc_alloc(sizes[i],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            //Write test data
            uint8_t *data=gc_lock(ids[i],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            for (int j=0;j<sizes[i];j++)
                data[j]=j*ids[i];
            gc_unlock(ids[i],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }
        gc_free(ids[0],&e);
        gc_free(ids[2],&e);
        gc_lock(ids[3],&e);
        gc_free(ids[4],&e);
        gc_free(ids[5],&e);
        gc_lock(ids[8],&e);
        gc_free(ids[9],&e);
        gc_lock(ids[10],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        gc_compact_fast(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        enum
        {
            CHECK_FREE,
            CHECK_LOCKED,
            CHECK_UNLOCKED
        };
        struct CheckType
        {
            int size;
            int state;
        }checks[]={
            {112,   CHECK_UNLOCKED}, 
            {1024,  CHECK_UNLOCKED},
            {16,    CHECK_FREE},
            {224,   CHECK_LOCKED},
            {1216,  CHECK_UNLOCKED},
            {720,   CHECK_UNLOCKED},
            {1040,  CHECK_FREE},
            {912,   CHECK_LOCKED},
            {624,   CHECK_FREE},
            {512,   CHECK_LOCKED},
            };

        struct GC_Header *header=gc_next_header((struct GC_Header *)test_mem_aligned,&e);
        for (int i=0;i<ARRAY_LEN(checks);i++)
        {
            //Assert object matches expected
            TEST_ASSERT_EQUAL(checks[i].size,header->size);
            bool free=(checks[i].state==CHECK_FREE);
            TEST_ASSERT_EQUAL(free,header->free);
            if (checks[i].state==CHECK_LOCKED)
                TEST_ASSERT_EQUAL(1,header->lock_count);
            else if (checks[i].state==CHECK_UNLOCKED)
                TEST_ASSERT_EQUAL(0,header->lock_count);
            
            header=gc_next_header(header,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }

        //Assert object data correct
        const int test_ids[]={2,4,7,8,9,11,12};
        const int test_lens[]={100,200,1200,1000,900,500,700};
        for (int i=0;i<ARRAY_LEN(test_ids);i++)
        {
            int test=test_ids[i];
            uint8_t *data=gc_lock(test,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            for (int j=0;j<test_lens[i];j++)
            {
                uint8_t expected=j*test;
                TEST_ASSERT_EQUAL(expected,data[j]);
            }

            gc_unlock(test,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }
    }

    //Assert correct compaction with large number of objects
    {
        //TODO: increase obj_count
        //const int obj_count=10000;
        const int obj_count=100;
        const int obj_steps=10;
        const int obj_size=100;
        //const int steps=50000;
        const int steps=500;
        int test_index=0;
        enum
        {
            STATE_NEW1,
            STATE_NEW2,
            STATE_NEW3,
            STATE_FREE,
            STATE_LOCKED,
            STATE_UNLOCKED,
            STATE_COMPACT,

            STATE_COUNT
        };
        struct TestType
        {
            int id;
            int size;
            int state;
            uint8_t start;
            uint8_t step;
        }test_objs[obj_count];

        //Seed RNG to get same sequence every time
        srand(42);
        
        //Simulate lots of actions
        for (int i=0;i<steps;i++)
        {
            int action=rand()%STATE_COUNT;
            switch (action)
            {
                case STATE_NEW1:
                case STATE_NEW2:
                case STATE_NEW3:
                    if (test_index<obj_count)
                    {
                        int size=(rand()%obj_steps+1)*obj_size;
                        int id=gc_alloc(size,&e);
                        test_objs[test_index].id=id;
                        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                        test_objs[test_index].size=size;
                        test_objs[test_index].state=STATE_UNLOCKED;
                        test_objs[test_index].start=rand()%256;
                        test_objs[test_index].step=rand()%256;
                        uint8_t *data=gc_lock(id,&e);
                        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                        uint8_t value=test_objs[test_index].start;
                        for (int j=0;j<size;j++)
                        {
                            data[j]=value;
                            value+=test_objs[test_index].step;
                        }
                        gc_unlock(id,&e);
                        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                        test_index++;
                    }
                    break;
                case STATE_FREE:
                    if (test_index!=0)
                    {
                        int id=rand()%test_index;
                        if (test_objs[id].state==STATE_UNLOCKED)
                        {
                            gc_free(test_objs[id].id,&e);
                            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                            test_objs[id].state=STATE_FREE;
                        }
                    }
                    break;
                case STATE_LOCKED:
                    if (test_index!=0)
                    {
                        int id=rand()%test_index;
                        if (test_objs[id].state==STATE_UNLOCKED)
                        {
                            gc_lock(test_objs[id].id,&e);
                            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                            test_objs[id].state=STATE_LOCKED;
                        }
                    }
                    break;
                case STATE_UNLOCKED:
                    if (test_index!=0)
                    {
                        int id=rand()%test_index;
                        if (test_objs[id].state==STATE_LOCKED)
                        {
                            gc_unlock(test_objs[id].id,&e);
                            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                            test_objs[id].state=STATE_UNLOCKED;
                        }
                    }
                    break;
                case STATE_COMPACT:
                    gc_compact_fast(&e);
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                    break;
            }
        }

        //Assert no heap corruption
        gc_compact_fast(&e);
        gc_check(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //TODO: remove
        /*
        int count=gc_obj_count(false,true,true,true,&e);
        int bytes=gc_allocated_bytes(false,&e);
        int lost=gc_lost_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_debug(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        printf("Results: obj_count %d, allocated %d, lost %d\n",count,bytes,lost);
        */

        //Assert object data correct
        for (int i=0;i<test_index;i++)
        {
            if ((test_objs[i].state==STATE_LOCKED)||
                (test_objs[i].state==STATE_UNLOCKED))
            {
                uint8_t *data=gc_lock(test_objs[i].id,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                uint8_t value=test_objs[i].start;
                for (int j=0;j<test_objs[i].size;j++)
                {
                    TEST_ASSERT_EQUAL(value,data[j]);
                    value+=test_objs[i].step;
                }
                gc_unlock(test_objs[i].id,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            }
        }
    }
}

void test_gc_check()        //15
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error when heap is empty
    gc_check(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error while allocating
    const int test_count=100;
    const int test_multiple=4;
    uint32_t test_ids[test_count];
    for (int i=0;i<test_count;i++)
    {
        test_ids[i]=gc_alloc((i+1)*test_multiple,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_check(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    //Assert no error while locking
    for (int i=0;i<test_count;i++)
    {
        gc_lock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_check(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    //Assert no error while unlocking
    for (int i=0;i<test_count;i++)
    {
        gc_unlock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_check(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    //Assert no error while freeing
    for (int i=0;i<test_count;i++)
    {
        gc_free(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_check(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }
}

void test_gc_swap_next()     //16
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    
    //Assert error on swapping last and next to last objects
    {
        struct GC_Header *header=(struct GC_Header *)test_mem_aligned;
        //Free object
        header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_TRUE(header->free);
        //Swap
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SWAP_END,e.code);
        error_reset(&e);
        //End object
        header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_TRUE(header->end);
        //Swap
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SWAP_END,e.code);
        error_reset(&e);
    }
    
    //Assert error on one or both objects locked
    {
        const int test_size=1000;
        uint32_t id1=gc_alloc(test_size,&e);
        uint32_t id2=gc_alloc(test_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //id1 locked
        gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        struct GC_Header *header=gc_get_header(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SWAP_LOCKED,e.code);
        error_reset(&e);
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //id2 locked
        gc_lock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        header=gc_get_header(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SWAP_LOCKED,e.code);
        error_reset(&e);
        gc_unlock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Both locked
        gc_lock(id1,&e);
        gc_lock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        header=gc_get_header(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SWAP_LOCKED,e.code);
        error_reset(&e);
        gc_unlock(id1,&e);
        gc_unlock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Both unlocked
        header=gc_get_header(id1,&e);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    printf("***swap unlocked objects\n");

    //Assert unlocked objects swapped correctly
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Create objects
        const int test_size=1000;
        uint32_t id1=gc_alloc(test_size,&e);
        uint32_t id2=gc_alloc(2*test_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Write data to objects
        uint8_t *data1=gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) data1[i]=i*2;
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        uint8_t *data2=gc_lock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size*2;i++) data2[i]=i*3;
        gc_unlock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Verify object headers
        struct GC_Header *obj1=gc_get_header(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        uint32_t obj1_size=obj1->size;
        struct GC_Header *obj2=gc_get_header(id2,&e);
        uint32_t obj2_size=obj2->size;
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        struct GC_Header *obj2_check=gc_next_header(obj1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(obj2,obj2_check);

        //Swap
        struct GC_Header *header=gc_get_header(id1,&e);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Reverify object headers
        struct GC_Header *new_obj2=gc_get_header(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(new_obj2,obj1);     
        TEST_ASSERT_EQUAL(new_obj2,header);
        uint32_t new_obj2_size=new_obj2->size;
        TEST_ASSERT_EQUAL(obj2_size,new_obj2_size);
        struct GC_Header *new_obj1=gc_get_header(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(new_obj1,(struct GC_Header *)(((uintptr_t)new_obj2)+new_obj2_size));
        uint32_t new_obj1_size=new_obj1->size;
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(obj1_size,new_obj1_size);
        struct GC_Header *new_obj1_check=gc_next_header(new_obj2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(new_obj1,new_obj1_check);

        //Check first object (id2)
        TEST_ASSERT_FALSE(header->free);
        TEST_ASSERT_EQUAL(id2,header->id);
        TEST_ASSERT_EQUAL(gc_obj_size(2*test_size),header->size);

        //Check second object (id1)
        header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_FALSE(header->free);
        TEST_ASSERT_EQUAL(id1,header->id);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),header->size);

        //Check data
        uint8_t *check1=gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(header->data,check1);
        for (int i=0;i<test_size;i++) 
            TEST_ASSERT_EQUAL_UINT8(i*2,check1[i]);
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        uint8_t *check2=gc_lock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) 
            TEST_ASSERT_EQUAL_UINT8(i*3,check2[i]);
        gc_unlock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Reswap
        header=gc_get_header(id2,&e);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Check first object (id1)
        TEST_ASSERT_FALSE(header->free);
        TEST_ASSERT_EQUAL(id1,header->id);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),header->size);

        //Check second object (id2)
        header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_FALSE(header->free);
        TEST_ASSERT_EQUAL(id2,header->id);
        TEST_ASSERT_EQUAL(gc_obj_size(2*test_size),header->size);

        //Check data
        check1=gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) 
            TEST_ASSERT_EQUAL_UINT8(i*2,check1[i]);
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        check2=gc_lock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) 
            TEST_ASSERT_EQUAL_UINT8(i*3,check2[i]);
        gc_unlock(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    printf("***swap one unlocked object\n");

    //Assert one unlocked and one free object swapped correctly
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Create objects
        const int test_size=1000;
        uint32_t id1=gc_alloc(test_size,&e);
        uint32_t id2=gc_alloc(2*test_size,&e);
        uint32_t id3=gc_alloc(test_size,&e);
        gc_free(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Write data to object
        uint8_t *data1=gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) data1[i]=i*2;
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Swap
        struct GC_Header *header=gc_get_header(id1,&e);
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Check first object (id2)
        TEST_ASSERT_TRUE(header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(2*test_size),header->size);

        //Check second object (id1)
        struct GC_Header *next_header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_FALSE(next_header->free);
        TEST_ASSERT_EQUAL(id1,next_header->id);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),next_header->size);

        //Check data
        uint8_t *check1=gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) 
            TEST_ASSERT_EQUAL_UINT8(i*2,check1[i]);
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Reswap
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Check first object (id1)
        TEST_ASSERT_FALSE(header->free);
        TEST_ASSERT_EQUAL(id1,header->id);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),header->size);

        //Check second object (id2)
        next_header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_TRUE(next_header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(2*test_size),next_header->size);

        //Check data
        check1=gc_lock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int i=0;i<test_size;i++) 
            TEST_ASSERT_EQUAL_UINT8(i*2,check1[i]);
        gc_unlock(id1,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    printf("***swap free objects\n");

    //Assert free objects swapped correctly
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Create objects
        const int test_size=1000;
        uint32_t id1=gc_alloc(test_size,&e);
        uint32_t id2=gc_alloc(2*test_size,&e);
        struct GC_Header *header=gc_get_header(id1,&e);
        gc_free(id1,&e);
        gc_free(id2,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Swap
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Check first object (id2)
        TEST_ASSERT_TRUE(header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(2*test_size),header->size);

        //Check second object (id1)
        struct GC_Header *next_header=gc_next_header(header,&e);
        TEST_ASSERT_TRUE(next_header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),next_header->size);

        //Reswap
        gc_swap_next(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        
        //Check first object (id1)
        TEST_ASSERT_TRUE(header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(test_size),header->size);

        //Check second object (id2)
        header=gc_next_header(header,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_TRUE(header->free);
        TEST_ASSERT_EQUAL(gc_obj_size(2*test_size),header->size);
    }

}

void test_gc_sort_id_list()             //17
{
    //Assert no errors creating and sorting various types of lists
    {
        enum
        {
            TEST_UNLOCKED,
            TEST_LOCKED,
        };
        const int test_len=5;
        const uint32_t tests[][5]={
            {100,200,300,400,500},
            {500,400,300,200,100},
            {200,200,200,200,200},
            {500,200,200,200,200},
            {200,200,200,200,500},
            {100,300,500,200,400},
            {200,400,100,300,500}
            };
        const uint32_t test_checks[][5]={
            {100,200,300,400,500},
            {100,200,300,400,500},
            {200,200,200,200,200},
            {200,200,200,200,500},
            {200,200,200,200,500},
            {100,200,300,400,500},
            {100,200,300,400,500},
            };
        const int test_status[][5]={
            {TEST_UNLOCKED,TEST_UNLOCKED,TEST_UNLOCKED,TEST_UNLOCKED,TEST_UNLOCKED},    //All unlocked
            {TEST_LOCKED,TEST_LOCKED,TEST_LOCKED,TEST_LOCKED,TEST_LOCKED},              //All locked
            {TEST_LOCKED,TEST_UNLOCKED,TEST_LOCKED,TEST_UNLOCKED,TEST_LOCKED},          //Locked and unlocked
            {TEST_UNLOCKED,TEST_LOCKED,TEST_UNLOCKED,TEST_LOCKED,TEST_UNLOCKED},        //Locked and unlocked
            };
        uint32_t obj_ids[test_len];
        for (int i=0;i<ARRAY_LEN(tests);i++)
        {
            for (int test=0;test<ARRAY_LEN(test_status);test++)
            {
                //Initialize GC
                gc_init(test_mem_aligned,HEAP_SIZE,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

                //Assert heap is empty
                TEST_ASSERT_EQUAL(0,gc_obj_count(false,true,true,false,&e));     //No unlocked or locked objects
                TEST_ASSERT_EQUAL(1,gc_obj_count(false,true,true,true,&e));     //Only one free object
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

                //Create objects
                for (int j=0;j<ARRAY_LEN(tests[i]);j++)
                {
                    uint32_t size=tests[i][j];
                    obj_ids[j]=gc_alloc(size,&e);
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                }

                //Assert heap contains correct object counts
                TEST_ASSERT_EQUAL(0,gc_obj_count(false,true,false,false,&e));   //No locked objects
                TEST_ASSERT_EQUAL(test_len,gc_obj_count(false,false,true,false,&e));   //Five unlocked objects
                TEST_ASSERT_EQUAL(1,gc_obj_count(false,false,false,true,&e));   //One free object
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

                //Assert objects are correct size
                struct GC_Header *header;
                for (int j=0;j<ARRAY_LEN(tests[i]);j++)
                {
                    uint32_t size=tests[i][j];
                    uint32_t predicted_size=gc_obj_size(size);
                    header=gc_get_header(obj_ids[j],&e);
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                    uint32_t actual_size=header->size;
                    TEST_ASSERT_EQUAL(predicted_size,actual_size);
                }

                //Apply lock according to pattern
                for (int j=0;j<ARRAY_LEN(tests[i]);j++)
                {
                    int test_action=test_status[test][j];
                    if (test_action==TEST_UNLOCKED)
                    {
                        //Nothing to do
                    }
                    else if (test_action==TEST_LOCKED)
                    {
                        //Lock
                        gc_lock(obj_ids[j],&e);
                    }
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                }

                //Sort list
                gc_sort_id_list(obj_ids,test_len,&e);
                TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

                //Assert list sorted correctly
                for (int j=0;j<ARRAY_LEN(test_checks[i]);j++)
                {
                    uint32_t obj_id=obj_ids[j];
                    header=gc_get_header(obj_id,&e);
                    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
                    uint32_t expected_size=test_checks[i][j];
                    TEST_ASSERT_EQUAL(gc_obj_size(expected_size),header->size);
                }
            }
        }
    }

    //Assert error on empty list
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        gc_sort_id_list(NULL,0,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SORT_EMPTY,e.code);
        error_reset(&e);
    }

    //Assert free objects in list caught as ID_UNASSIGNED
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Create objects
        const int test_count=5;
        const int test_size=1000;
        uint32_t test_ids[test_count];
        for (int i=0;i<test_count;i++)
        {
            test_ids[i]=gc_alloc(test_count,&e); 
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }

        //Sort list
        gc_sort_id_list(test_ids,test_count,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Free one object
        gc_free(test_ids[2],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Sort list
        gc_sort_id_list(test_ids,test_count,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_ID_UNASSIGNED,e.code);
    }
}

void test_gc_find_subset()
{
    //Assert error on empty list
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    
        gc_find_subset(NULL,0,42,&e);
        TEST_ASSERT_EQUAL(GC_ERROR_SUBSET_EMPTY,e.code);
        error_reset(&e);
    }

    //Assert error on free items in list
    {
        //Initialize GC
        gc_init(test_mem_aligned,HEAP_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Create objects
        const int test_multiple=1000;
        const int test_count=5;
        uint32_t test_ids[test_count];
        struct GC_Header *test_headers[test_count];
        for (int i=1;i<=test_count;i++)
        {
            test_ids[i-1]=gc_alloc(i*test_multiple,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            test_headers[i-1]=gc_get_header(test_ids[i-1],&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }

        gc_debug(&e);
        printf("\n");

        //Assert no errors if no objects free
        gc_find_subset(test_headers[0],test_count,3032,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        gc_debug(&e);
        printf("\n");

        //Assert error if object free
        gc_free(test_ids[2],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        gc_find_subset(test_headers[0],test_count,3032,&e);

        gc_debug(&e);
        printf("\n");

        TEST_ASSERT_EQUAL(GC_ERROR_SUBSET_FREE,e.code);
    }


        //out of mem for temp lists
        //free items in list

    //Assert correct subsets for various combinations
    //const int test_sizes[]={2000,1000,1000,3000};
    //include perfect matches
    //subset not found
    //test clean up
    const int test_sizes[]={1000,1000,2000,3000};
    uint32_t test_ids[ARRAY_LEN(test_sizes)];
    for (int i=0;i<ARRAY_LEN(test_sizes);i++)
    {
        test_ids[i]=gc_alloc(test_sizes[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }
    struct GC_Header *header=gc_get_header(test_ids[0],&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_find_subset(header,ARRAY_LEN(test_sizes),3032,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //out of mem errors

    //
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_gc_get_header);       //1
    RUN_TEST(test_gc_next_header);      //2
    RUN_TEST(test_gc_init);             //3
    RUN_TEST(test_gc_alloc);            //4
    RUN_TEST(test_gc_realloc);          //5
    RUN_TEST(test_gc_free);             //6
    RUN_TEST(test_gc_lock);             //7
    RUN_TEST(test_gc_unlock);           //8
    RUN_TEST(test_gc_free_bytes);       //9
    RUN_TEST(test_gc_allocated_bytes);  //10
    RUN_TEST(test_gc_locked_bytes);     //11
    RUN_TEST(test_gc_lost_bytes);       //12
    RUN_TEST(test_gc_obj_count);        //13
    RUN_TEST(test_gc_compact_fast);     //14
    RUN_TEST(test_gc_check);            //15
    RUN_TEST(test_gc_swap_next);        //16
    RUN_TEST(test_gc_sort_id_list);     //17
    RUN_TEST(test_gc_find_subset);      //18
    return UNITY_END();
}

