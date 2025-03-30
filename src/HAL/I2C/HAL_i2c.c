/******************************************************************************/
/*                                                                            */
/*   S32K144 I2C HAL Module                                                   */
/*                                                                            */
/*   Author:  Pablo Pérez Fernández                                           */
/*   Date:    30/03/2025                                                      */
/*                                                                            */
/*   This module provides basic initialization and communication functions   */
/*   for the I2C peripheral operating in slave mode on the S32K144. It performs */
/*   a hardware reset of the I2C module, sets the slave address, configures the  */
/*   I2C pins (using a 2-pin open drain configuration), and enables the module. */
/*   Additionally, it offers simple functions for transmitting and receiving a  */
/*   single byte using the LPI2C driver.                                      */
/*                                                                            */
/*   This software is provided free of charge.                              */
/*                                                                            */
/******************************************************************************/

#include "HAL_i2c.h"
#include "lpi2c_hw_access.h"  /* Includes LPI2C driver definitions and functions */

/******************************************************************************/
/*                   Definition of local symbolic constants                 */
/******************************************************************************/
/** \brief I2C slave instance using LPI2C0 base address. */
#define I2C_SLAVE_INSTANCE   ((LPI2C_Type *)LPI2C0_BASE)

/** \brief I2C slave address. Adjust as necessary. */
#define SLAVE_ADDRESS        0x3A

/******************************************************************************/
/*                      Definition of exported functions                      */
/******************************************************************************/

/**
 * \brief Initializes the I2C peripheral in slave mode.
 *
 * \details This function resets the internal logic of the I2C module, sets the
 *          slave address using ADDR0, configures the I2C pins in 2-pin open drain
 *          mode, and enables the I2C module in slave mode.
 *
 * \return void.
 *
 * \note This is a basic initialization. For full I2C register management, additional
 *       protocol layers (e.g., handling multi-byte transactions) should be implemented.
 */
void HAL_I2C_Init(void)
{
    /* Perform a software reset of the I2C slave module */
    LPI2C_Set_SlaveSoftwareReset(I2C_SLAVE_INSTANCE, true);
    LPI2C_Set_SlaveSoftwareReset(I2C_SLAVE_INSTANCE, false);

    /* Set the slave address using ADDR0 */
    LPI2C_Set_SlaveAddr0(I2C_SLAVE_INSTANCE, SLAVE_ADDRESS);

    /* Configure the I2C pins.
       Typically, I2C uses 2-pin open drain configuration. */
    LPI2C_Set_MasterPinConfig(I2C_SLAVE_INSTANCE, LPI2C_CFG_2PIN_OPEN_DRAIN);

    /* Enable the I2C module in slave mode */
    LPI2C_Set_SlaveEnable(I2C_SLAVE_INSTANCE, true);
}

/**
 * \brief Transmits a single byte over I2C as a slave.
 *
 * \details Uses the LPI2C driver function to send a byte from the slave module.
 *
 * \param[in] data The byte to transmit.
 *
 * \return void.
 */
void HAL_I2C_SlaveTransmit(uint8_t data)
{
    /* Transmit a byte using the driver function */
    LPI2C_Transmit_SlaveData(I2C_SLAVE_INSTANCE, data);
}

/**
 * \brief Receives a single byte over I2C as a slave.
 *
 * \details Reads a byte from the I2C slave data register using the driver function.
 *
 * \return The received byte.
 */
uint8_t HAL_I2C_SlaveReceive(void)
{
    /* Read and return a byte received by the I2C slave module */
    return LPI2C_Get_SlaveData(I2C_SLAVE_INSTANCE);
}
