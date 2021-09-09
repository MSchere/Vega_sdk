/*
 Simple malloc and free implementation based on https://gist.github.com/mshr-h/9636fa0adcf834103b1b
 */
#include <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 all the API functions to use the MPU wrappers.  That should only be done when
 task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "fsl_debug_console.h"
#include "task.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#if( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
	#error This file must not be used if configSUPPORT_DYNAMIC_ALLOCATION is 0
#endif

/* Block sizes must not get too small. */
#define heapMINIMUM_BLOCK_SIZE	( ( size_t ) ( xHeapStructSize << 1 ) )

/* Assumes 8bit bytes! */
#define heapBITS_PER_BYTE		( ( size_t ) 8 )

/* Allocate the memory for the heap. */
#if( configAPPLICATION_ALLOCATED_HEAP == 1 )
	/* The application writer has already defined the array used for the RTOS
	heap - probably so it can be placed in a special segment or address. */
	extern uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#else
static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
//const uint8_t *ucHeap = (uint8_t*) (0x20004200) ; //0x20003200 plant control system
//20004200 ASW
//const uint8_t *ucHeap = (uint8_t*) (0x2002E800-configTOTAL_HEAP_SIZE); //end of m_data
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/*-----------------------------------------------------------*/

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
static void prvHeapInit(void);

/*-----------------------------------------------------------*/



/* Keeps track of the number of free bytes remaining, but says nothing about
 fragmentation. */
static size_t xFreeBytesRemaining = 0U;
static size_t xMinimumEverFreeBytesRemaining = 0U;

/* Gets set to the top bit of an size_t type.  When this bit in the xBlockSize
 member of an BlockLink_t structure is set then the block belongs to the
 application.  When the bit is free the block is still part of the free heap
 space. */
//static size_t xBlockAllocatedBit = 0;
typedef struct MCB { //Memory Control Block
	int is_available;
	size_t size;
} MCB_t;

/* The size of the structure placed at the beginning of each allocated memory
 block must by correctly byte aligned. */
static const size_t xHeapStructSize = (sizeof(MCB_t)
		+ ((size_t) ( portBYTE_ALIGNMENT - 1)))
		& ~((size_t) portBYTE_ALIGNMENT_MASK);

void *memory_start, *last_valid_address, *memory_end;

/*-----------------------------------------------------------*/

static void prvHeapInit(void) {
	uint8_t *pucAlignedHeap;
	size_t uxAddress;
	size_t xTotalHeapSize = configTOTAL_HEAP_SIZE;

	/* Ensure the heap starts on a correctly aligned boundary. */
	uxAddress = (size_t) ucHeap;
	if ((uxAddress & portBYTE_ALIGNMENT_MASK) != 0) {
		uxAddress += ( portBYTE_ALIGNMENT - 1);
		uxAddress &= ~((size_t) portBYTE_ALIGNMENT_MASK);
		xTotalHeapSize -= uxAddress - (size_t) ucHeap;
	}
	pucAlignedHeap = (uint8_t*) uxAddress;

	memory_start = (void*) pucAlignedHeap; //Memory start is the address of the heap
	last_valid_address = memory_start;  //Last valid address is the memory start at the beginning

	uxAddress = ((size_t) pucAlignedHeap) + xTotalHeapSize;
	uxAddress -= xHeapStructSize;
	uxAddress &= ~((size_t) portBYTE_ALIGNMENT_MASK);
	memory_end = (void*) uxAddress; //Stores the last possible address
	xMinimumEverFreeBytesRemaining = xTotalHeapSize; //All of the heap is free at the beginning
	xFreeBytesRemaining = xMinimumEverFreeBytesRemaining;
}

/*-----------------------------------------------------------*/

void* pvPortMalloc(size_t xWantedSize) {
	void *current_location = NULL; //Where we are looking in memory
	struct MCB *current_location_mcb; //Cast to control block
	void *memory_location = NULL; //Value to be returned
	vTaskSuspendAll();
	{
		if (memory_end == NULL) {
			prvHeapInit(); //Last address NULL, not initialized
		}
		//Wanted size greater than 0 and there is free space remaining in the heap
		if ((xWantedSize > 0) && (xWantedSize <= xFreeBytesRemaining)) {
			xWantedSize = xWantedSize + sizeof(MCB_t); //Memory must include de MCB
			current_location = memory_start; //Start from the beginning
			while (current_location != last_valid_address) { //While not at the last location
				current_location_mcb = (struct MCB*) current_location; //Cast to MCB
				if (current_location_mcb->is_available) { //Location is available
					if (current_location_mcb->size >= xWantedSize) { //There is enough space
						current_location_mcb->is_available = 0; //We take it
						memory_location = current_location; //and return it
						break;
					}
				}
				//Current block is not suitable
				current_location = current_location + current_location_mcb->size; 
			}
			if (!memory_location) { //No valid blocks found, new memory is used
				//New memory will be where the last valid address left is
				memory_location = last_valid_address;
				// We move the last valid address forward by xWantedSize
				last_valid_address = last_valid_address + (int) xWantedSize;
				// Initialize the mem_control_block
				current_location_mcb = memory_location;
				current_location_mcb->is_available = 0;
				current_location_mcb->size = xWantedSize;
			}
			//Move to pointer past the MCB
			memory_location = memory_location + sizeof(MCB_t);
			xFreeBytesRemaining -= current_location_mcb->size; //Update bytes remaining
			//PRINTF("\r\nFree heap bytes remaining:%d\r\n",(int) xFreeBytesRemaining);
			if (xFreeBytesRemaining < xMinimumEverFreeBytesRemaining) {
				xMinimumEverFreeBytesRemaining = xFreeBytesRemaining; //Update minimum ever bytes remaining
			}
		} else {
			mtCOVERAGE_TEST_MARKER(); //ERROR
		}traceMALLOC(memory_location, xWantedSize );
	}
	(void) xTaskResumeAll();
	
	#if( configUSE_MALLOC_FAILED_HOOK == 1 ) //Malloc failed hook activated in FreeRTOSConfig
	{
		if( memory_location == NULL )
		{
			extern void vApplicationMallocFailedHook(size_t size);
			vApplicationMallocFailedHook(xWantedSize);
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	#endif
	
	configASSERT(
			( ( ( size_t ) memory_location ) & ( size_t ) portBYTE_ALIGNMENT_MASK ) == 0);
	return memory_location;
}
/*-----------------------------------------------------------*/

void vPortFree(void *pv) {
	struct MCB *mcb;

	vTaskSuspendAll();
	{
		//Release block
		mcb = pv - sizeof(MCB_t);
		xFreeBytesRemaining += mcb->size;
		traceFREE( pv, mcb->size);
		mcb->is_available = 1;
	}
	(void) xTaskResumeAll();

	return;
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize(void) {
	return xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t xPortGetMinimumEverFreeHeapSize(void) {
	return xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

void vPortInitialiseBlocks(void) {
	/* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(size_t size) {
	PRINTF("\r\nMALLOC FAILED after requesting %d bytes with %d bytes remaining\r\n", size, xPortGetFreeHeapSize());
}

/*-----------------------------------------------------------*/

