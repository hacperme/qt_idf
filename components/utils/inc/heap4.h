#ifndef __HEAP_4_H__
#define __HEAP_4_H__
// #include "config.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define configSUPPORT_DYNAMIC_ALLOCATION (1)

#define configTOTAL_HEAP_SIZE (3*1024*1024)
#define portBYTE_ALIGNMENT    4

#if portBYTE_ALIGNMENT == 32
    #define portBYTE_ALIGNMENT_MASK    ( 0x001f )
#elif portBYTE_ALIGNMENT == 16
    #define portBYTE_ALIGNMENT_MASK    ( 0x000f )
#elif portBYTE_ALIGNMENT == 8
    #define portBYTE_ALIGNMENT_MASK    ( 0x0007 )
#elif portBYTE_ALIGNMENT == 4
    #define portBYTE_ALIGNMENT_MASK    ( 0x0003 )
#elif portBYTE_ALIGNMENT == 2
    #define portBYTE_ALIGNMENT_MASK    ( 0x0001 )
#elif portBYTE_ALIGNMENT == 1
    #define portBYTE_ALIGNMENT_MASK    ( 0x0000 )
#else /* if portBYTE_ALIGNMENT == 32 */
    #error "Invalid portBYTE_ALIGNMENT definition"
#endif /* if portBYTE_ALIGNMENT == 32 */

#define configUSE_MALLOC_FAILED_HOOK 1


#define PRIVILEGED_DATA
#define PRIVILEGED_FUNCTION
#ifndef mtCOVERAGE_TEST_MARKER
    #define mtCOVERAGE_TEST_MARKER()
#endif

/* No tracing by default. */
#ifndef traceMALLOC
#define traceMALLOC( pvReturn, xWantedSize )  /*{printf("\n malloc:%p, size:%d\n", pvReturn, xWantedSize);}*/
#endif

/* No tracing by default. */
#ifndef traceFREE
    #define traceFREE( pv, xBlockSize ) /*{printf("\n free:%p, size:%d\n", pv, xBlockSize);}*/
#endif


// void exit(int);
#define configASSERT( x )   if (!(x)) { printf("\nAssertion failed in %s:%d\n", __FILE__, __LINE__); exit(-1); }


#define taskENTER_CRITICAL()               
#define taskENTER_CRITICAL_FROM_ISR()      

#define taskEXIT_CRITICAL()                
#define taskEXIT_CRITICAL_FROM_ISR( x )   
#define vTaskSuspendAll() 
#define xTaskResumeAll() 



typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t) 0xFFFFFFFFF

/* Used to pass information about the heap out of vPortGetHeapStats(). */
typedef struct xHeapStats
{
    size_t xAvailableHeapSpaceInBytes;      /* The total heap size currently available - this is the sum of all the free blocks, not the largest block that can be allocated. */
    size_t xSizeOfLargestFreeBlockInBytes;  /* The maximum size, in bytes, of all the free blocks within the heap at the time vPortGetHeapStats() is called. */
    size_t xSizeOfSmallestFreeBlockInBytes; /* The minimum size, in bytes, of all the free blocks within the heap at the time vPortGetHeapStats() is called. */
    size_t xNumberOfFreeBlocks;             /* The number of free memory blocks within the heap at the time vPortGetHeapStats() is called. */
    size_t xMinimumEverFreeBytesRemaining;  /* The minimum amount of total free memory (sum of all free blocks) there has been in the heap since the system booted. */
    size_t xNumberOfSuccessfulAllocations;  /* The number of calls to pvPortMalloc() that have returned a valid memory block. */
    size_t xNumberOfSuccessfulFrees;        /* The number of calls to vPortFree() that has successfully freed a block of memory. */
} HeapStats_t;

/*
 * Returns a HeapStats_t structure filled with information about the current
 * heap state.
 */
void vPortGetHeapStats( HeapStats_t * pxHeapStats );

#ifdef SQLITE_OS_QUEC_RTOS

#define pvPortMalloc( x ) malloc(x)
#define pvPortCalloc( a, b ) calloc(a, b)
#define pvPortRealloc( a, b ) realloc(a, b)
#define vPortFree( x ) free(x)
#else
/*
 * Map to the memory management routines required for the port.
 */
void * pvPortMalloc( size_t xSize , void *caller) PRIVILEGED_FUNCTION;
void * pvPortCalloc( size_t xNum,
                     size_t xSize ) PRIVILEGED_FUNCTION;
void * pvPortRealloc( void *p,
                     size_t xSize, void *caller) PRIVILEGED_FUNCTION;
void vPortFree( void * pv ) PRIVILEGED_FUNCTION;
#endif

size_t vPortGetAllocSize( void *p ) PRIVILEGED_FUNCTION;

void vPortInitialiseBlocks( void ) PRIVILEGED_FUNCTION;
size_t xPortGetFreeHeapSize( void ) PRIVILEGED_FUNCTION;
size_t xPortGetMinimumEverFreeHeapSize( void ) PRIVILEGED_FUNCTION;

#if defined(configSTACK_ALLOCATION_FROM_SEPARATE_HEAP) && ( configSTACK_ALLOCATION_FROM_SEPARATE_HEAP == 1 )
    void * pvPortMallocStack( size_t xSize ) PRIVILEGED_FUNCTION;
    void vPortFreeStack( void * pv ) PRIVILEGED_FUNCTION;
#else
    #define pvPortMallocStack    pvPortMalloc
    #define vPortFreeStack       vPortFree
#endif

#if ( configUSE_MALLOC_FAILED_HOOK == 1 )

/**
 * task.h
 * @code{c}
 * void vApplicationMallocFailedHook( void )
 * @endcode
 *
 * This hook function is called when allocation failed.
 */
    void vApplicationMallocFailedHook( void ); /*lint !e526 Symbol not defined as it is an application callback. */
#endif

void show_heap_info(void);

#endif // __HEAP_4_H__