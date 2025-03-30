/*
 * i2c.c
 *
 *  Created on: 27 mar. 2025
 *      Author: pabper3710
 */

#include "i2c.h"
#include "lpi2c_hw_access.h"  /* Incluye las definiciones y funciones del driver LPI2C */

/* Definición de la instancia I2C esclavo (usamos LPI2C0 en este ejemplo) */
#define I2C_SLAVE_INSTANCE   ((LPI2C_Type *)LPI2C0_BASE)

/* Dirección I2C del esclavo (ajusta según sea necesario) */
#define SLAVE_ADDRESS        0x3A

void I2C_Init(void)
{
    /* Realiza un reset de la lógica interna del módulo I2C en modo esclavo */
    LPI2C_Set_SlaveSoftwareReset(I2C_SLAVE_INSTANCE, true);
    LPI2C_Set_SlaveSoftwareReset(I2C_SLAVE_INSTANCE, false);

    /* Configura la dirección del esclavo usando ADDR0 */
    LPI2C_Set_SlaveAddr0(I2C_SLAVE_INSTANCE, SLAVE_ADDRESS);

    /* Configura los pines I2C.
       Usualmente se utiliza el modo 2-pin open drain para I2C. */
    LPI2C_Set_MasterPinConfig(I2C_SLAVE_INSTANCE, LPI2C_CFG_2PIN_OPEN_DRAIN);

    /* Habilita el módulo I2C en modo esclavo */
    LPI2C_Set_SlaveEnable(I2C_SLAVE_INSTANCE, true);
}

void I2C_SlaveTransmit(uint8_t data)
{
    /* Envía un byte utilizando la función del driver */
    LPI2C_Transmit_SlaveData(I2C_SLAVE_INSTANCE, data);
}

uint8_t I2C_SlaveReceive(void)
{
    /* Lee y retorna un byte recibido por el módulo I2C */
    return LPI2C_Get_SlaveData(I2C_SLAVE_INSTANCE);
}
