/*
 * defines.h
 *
 *  Created on: Nov 21, 2021
 *      Author: woraelsa
 */

#ifndef UTILS_DEFINES_H_
#define UTILS_DEFINES_H_

#define ENABLE								0xFFU
#define DISABLE								0x00U
#define UTEST								ENABLE

#if(ENABLE == UTEST)
#define PRIVATE
#else
#define PRIVATE								static
#endif

#define PUBLIC_API							extern
#define	PUBLIC


#endif /* UTILS_DEFINES_H_ */
