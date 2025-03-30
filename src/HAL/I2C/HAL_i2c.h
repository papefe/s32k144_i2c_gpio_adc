/******************************************************************************/
/*                                                                            */
/*   S32K144 I2C HAL Module                                                   */
/*                                                                            */
/*   Author:  Pablo Pérez Fernández                                           */
/*   Date:    30/03/2025                                                      */
/*                                                                            */
/*   This module provides basic functions for initializing the I2C          */
/*   peripheral in slave mode and for transmitting and receiving a single   */
/*   byte over I2C.                                                           */
/*                                                                            */
/*   This software is provided free of charge.                              */
/*                                                                            */
/******************************************************************************/

/** \file i2c.h
 *
 * \brief I2C HAL Interface.
 *
 * This header declares the functions used for initializing the I2C module in
 * slave mode and for simple byte-level communication.
 *
 * \note This implementation uses the LPI2C driver for the S32K144.
 *
 * \see i2c.c
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Initializes the I2C peripheral in slave mode.
 *
 * \details This function resets the internal logic of the I2C module, sets the slave
 *          address, configures the I2C pins in 2-pin open drain mode, and enables
 *          the I2C module for slave operation.
 *
 * \return void.
 */
void HAL_I2C_Init(void);

/**
 * \brief Transmits a single byte via I2C as a slave.
 *
 * \param[in] data The byte to be transmitted.
 *
 * \return void.
 */
void HAL_I2C_SlaveTransmit(uint8_t data);

/**
 * \brief Receives a single byte via I2C as a slave.
 *
 * \return The received byte.
 */
uint8_t HAL_I2C_SlaveReceive(void);

#endif /* I2C_H */
