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
    TEST_ASSERT_EQUAL(header->size,table_size);
    TEST_ASSERT_FALSE(header->free);
    TEST_ASSERT_EQUAL(header->pid,0);
    TEST_ASSERT_EQUAL(header->lock_count,1);

    //Assert empty object marking end of heap is correct
    uint32_t marker_size=sizeof(struct GC_Header);
    header=(struct GC_Header *)((uintptr_t)test_mem_aligned+HEAP_SIZE-sizeof(struct GC_Header));
    TEST_ASSERT_EQUAL(header->size,marker_size);
    TEST_ASSERT_FALSE(header->free);
    TEST_ASSERT_EQUAL(header->pid,0);
    TEST_ASSERT_EQUAL(header->lock_count,1);

    //Assert memory ready to be allocated
    uint32_t free_size=HEAP_SIZE-table_size-marker_size;
    header=(struct GC_Header *)test_mem_aligned;
    header+=header->size;
    TEST_ASSERT_EQUAL(header->size,free_size);
    TEST_ASSERT_TRUE(header->free);

}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_gc_init);
    return UNITY_END();
}
