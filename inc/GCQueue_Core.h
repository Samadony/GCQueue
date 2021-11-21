#ifndef CQUEUE_H_
#define CQUEUE_H_

#include<stdint.h>
#include<utils/defines.h>


typedef enum{
	GCQ_EMPTY = -2,
	GCQ_FULL = -1,
	GCQ_OK = 0,
	GCQ_DATA_BUFFER_NULL = 1,
	GCQ_ENQUEUE_DATA_NULL = 2,
	GCQ_DEQUEUE_DATA_NULL = 3,
	GCQ_ERROR_NUM
}GCQ_Status_t;

typedef struct{
	int16_t write_idx;
	int16_t read_idx;
	uint8_t* data_buffer_ptr;
	GCQ_Status_t gcq_status;
}GCQ_t;

PUBLIC GCQ_Status_t GCQueue_EraseHard(GCQ_t* const self);
PUBLIC GCQ_Status_t GCQueue_EraseSoft(GCQ_t* const self);
PUBLIC GCQ_Status_t GCQueue_Enqueue(GCQ_t* const self, const uint8_t* const u8ptr_data_enqueued);
PUBLIC GCQ_Status_t GCQueue_Dequeue(GCQ_t* const self, uint8_t* const u8ptr_data_dequeued);
PUBLIC GCQ_Status_t GCQueue_IsFull(const GCQ_t* const self);
PUBLIC GCQ_Status_t GCQueue_IsEmpty(const GCQ_t* const self);


#endif //CQUEUE_H_
