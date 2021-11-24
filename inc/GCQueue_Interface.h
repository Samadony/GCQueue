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

/*TODO: add macro helper here to add this pattern into the hard erase API*/
/*
 * There will be always one extra place need to be used, best that the user
 * adapt the numbe to be divisible by MEMORY_WORD knowing that there will be
 * always size - 1 used to check the memory status (full not full)
 *
 * The size shall be divisible by 2
 */
#define QUEUE_BUFFER_SIZE_1024				10
#define QUEUE_BUFFER_SIZE				(1 << QUEUE_BUFFER_SIZE_1024)
#define QUEUE_BUFFER_MEMORY_SECTION
#define QUEUE_BUFFER_PACKING

/*
 * Error and status of queue
 */
typedef enum{
	GCQ_EMPTY = -2,
	GCQ_FULL = -1,
	GCQ_OK = 0,
	GCQ_DATA_BUFFER_NULL = 1,
	GCQ_ENQUEUE_DATA_ADD_NULL = 2,
	GCQ_DEQUEUE_DATA_ADD_NULL = 3,
	GCQ_ERROR_NUM
}GCQ_Status_t;

/*
 * Template to define queue_header + queue buffer with types varies between
 * signed/unsigned 8, 16, 32 and 64 bits variables
 *
 * Constraint, This MACRO shall be invoked once per type
 * Preferred place of invocation is here in this file
 */

#define DEFINE_GCQUEUE(TYPE)					DEFINE_GCQUEUE_ABSTRACTOR(TYPE)

/* Pre -requisite: calling DEFINE_GCQUEUE() with the same type used for OBJECT_ADD creation
 * Template to instantiate queue_header + queue buffer with types varies between
 * signed/unsigned 8, 16, 32 and 64 bits variables
 */
#define CREATE_GCQUEUE(TYPE, NAME, BUFFER_SIZE_IN_TYPE_SIZE)\
				CREATE_GCQUEUE_ABSTRACTOR(TYPE, NAME, BUFFER_SIZE_IN_TYPE_SIZE)
/*
 * APIs
 */
#define GCQ_HARD_ERASE_API(TYPE, OBJECT_ADD) 			GCQ_HARD_ERASE_ABSTRACTOR(TYPE, OBJECT_ADD)
#define GCQ_SOFT_ERASE_API(TYPE, OBJECT_ADD) 			GCQ_SOFT_ERASE_ABSTRACTOR(TYPE, OBJECT_ADD)
#define GCQ_IS_FULL_API(TYPE, OBJECT_ADD)				GCQ_IS_FULL_ABSTRACTOR(TYPE, OBJECT_ADD)
#define GCQ_IS_EMPTY_API(TYPE, OBJECT_ADD)				GCQ_IS_EMPTY_ABSTRACTOR(TYPE, OBJECT_ADD)
#define GCQ_ENQUEUE_API(TYPE, OBJECT_ADD, DATA_ADD)  		GCQ_ENQUEUE_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
#define GCQ_DEQUEUE_API(TYPE, OBJECT_ADD, DATA_ADD)  		GCQ_DEQUEUE_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
#define GCQ_PEEK_API(TYPE, OBJECT_ADD, DATA_ADD)  			GCQ_PEEK_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
#endif /* INC_GCQUEUE_INTERFACE_H_ */
