/*
 * i2c.c
 *
 *  Created on: 27 mar. 2025
 *      Author: pabper3710
 */

#include "i2c.h"
#include "lpi2c_hw_access.h"  /* Incluye las definiciones y funciones del driver LPI2C */

/* Definici�n de la instancia I2C esclavo (usamos LPI2C0 en este ejemplo) */
#define I2C_SLAVE_INSTANCE   ((LPI2C_Type *)LPI2C0_BASE)

/* Direcci�n I2C del esclavo (ajusta seg�n sea necesario) */
#define SLAVE_ADDRESS        0x3A

void I2C_Init(void)
{
    /* Realiza un reset de la l�gica interna del m�dulo I2C en modo esclavo */
    LPI2C_Set_SlaveSoftwareReset(I2C_SLAVE_INSTANCE, true);
    LPI2C_Set_SlaveSoftwareReset(I2C_SLAVE_INSTANCE, false);

    /* Configura la direcci�n del esclavo usando ADDR0 */
    LPI2C_Set_SlaveAddr0(I2C_SLAVE_INSTANCE, SLAVE_ADDRESS);

    /* Configura los pines I2C.
       Usualmente se utiliza el modo 2-pin open drain para I2C. */
    LPI2C_Set_MasterPinConfig(I2C_SLAVE_INSTANCE, LPI2C_CFG_2PIN_OPEN_DRAIN);

    /* Habilita el m�dulo I2C en modo esclavo */
    LPI2C_Set_SlaveEnable(I2C_SLAVE_INSTANCE, true);
}

void I2C_SlaveTransmit(uint8_t data)
{
    /* Env�a un byte utilizando la funci�n del driver */
    LPI2C_Transmit_SlaveData(I2C_SLAVE_INSTANCE, data);
}

uint8_t I2C_SlaveReceive(void)
{
    /* Lee y retorna un byte recibido por el m�dulo I2C */
    return LPI2C_Get_SlaveData(I2C_SLAVE_INSTANCE);
}
