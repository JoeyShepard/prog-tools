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
        int id=gc_alloc(i*GC_MIN_SIZE,&e);
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
                header=(struct GC_Header *)((uintptr_t)header+sizeof(struct GC_Header)+j*GC_MIN_SIZE);
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
    for (int i=1;i<=test_objs;i++)
    {
        int id=gc_alloc(i*GC_MIN_SIZE,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    }

    //Test various types of heap corruption
    const int test_count=3;
    for (int test=0;test<test_count;test++)
    {
        for (int i=1;i<=test_objs;i++)
        {
            //Assert gc_next_header works with no heap corruption
            struct GC_Header *header=gc_get_header(1,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            for (int j=1;j<=test_objs;j++)
            {
                uint32_t expected_size=j*GC_MIN_SIZE+sizeof(struct GC_Header);
                header=gc_next_header(header,&e);
            }
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            //Purposely corrupt heap
            struct GC_Header *test_header=gc_get_header(i,&e);
            uint32_t old_size=test_header->size;
            if (test==0) test_header->size=0;
            else if (test==1) test_header->size=-GC_ALIGN;
            else if (test==2) test_header->size=HEAP_SIZE;

            //Assert error caught after purposely corrupting heap
            header=gc_get_header(1,&e);
            for (int j=1;j<=test_objs;j++)
            {
                uint32_t expected_size=j*GC_MIN_SIZE+sizeof(struct GC_Header);
                header=gc_next_header(header,&e);
            }
            if (test==0) TEST_ASSERT_EQUAL(GC_ERROR_EMPTY_HEADER,e.code);
            else if (test==1) TEST_ASSERT_EQUAL(GC_ERROR_HEADER_SIZE,e.code);
            else if (test==2) TEST_ASSERT_EQUAL(GC_ERROR_HEADER_OVERFLOW,e.code);
            error_reset(&e);

            //Undo heap corruption for next check
            test_header->size=old_size;
        }
    }
}

void test_gc_init()     //3
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert header for GC table of IDs is correct
    uint32_t table_size=sizeof(struct GC_Header)+sizeof(struct GC_Header *)*GC_TABLE_ELEMENTS;
    struct GC_Header *header=(struct GC_Header *)test_mem_aligned;
    TEST_ASSERT_EQUAL(table_size,header->size);
    TEST_ASSERT_FALSE(header->free);
    TEST_ASSERT_EQUAL(0,header->pid);
    TEST_ASSERT_EQUAL(0,header->lock_count);
    TEST_ASSERT_EQUAL(header,((struct GC_Header **)header->data)[0]);
    TEST_ASSERT_EACH_EQUAL_PTR(NULL,&((struct GC_Header **)header->data)[1],GC_TABLE_ELEMENTS-1);

    //Assert empty object marking end of heap is correct
    uint32_t marker_size=sizeof(struct GC_Header);
    header=(struct GC_Header *)((uintptr_t)test_mem_aligned+HEAP_SIZE-sizeof(struct GC_Header));
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
        if (i<=GC_ALIGN) TEST_ASSERT_EQUAL(GC_ALIGN+sizeof(struct GC_Header),header->size);
        else TEST_ASSERT_EQUAL(GC_ALIGN*2+sizeof(struct GC_Header),header->size);

        //Assert ID assigned correctly
        TEST_ASSERT_EQUAL(i,id);
    }

    //TODO: expand ID table if necessary

    //TODO: test out of memory

    //TODO: test splitting blocks (requires free)
}

