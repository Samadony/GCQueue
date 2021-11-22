/*
 * GCQueue_Interface.h
 *
 *  Created on: Nov 21, 2021
 *      Author: woraelsa
 */

#ifndef INC_GCQUEUE_INTERFACE_H_
#define INC_GCQUEUE_INTERFACE_H_

#include <GCQueue_Core.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * Circular buffer configurations
 * preferably for compitability with different embedded target applications
 * the size shall be divisble by 2(16-bit target) and by 4(32 bit target)
 * TODO: warning or error implementations
 */
#define QUEUE_ENABLE_OVR_WRT			false
#define QUEUE_ERASE_VALUE				0x00U
/*TODO: add macro helper here to add this pattern into the harderase api*/
/*
 * There will be always one extra place need to be used, best that the user
 * adapt the numbe to be divisible by MEMORY_WORD knowing that there will be
 * always size - 1 used to check the memory status (full not full)
 */
#define QUEUE_BUFFER_SIZE				1024U

/*
 * TODO: Templpates shall be added with buffer allocation in the queue section
 * in linker file.
 * steps:
 *  - Define a section in the linker script
 *  - Define a macro guard in the template around the buffer instantiation to
 *  place the buffer where it shall be, the guards shall support the memory
 *  padding/packing as well
 */
/*
 * Error and status of queue
 */
typedef enum{
	GCQ_EMPTY = -2,
	GCQ_FULL = -1,
	GCQ_OK = 0,
	GCQ_DATA_BUFFER_NULL = 1,
	GCQ_ENQUEUE_DATA_NULL = 2,
	GCQ_DEQUEUE_DATA_NULL = 3,
	GCQ_ERROR_NUM
}GCQ_Status_t;


#define DEFINE_GCQUEUE(TYPE)					DEFINE_GCQUEUE_CONC_HELPER(TYPE)
#define DEFINE_GCQUEUE_CONC_HELPER(TYPE)		\
typedef struct{ int32_t write_idx; int32_t read_idx; TYPE* data_buffer_ptr; GCQ_Status_t gcq_status;}GCQ_t;\
PUBLIC GCQ_Status_t GCQueue_EraseHard(GCQ_t* const self);\
PUBLIC GCQ_Status_t GCQueue_EraseSoft(GCQ_t* const self);\
PUBLIC GCQ_Status_t GCQueue_Enqueue(GCQ_t* const self, const TYPE* const TYPE##ptr_data_enqueued);\
PUBLIC GCQ_Status_t GCQueue_Dequeue(GCQ_t* const self, TYPE* const TYPE##ptr_data_dequeued);\
PUBLIC GCQ_Status_t GCQueue_Peek(GCQ_t* const self, TYPE* const TYPE##ptr_data_dequeued);\
PUBLIC GCQ_Status_t GCQueue_IsFull(const GCQ_t* const self);\
PUBLIC GCQ_Status_t GCQueue_IsEmpty(const GCQ_t* const self);\
GCQUEUE_ERASEHARD(TYPE)\
GCQUEUE_ERASESOFT(TYPE)\
GCQUEUE_ISFULL(TYPE)\
GCQUEUE_ISEMPTY(TYPE)\
GCQUEUE_ENQUEUE(TYPE)\
GCQUEUE_DEQUEUE(TYPE)\
GCQUEUE_PEEK(TYPE)\


#define CREATE_GCQUEUE(TYPE, NAME, BUFFER_SIZE_IN_TYPE_SIZE)            \
PRIVATE TYPE NAME##_data_buffer[BUFFER_SIZE_IN_TYPE_SIZE];     						\
PRIVATE GCQ_t NAME = {                                      			\
		.write_idx = 0,                                                 \
		.read_idx = 0,                                                  \
		.data_buffer_ptr = NAME##_data_buffer,			                            \
};                                                                      \


#endif /* INC_GCQUEUE_INTERFACE_H_ */
