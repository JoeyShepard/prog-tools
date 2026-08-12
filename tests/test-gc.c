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

void test_gc_init()
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);

    //Assert no errors from gc_init
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
    header=gc_next_header(header);
    TEST_ASSERT_EQUAL(free_size,header->size);
    TEST_ASSERT_TRUE(header->free);

}

void test_gc_alloc()
{
    //Initialize GC
    gc_init(test_mem_aligned,HEAP_SIZE,&e);

    //Assert no errors from gc_init
    TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

    //Allocate 0 size object - not allowed
    int id=gc_alloc(0,&e);

    //Assert 0 size object allocation fails
    TEST_ASSERT_EQUAL(GC_ERROR_OBJ_SIZE,e.code);

    //Test object size alignment
    error_reset(&e);
    for (int i=1;i<8;i++)
    {
        //Allocate memory
        int id=gc_alloc(i,&e);
        struct GC_Header *header=gc_header(id,&e);

        //Assert no errors in allocation or fetching header
        TEST_ASSERT_EQUAL(ERROR_NONE,e.code);

        //Assert rounded up correctly
        if (i<=GC_ALIGN) TEST_ASSERT_EQUAL(GC_ALIGN+sizeof(struct GC_Header),header->size);
        else TEST_ASSERT_EQUAL(GC_ALIGN*2+sizeof(struct GC_Header),header->size);
    }
}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_gc_init);
    RUN_TEST(test_gc_alloc);
    return UNITY_END();
}
