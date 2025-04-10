/*******************************************************************************
 *   Main Module
 *
 *   Author:  Pablo P�rez Fern�ndez
 *   Date:    30/03/2025
 *
 *   This module contains the user's application code. It initializes the
 *   system clocks, board pins, and peripheral modules (I�C, SPI, ADC, etc.).
 *   In the main loop, it updates the registers with GPIO and ADC readings,
 *   processes I�C transactions using a polling mechanism, and transmits new SPI
 *   configuration if the configuration register has been modified.
 *
 *   This software is provided free of charge.
 *
 ******************************************************************************/

/*==============================================================================
                           INCLUDE FILES
==============================================================================*/
#include <HAL_adc.h>
#include <HAL_dio.h>
#include <HAL_spi.h>
#include "sdk_project_config.h"
#include <stdio.h>
#include "HAL_i2c.h"
#include "registers.h"
#include "pin_mux.h"  /* Includes BOARD_InitPins() generated by the tool */

extern void initialise_monitor_handles(void);

/*==============================================================================
                      LOCAL FUNCTION DEFINITIONS
==============================================================================*/
/**
 * \brief Polls for I�C transactions.
 *
 * \details This function calls HAL_I2C_SlaveReceive() and, if a non-zero byte is
 *          received, passes it to registers_processByte() to process the incoming
 *          I�C transaction.
 *
 * \return void.
 */
void processI2CTransactionPolling(void)
{
    uint8_t byteReceived = HAL_I2C_SlaveReceive();

    /* We assume that 0 is not a valid data byte. In a real application, a
       mechanism should be implemented to differentiate "no data" from a valid 0x00 */
    if (byteReceived != 0U)
    {
        registers_processByte(byteReceived);
    }
}


/*==============================================================================
                           GLOBAL FUNCTION DEFINITIONS
==============================================================================*/


/**
 * \brief Main entry point of the application.
 *
 * \details Initializes system clocks, board pins, and peripheral modules.
 *          The main loop performs the following tasks:
 *          - Updates the GPIO register with the current state of 8 GPIO inputs.
 *          - Reads two ADC channels and updates the corresponding registers.
 *          - Processes incoming I�C transactions using a simple polling mechanism.
 *          - If the SPI configuration register is modified via I�C, transmits the new
 *            configuration via SPI.
 *
 * \return Returns 0 upon successful execution.
 */
int main(void)
{
    /* Initialize system clocks */
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    /* Initialize board pins */
    BOARD_InitPins();

    /* Initialize peripheral modules */
    HAL_I2C_Init();   /* Initialize I�C in slave mode */
    HAL_SPI_Init();   /* Initialize SPI for communication with ISO1H816G */
    HAL_ADC_Init();   /* Initialize ADC module */

    /* Initialize the registers module */
    registers_init();

    /* Initialize semihosting for printf output */
    initialise_monitor_handles();

    printf("System initialized.\r\n");

    /* Main loop */
    while (1)
    {
        /* Update the GPIO register with the current 8-bit value from the GPIO inputs */
        registers_updateGPIO(HAL_GPIO_ReadInputs());

        /* Read ADC channels (0 and 1) and update the corresponding registers.
           The ADC values are truncated to 8 bits. Adjust scaling as necessary. */
        uint16_t adcVal0 = HAL_ADC_ReadChannel(0);
        uint16_t adcVal1 = HAL_ADC_ReadChannel(1);
        registers_updateADC(0, (uint8_t)adcVal0);
        registers_updateADC(1, (uint8_t)adcVal1);

        /* Process any received I�C transaction using a polling method */
        processI2CTransactionPolling();

        /* If the configuration register has been modified via I�C,
           transmit the new configuration value to the ISO1H816G via SPI */
        if (registers_configChanged())
        {
            uint8_t configValue = registers_getConfig();
            HAL_SPI_Transmit(configValue);
            registers_clearConfigFlag();
        }

        /* Simple delay loop */
        for (volatile int i = 0; i < 1000000; i++);
    }

    /* Although this point is never reached, return 0 */
    return 0;
}

/*==============================================================================
                                 EOF
==============================================================================*/
