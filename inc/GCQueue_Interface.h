/*
 * GCQueue_Interface.h
 *
 *  Created on: Nov 21, 2021
 *      Author: woraelsa
 */

#ifndef INC_GCQUEUE_INTERFACE_H_
#define INC_GCQUEUE_INTERFACE_H_
#include <stdbool.h>
/*
 * Circular buffer configurations
 * preferably for compitability with different embedded target applications
 * teh size shall be divisble by 2(16-bit target) and by 4(32 bit target)
 * TODO: warning or error implementations
 */
#define QUEUE_ENABLE_OVR_WRT			false
#define QUEUE_ERASE_VALUE				0x00U
#define QUEUE_BUFFER_SIZE				512U


#endif /* INC_GCQUEUE_INTERFACE_H_ */
