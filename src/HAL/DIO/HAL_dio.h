/******************************************************************************/
/*                                                                            */
/*   S32K144 DIO HAL Module                                                   */
/*                                                                            */
/*   Author:  Pablo Pérez Fernández                                           */
/*   Date:    30/03/2025                                                      */
/*                                                                            */
/*   This module provides functions for initializing 8 digital I/O (GPIO) pins  */
/*   and for reading the state of these pins. The pins are configured as       */
/*   digital inputs using the S32K144 pin driver.                             */
/*                                                                            */
/*   This software is provided free of charge.                              */
/*                                                                            */
/******************************************************************************/

#ifndef HAL_DIO_HAL_DIO_H_
#define HAL_DIO_HAL_DIO_H_

#include <stdint.h>

/**
 * \brief Initializes the 8 digital I/O pins.
 *
 * \details This function configures the 8 GPIO pins as inputs by defining an
 *          array of pin configurations and initializing them with a single call
 *          to the pins driver.
 *
 * \return void.
 */
void HAL_GPIO_Init(void);

/**
 * \brief Reads the state of the 8 digital I/O pins.
 *
 * \details This function reads the state of the pins from the hardware ports,
 *          maps each pin's state to a bit of an 8-bit value, and returns that value.
 *          Each bit in the returned byte corresponds to one of the configured pins.
 *
 * \return A uint8_t where each bit represents the state of one DIO pin (1 = high, 0 = low).
 */
uint8_t HAL_GPIO_ReadInputs(void);

#endif /* HAL_DIO_HAL_DIO_H_ */
