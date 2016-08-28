/*
 * utils.h
 *
 *  Created on: 18/06/2016
 *      Author: xavier
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "xil_types.h"

int path2args (char *path, char ** argv);
u8 streq (u8 * str1, u8 * str2, size_t n);

#endif /* UTILS_H_ */
