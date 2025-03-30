/*!
** Copyright 2020 NXP
** @file main.c
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary configuration files. */
#include "sdk_project_config.h"
#include <stdio.h>
#include "spi.h"
#include "dio.h"
#include "i2c.h"
#include "pin_mux.h"  /* Incluye la función BOARD_InitPins() generada por la herramienta */


extern void initialise_monitor_handles(void);


int main(void)
{

	/* InicializaciÃ³n del Clock */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	/* Inicialización de Pines */
	BOARD_InitPins();

    I2C_Init();         // Inicializa el I2C en modo esclavo
    HAL_SPI_Init();     // Inicializa el SPI para comunicarse con el ISO1H816G

    initialise_monitor_handles();

    printf("Sistema inicializado.\r\n");

    /* Bucle principal */
    while (1)
    {

    }

    /* Aunque este punto nunca se alcanza */
    return 0;
}


/* END main */
/*!
** @}
*/
