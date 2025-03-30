/*******************************************************************************
 *   SPI HAL Module
 *
 *   Author:  Pablo Pérez Fernández
 *   Date:    30/03/2025
 *
 *   This module provides basic initialization and communication functions for
 *   the SPI peripheral on the S32K144. It configures the SPI to operate in
 *   master mode with the following settings:
 *     - Source clock: 60 MHz
 *     - Baud rate: 1 MHz
 *     - Mode 3 operation (CPOL = 1, CPHA = 1), 8-bit frames, MSB first
 *     - Active-low Chip Select (PCS)
 *
 *   This software is provided free of charge.
 *
 ******************************************************************************/

/*==============================================================================
                           INCLUDE FILES
==============================================================================*/
#ifndef HAL_SPI_HAL_SPI_H_
#define HAL_SPI_HAL_SPI_H_

#include <stdint.h>
#include "device_registers.h"
#include "lpspi_hw_access.h"

/******************************************************************************/
/*                Declaration of exported function prototypes               */
/******************************************************************************/

/**
 * \brief Initializes the SPI peripheral.
 *
 * \details This function configures the SPI peripheral (using LPSPI0) with a
 *          source clock of 60 MHz, a baud rate of 1 MHz, and settings for Mode 3
 *          operation (CPOL=1, CPHA=1). The chip select is active low.
 *
 * \return void.
 */
void HAL_SPI_Init(void);

/**
 * \brief Transmits a single byte via SPI.
 *
 * \details This function sends one byte by writing to the SPI transmit data register,
 *          and waits until the transfer is complete.
 *
 * \param[in] data  The byte to transmit.
 *
 * \return void.
 */
void HAL_SPI_Transmit(uint8_t data);

/**
 * \brief Performs a full-duplex SPI data transfer.
 *
 * \details This function transmits a block of data while simultaneously receiving
 *          data from the SPI peripheral. The function uses polling to wait for each
 *          transfer to complete.
 *
 * \param[in]  txBuffer  Pointer to the buffer containing data to transmit.
 * \param[out] rxBuffer  Pointer to the buffer where received data will be stored.
 * \param[in]  size      Number of bytes to transfer.
 *
 * \return void.
 */
void HAL_SPI_Transfer(uint8_t *txBuffer, uint8_t *rxBuffer, uint32_t size);

#endif /* HAL_SPI_HAL_SPI_H_ */
