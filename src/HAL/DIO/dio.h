/*
 * dio.h
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */

#ifndef HAL_DIO_DIO_H_
#define HAL_DIO_DIO_H_

#include <stdint.h>
#include "conf.h"           // Para PIN_DIO_x

void DIO_Init (void);
uint8_t HAL_GPIO_ReadInputs(void);


#endif /* HAL_DIO_DIO_H_ */
