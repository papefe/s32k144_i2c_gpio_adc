/*
 * spi.h
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */

#ifndef HAL_SPI_SPI_H_
#define HAL_SPI_SPI_H_

#include <stdint.h>
#include "device_registers.h"
#include "lpspi_hw_access.h"

/* Inicializa el SPI para comunicar con el ISO1H816G */
void HAL_SPI_Init(void);

/* Transmite un byte por SPI */
void HAL_SPI_Transmit(uint8_t data);

/* Transfiere un bloque de datos (envío y recepción) */
void HAL_SPI_Transfer(uint8_t *txBuffer, uint8_t *rxBuffer, uint32_t size);

#endif /* HAL_SPI_SPI_H_ */
