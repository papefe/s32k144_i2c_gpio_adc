/*
 * i2c.h
 *
 *  Created on: 27 mar. 2025
 *      Author: pabper3710
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

/* Inicializa el perif�rico I2C en modo esclavo */
void I2C_Init(void);

/* Env�a un byte v�a I2C (para el esclavo) */
void I2C_SlaveTransmit(uint8_t data);

/* Recibe un byte v�a I2C (para el esclavo) */
uint8_t I2C_SlaveReceive(void);

#endif /* I2C_H */