void test_gc_realloc()  //5
{
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
    uint32_t expected_size=HEAP_SIZE-sizeof(struct GC_Header)*2-GC_TABLE_ELEMENTS*sizeof(struct GC_Header *);
    uint32_t size=gc_free_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(expected_size,size);

    //Assert size after allocating
    const int test_count=100;
    uint32_t test_ids[test_count];
    for (int i=0;i<test_count;i++)
    {
        uint32_t obj_size=(i+1)*GC_MIN_SIZE;
        test_ids[i]=gc_alloc(obj_size,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size-=obj_size+sizeof(struct GC_Header);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert size after locking
    for (int i=0;i<test_count;i++)
    {
        uint32_t obj_size=(i+1)*GC_MIN_SIZE;
        gc_lock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert size after unlocking
    for (int i=0;i<test_count;i++)
    {
        uint32_t obj_size=(i+1)*GC_MIN_SIZE;
        gc_unlock(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        size=gc_free_bytes(&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        TEST_ASSERT_EQUAL(expected_size,size);
    }

    //Assert size after freeing
    for (int i=0;i<test_count;i++)
    {
        uint32_t obj_size=(i+1)*GC_MIN_SIZE;
        gc_free(test_ids[i],&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        expected_size+=obj_size+sizeof(struct GC_Header);
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
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        test_sizes[i]=test*((test*GC_MIN_SIZE)+sizeof(struct GC_Header));
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<test;j++)
        {
            test_ids[test_ids_index]=gc_alloc(test*GC_MIN_SIZE,&e);
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
            expected_size-=test*GC_MIN_SIZE+sizeof(struct GC_Header);
            total_size-=test*GC_MIN_SIZE+sizeof(struct GC_Header);

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
    for (int i=0;i<ARRAY_LEN(tests);i++)
    {
        int test=tests[i];
        test_sizes[i]=test*((test*GC_MIN_SIZE)+sizeof(struct GC_Header));
        gc_set_pid(test,&e);
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        for (int j=0;j<test;j++)
        {
            test_ids[test_ids_index]=gc_alloc(test*GC_MIN_SIZE,&e);
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
            expected_size+=test*GC_MIN_SIZE+sizeof(struct GC_Header);
            total_size+=test*GC_MIN_SIZE+sizeof(struct GC_Header);

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
            expected_size-=test*GC_MIN_SIZE+sizeof(struct GC_Header);
            total_size-=test*GC_MIN_SIZE+sizeof(struct GC_Header);

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
    uint32_t test_ids[test_count];
    uint32_t size=gc_lost_bytes(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    TEST_ASSERT_EQUAL(0,size);

    //Assert no bytes lost while allocating
    for (int i=0;i<test_count;i++)
    {
        int obj_size=(i+1)*GC_MIN_SIZE;
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
        expected_size+=(i+1)*GC_MIN_SIZE+sizeof(struct GC_Header);
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
        int obj_size=(i+1)*GC_MIN_SIZE;
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
        expected_size+=(index+1)*GC_MIN_SIZE+sizeof(struct GC_Header);
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
            int obj_size=(i*4+j+1)*GC_MIN_SIZE;
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
        for (int i=72;i<=100;i+=GC_ALIGN)
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

            if (slot_size-i>=sizeof(struct GC_Header)+GC_MIN_SIZE)
            {
                //Small free object created in slot
                TEST_ASSERT_EQUAL(4,count);
                int size=gc_lost_bytes(&e);
                TEST_ASSERT_EQUAL(size,slot_size-i);
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
        Before                  After
        ======                  =====
        0 free        400       unlocked    100
        1 unlocked    100       unlocked    1000
        2 free        600       locked      200
        3 locked      200       unlocked    1200
        4 free        400       unlocked    1000
        5 free        300       unlocked    700
        6 unlocked    1200      locked      900
        7 unlocked    1000      free        600
        8 locked      900       locked      500
        9 free        600       unlocked    700
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

        struct CheckType
        {
            int size;
            int combined;
            bool free;
            bool locked;
        }checks[]={
            {100,   1,  false,false},
            {1000,  2,  false,false},
            {200,   1,  false,true},
            {1200,  1,  false,false},
            {700,   1,  false,false},
            {1000,  2,  true,false},
            {900,   1,  false,true},
            {600,   1,  true,false},
            {500,   1,  false,true},
            };

        struct GC_Header *header=gc_next_header((struct GC_Header *)test_mem_aligned,&e);
        for (int i=0;i<ARRAY_LEN(checks);i++)
        {
            //Assert object matches expected
            TEST_ASSERT_EQUAL(checks[i].size+sizeof(struct GC_Header)*checks[i].combined,header->size);
            TEST_ASSERT_EQUAL(checks[i].free,header->free);
            if (checks[i].free==false)
            {
                if (checks[i].locked==true)
                    TEST_ASSERT_EQUAL(1,header->lock_count);
                else TEST_ASSERT_EQUAL(0,header->lock_count);
            }
            
            header=gc_next_header(header,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
        }

        //Assert object data correct
        const int test_ids[]={2,4,7,8,9,11,12};
        for (int i=0;i<ARRAY_LEN(test_ids);i++)
        {
            int test=test_ids[i];
            uint8_t *data=gc_lock(test,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

            int count=gc_get_data_size(test,&e);
            TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
            //Correction for slight increase in object size when free space to
                //next object is not enough to create free object
            count-=count%100;
            for (int j=0;j<count;j++)
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

void test_gc_check()
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error when heap is empty
    gc_check(&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error while allocating
    const int test_count=100;
    uint32_t test_ids[test_count];
    for (int i=0;i<test_count;i++)
    {
        test_ids[i]=gc_alloc((i+1)*GC_MIN_SIZE,&e);
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


    RUN_TEST(test_gc_check);
    return UNITY_END();
}

