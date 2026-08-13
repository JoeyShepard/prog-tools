#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "compatibility.h"
#include "error.h"
#include "gc.h"
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

void test_gc_get_header()
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
        int id=gc_alloc(i*GC_ALIGN,&e);
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
                header=(struct GC_Header *)((uintptr_t)header+sizeof(struct GC_Header)+j*GC_ALIGN);
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

void test_gc_next_header()
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Alocate test objects
    const int test_objs=5;
    for (int i=1;i<=test_objs;i++)
    {
        int id=gc_alloc(i*GC_ALIGN,&e);
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
                uint32_t expected_size=j*GC_ALIGN+sizeof(struct GC_Header);
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
                uint32_t expected_size=j*GC_ALIGN+sizeof(struct GC_Header);
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

void test_gc_init()
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
    TEST_ASSERT_EQUAL(1,header->lock_count);
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

void test_gc_alloc()
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

void test_gc_free()
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert double free causes error
    int id=gc_alloc(100,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_ID_UNASSIGNED,e.code);
    error_reset(&e);

    //Assert no error if freeing memory from same PID
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(100,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(100,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert no error if freeing from PID 0
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(100,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Assert error if freeing from different PID
    gc_set_pid(0,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(100,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);

    gc_set_pid(1,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    id=gc_alloc(100,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_set_pid(2,&e);
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);
    gc_free(id,&e);
    TEST_ASSERT_EQUAL(GC_ERROR_WRONG_PID,e.code);
    error_reset(&e);

    //Assert error if memory is locked
    id=gc_alloc(100,&e);
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

void test_gc_lock()
{
}

void test_gc_unlock()
{
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_gc_get_header);
    RUN_TEST(test_gc_next_header);
    RUN_TEST(test_gc_init);
    RUN_TEST(test_gc_alloc);
    RUN_TEST(test_gc_free);
    RUN_TEST(test_gc_lock);
    RUN_TEST(test_gc_unlock);
    return UNITY_END();
}

