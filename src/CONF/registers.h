/*******************************************************************************
 *   Registers Module
 *
 *   Author:  Pablo Pérez Fernández
 *   Date:    30/03/2025
 *
 *   This module provides a simple register map to store configuration and data
 *   accessible via I²C. It also includes a state machine to process incoming
 *   I²C bytes: the first byte sets the register index, and the second is used to
 *   write data to that register.
 *
 *   This software is provided free of charge.
 *
 ******************************************************************************/

#ifndef MID_REG_REGISTERS_H_
#define MID_REG_REGISTERS_H_

#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
/*                Definition of exported symbolic constants               */
/******************************************************************************/
/** \brief Register for reading 8 GPIO pins */
#define REG_GPIO   0
/** \brief Register for reading ADC channel 0 */
#define REG_ADC0   1
/** \brief Register for reading ADC channel 1 */
#define REG_ADC1   2
/** \brief Register for SPI configuration to be sent via SPI */
#define REG_SPICFG 3
/** \brief Total number of registers available */
#define NUM_REGISTERS 4

/******************************************************************************/
/*         Declaration of exported function prototypes                      */
/******************************************************************************/

/**
 * \brief Initializes the registers module.
 *
 * \details This function initializes all registers to 0 and resets the state
 *          machine used for processing incoming I²C bytes.
 *
 * \return void.
 */
void registers_init(void);

/**
 * \brief Updates the GPIO register with the current 8-bit value.
 *
 * \param[in] gpioVal  8-bit value read from the GPIO pins.
 *
 * \return void.
 */
void registers_updateGPIO(uint8_t gpioVal);

/**
 * \brief Updates the ADC register corresponding to the specified channel.
 *
 * \param[in] channel  ADC channel number (0 or 1).
 * \param[in] adcVal   8-bit value derived from the ADC conversion.
 *
 * \return void.
 */
void registers_updateADC(uint8_t channel, uint8_t adcVal);

/**
 * \brief Retrieves the current configuration for the SPI.
 *
 * \return The value stored in the SPI configuration register.
 */
uint8_t registers_getConfig(void);

/**
 * \brief Writes a new value to the SPI configuration register and marks the configuration as changed.
 *
 * \param[in] newConfig  New configuration value.
 *
 * \return void.
 */
void registers_setConfig(uint8_t newConfig);

/**
 * \brief Clears the configuration change flag.
 *
 * \return void.
 */
void registers_clearConfigFlag(void);

/**
 * \brief Returns whether the configuration has been modified.
 *
 * \return true if the configuration register was changed; false otherwise.
 */
bool registers_configChanged(void);

/**
 * \brief Reads the value stored in the specified register.
 *
 * \param[in] regIndex  The index of the register to read.
 *
 * \return The value stored in the register, or 0 if the index is out of range.
 */
uint8_t registers_read(uint8_t regIndex);

/**
 * \brief Writes a value to the specified register.
 *
 * \param[in] regIndex  The index of the register to write to.
 * \param[in] value     The value to write.
 *
 * \return void.
 */
void registers_write(uint8_t regIndex, uint8_t value);

/**
 * \brief Processes an incoming I²C byte.
 *
 * \details Implements a simple state machine:
 *          - If no register index has been received, the received byte is treated as the register index.
 *          - Otherwise, the received byte is written into that register and the state is reset.
 *
 * \param[in] byteReceived  The byte received via I²C.
 *
 * \return void.
 */
void registers_processByte(uint8_t byteReceived);

#endif /* MID_REG_REGISTERS_H_ */
