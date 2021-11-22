//#include <GCQueue_Core.h>
//#include <GCQueue_Interface.h>
//#include <stddef.h>
//#include <string.h>
//
///*
// * Hard erase
// */
//#define GCQUEUE_ERASEHARD(TYPE)					GCQUEUE_ERASEHARD_CONC_HELPER(TYPE)
//#define GCQUEUE_ERASEHARD_CONC_HELPER(TYPE)																		 \
//PUBLIC GCQ_Status_t GCQueue_EraseHard(GCQ_t* const self)                                                         \
//{                                                                                                                \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                     \
//                                                                                                                 \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                        \
//	{                                                                                                            \
//		memset(self->data_buffer_ptr, QUEUE_ERASE_VALUE, QUEUE_BUFFER_SIZE * sizeof(self->data_buffer_ptr[0]));  \
//		self->read_idx = 0;                                                                                      \
//		self->write_idx = 0;                                                                                     \
//                                                                                                                 \
//		gcq_status = GCQ_OK;                                                                                     \
//	}                                                                                                            \
//	else                                                                                                         \
//	{                                                                                                            \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                       \
//	}                                                                                                            \
//	return gcq_status;                                                                                           \
//}                                                                                                                \
//
//
//#define GCQUEUE_ERASESOFT(TYPE)					GCQUEUE_ERASESOFT_CONC_HELPER(TYPE)
//#define GCQUEUE_ERASESOFT_CONC_HELPER(TYPE) \
//PUBLIC GCQ_Status_t GCQueue_EraseSoft(GCQ_t* const self)														\
//{                                                                                                               \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                    \
//                                                                                                                \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                       \
//	{                                                                                                           \
//		self->read_idx = 0;                                                                                     \
//		self->write_idx = 0;                                                                                    \
//                                                                                                                \
//		gcq_status = GCQ_OK;                                                                                    \
//	}                                                                                                           \
//	else                                                                                                        \
//	{                                                                                                           \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                      \
//	}                                                                                                           \
//	return gcq_status;                                                                                          \
//}                                                                                                               \
//
//
//#define GCQUEUE_ISFULL(TYPE)					GCQUEUE_ISFULL_CONC_HELPER(TYPE)
//#define GCQUEUE_ISFULL_CONC_HELPER(TYPE)		\
//PUBLIC GCQ_Status_t GCQueue_IsFull(const GCQ_t* const self)                                                               \
//{                                                                                                                         \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                              \
//                                                                                                                          \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                                 \
//	{                                                                                                                     \
//		/*read = 0 and end = size -1 */                                                                                   \
//		if(((self->read_idx < self->write_idx) && (((self->write_idx - self->read_idx) == (QUEUE_BUFFER_SIZE - 1))))      \
//		||                                                                                                                \
//		/*read = idx and write = idx - 1*/                                                                                \
//		((self->read_idx > self->write_idx) && ((self->read_idx - self->write_idx) == 1)) )                               \
//		{                                                                                                                 \
//			gcq_status = GCQ_FULL;                                                                                        \
//		}                                                                                                                 \
//		else/*Empty  or just not Full*/                                                                                   \
//		{                                                                                                                 \
//			gcq_status = GCQ_OK;                                                                                          \
//		}                                                                                                                 \
//	}                                                                                                                     \
//	else                                                                                                                  \
//	{                                                                                                                     \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                                \
//	}                                                                                                                     \
//	return gcq_status;                                                                                                    \
//}                                                                                                                         \
//
//
//#define GCQUEUE_ISEMPTY(TYPE)					GCQUEUE_ISEMPTY_CONC_HELPER(TYPE)
//#define GCQUEUE_ISEMPTY_CONC_HELPER(TYPE)		\
//PUBLIC GCQ_Status_t GCQueue_IsEmpty(const GCQ_t* const self)															  \
//{                                                                                                                         \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                              \
//                                                                                                                          \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                                 \
//	{                                                                                                                     \
//		if(self->read_idx == self->write_idx) /*read == write*/                                                           \
//		{                                                                                                                 \
//			gcq_status = GCQ_EMPTY;                                                                                       \
//		}                                                                                                                 \
//		else/*Empty  or just not Full*/                                                                                   \
//		{                                                                                                                 \
//			gcq_status = GCQ_OK;                                                                                          \
//		}                                                                                                                 \
//	}                                                                                                                     \
//	else                                                                                                                  \
//	{                                                                                                                     \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                                \
//	}                                                                                                                     \
//	return gcq_status;                                                                                                    \
//}
//
//
//#define GCQUEUE_ENQUEUE(TYPE)					GCQUEUE_ENQUEUE_CONC_HELPER(TYPE)
//#define GCQUEUE_ENQUEUE_CONC_HELPER(TYPE)		\
//PUBLIC GCQ_Status_t GCQueue_Enqueue(GCQ_t* const self, const TYPE* const TYPE##ptr_data_enqueued)						  \
//{                                                                                                                         \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                              \
//                                                                                                                          \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                                 \
//	{                                                                                                                     \
//		if(NULL != TYPE##ptr_data_enqueued)                                                                                   \
//		{                                                                                                                 \
//			/*                                                                                                            \
//			 * QUEUE_ENABLE_OVR_WRT == Enable, this condition always true,                                                \
//			 * order is important to avoid calling isFull()                                                               \
//			 * TODO: Do it to remove IsFull from the code completely saving some                                          \
//			 * flash                                                                                                      \
//			 */                                                                                                           \
//			if( QUEUE_ENABLE_OVR_WRT ||(GCQ_FULL != GCQueue_IsFull(self)) )                                               \
//			{                                                                                                             \
//				self->data_buffer_ptr[self->write_idx] = *TYPE##ptr_data_enqueued;                                        \
//				self->write_idx = ((self->write_idx + 1U) % QUEUE_BUFFER_SIZE);                                           \
//				gcq_status = GCQ_OK;                                                                                      \
//			}                                                                                                             \
//			else /*Queue is Full*/                                                                                        \
//			{                                                                                                             \
//				gcq_status = GCQ_FULL;                                                                                    \
//			}                                                                                                             \
//		}                                                                                                                 \
//		else                                                                                                              \
//		{                                                                                                                 \
//			gcq_status = GCQ_ENQUEUE_DATA_NULL;                                                                           \
//		}                                                                                                                 \
//	}                                                                                                                     \
//	else                                                                                                                  \
//	{                                                                                                                     \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                                \
//	}                                                                                                                     \
//	return gcq_status;                                                                                                    \
//}                                                                                                                         \
//
//
//#define GCQUEUE_DEQUEUE(TYPE)					GCQUEUE_DEQUEUE_CONC_HELPER(TYPE)
//#define GCQUEUE_DEQUEUE_CONC_HELPER(TYPE)		\
//PUBLIC GCQ_Status_t GCQueue_Dequeue(GCQ_t* const self, TYPE* const TYPE##ptr_data_dequeued)								 \
//{                                                                                                                        \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                             \
//                                                                                                                         \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                                \
//	{                                                                                                                    \
//		if(NULL != TYPE##ptr_data_dequeued)                                                                                  \
//		{                                                                                                                \
//			if( GCQ_EMPTY != GCQueue_IsEmpty(self))                                                                      \
//			{                                                                                                            \
//				*TYPE##ptr_data_dequeued = self->data_buffer_ptr[self->read_idx];                                            \
//				self->read_idx = ((self->read_idx + 1U) % QUEUE_BUFFER_SIZE);                                            \
//				gcq_status = GCQ_OK;                                                                                     \
//			}                                                                                                            \
//			else /*Queue is Empty*/                                                                                      \
//			{                                                                                                            \
//				gcq_status = GCQ_EMPTY;                                                                                  \
//			}                                                                                                            \
//		}                                                                                                                \
//		else                                                                                                             \
//		{                                                                                                                \
//			gcq_status = GCQ_ENQUEUE_DATA_NULL;                                                                          \
//		}                                                                                                                \
//	}                                                                                                                    \
//	else                                                                                                                 \
//	{                                                                                                                    \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                               \
//	}                                                                                                                    \
//	return gcq_status;                                                                                                   \
//}                                                                                                                        \
//
//
//#define GCQUEUE_PEEK(TYPE)					GCQUEUE_PEEK_CONC_HELPER(TYPE)
//#define GCQUEUE_PEEK_CONC_HELPER(TYPE)		\
//PUBLIC GCQ_Status_t GCQueue_Peek(GCQ_t* const self, TYPE* const TYPE##ptr_data_dequeued)								\
//{                                                                                                                       \
//	GCQ_Status_t gcq_status = GCQ_ERROR_NUM;                                                                            \
//                                                                                                                        \
//	if((NULL != self) && (NULL != self->data_buffer_ptr))                                                               \
//	{                                                                                                                   \
//		if(NULL != TYPE##ptr_data_dequeued)                                                                             \
//		{                                                                                                               \
//			if( GCQ_EMPTY != GCQueue_IsEmpty(self))                                                                     \
//			{                                                                                                           \
//				*TYPE##ptr_data_dequeued = self->data_buffer_ptr[self->read_idx];                                       \
//				gcq_status = GCQ_OK;                                                                                    \
//			}                                                                                                           \
//			else /*Queue is Empty*/                                                                                     \
//			{                                                                                                           \
//				gcq_status = GCQ_EMPTY;                                                                                 \
//			}                                                                                                           \
//		}                                                                                                               \
//		else                                                                                                            \
//		{                                                                                                               \
//			gcq_status = GCQ_ENQUEUE_DATA_NULL;                                                                         \
//		}                                                                                                               \
//	}                                                                                                                   \
//	else                                                                                                                \
//	{                                                                                                                   \
//		gcq_status = GCQ_DATA_BUFFER_NULL;                                                                              \
//	}                                                                                                                   \
//	return gcq_status;                                                                                                  \
//}																														\



