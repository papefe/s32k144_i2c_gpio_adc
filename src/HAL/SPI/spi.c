/*
 * spi.c
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */


#include "spi.h"

/* Definición de la instancia de LPSPI a usar, en este ejemplo LPSPI0 */
#define SPI_INSTANCE    ((LPSPI_Type *)LPSPI0_BASE)

/* Configuración inicial para el SPI:
   - Frecuencia del reloj fuente (por ejemplo, 60MHz)
   - Baudrate deseado (por ejemplo, 1MHz)
   - Modo maestro
   - PCS activo en bajo
   - Configuración de TCR para modo 3 (CPOL=1, CPHA=1), 8 bits, MSB first
*/
static const uint32_t srcClk = 60000000U;
static const uint32_t baudrate = 1000000U;

void HAL_SPI_Init(void)
{
    lpspi_init_config_t spiInitConfig;
    lpspi_tx_cmd_config_t txCmdConfig;
    uint32_t prescale;

    /* Inicializar el módulo LPSPI a sus valores por defecto */
    LPSPI_Init(SPI_INSTANCE);

    /* Configuración de la estructura de inicialización */
    spiInitConfig.lpspiSrcClk = srcClk;
    spiInitConfig.baudRate = baudrate;
    spiInitConfig.lpspiMode = LPSPI_MASTER;
    spiInitConfig.pcsPol = LPSPI_ACTIVE_LOW; /* CS activo en bajo */

    /* Configura el baud rate y obtiene el valor de prescaler (para el TCR) */
    (void)LPSPI_SetBaudRate(SPI_INSTANCE, spiInitConfig.baudRate, spiInitConfig.lpspiSrcClk, &prescale);

    /* Configurar la Transmit Command Register para 8 bits, modo 3 y MSB first */
    txCmdConfig.frameSize = 8U;                      /* 8 bits por frame */
    txCmdConfig.width = LPSPI_SINGLE_BIT_XFER;       /* Transferencia normal de 1 bit a la vez */
    txCmdConfig.txMask = false;
    txCmdConfig.rxMask = false;
    txCmdConfig.contCmd = false;                     /* No usar comandos continuos */
    txCmdConfig.contTransfer = false;
    txCmdConfig.byteSwap = false;
    txCmdConfig.lsbFirst = false;                    /* MSB first */
    txCmdConfig.whichPcs = LPSPI_PCS2;               /* Asegúrate de que coincida con el pin mux (en tu caso, PCS asignado en PTE6 es PCS2) */
    txCmdConfig.preDiv = prescale;                   /* Prescaler obtenido */
    /* Modo 3: CPOL = 1 y CPHA = 1 */
    txCmdConfig.clkPolarity = LPSPI_SCK_ACTIVE_HIGH; /* Clock idle high (CPOL=1) */
    txCmdConfig.clkPhase = LPSPI_CLOCK_PHASE_2ND_EDGE;        /* Datos capturados en el segundo flanco (CPHA=1) */

    /* Configura el TCR con la estructura preparada */
    LPSPI_SetTxCommandReg(SPI_INSTANCE, &txCmdConfig);

    /* Habilitar el módulo LPSPI */
    LPSPI_Enable(SPI_INSTANCE);
}

void HAL_SPI_Transmit(uint8_t data)
{
    /* Enviar el dato escribiéndolo en el TDR */
    LPSPI_WriteData(SPI_INSTANCE, (uint32_t)data);

    /* Esperar a que se complete la transferencia (polling del flag de Transfer Complete) */
    while (!LPSPI_GetStatusFlag(SPI_INSTANCE, LPSPI_TRANSFER_COMPLETE))
    {
        ; /* Espera activa */
    }

    /* Se puede limpiar el flag si es necesario (dependiendo del driver) */
    // LPSPI_ClearStatusFlag(SPI_INSTANCE, LPSPI_TRANSFER_COMPLETE);
}

void HAL_SPI_Transfer(uint8_t *txBuffer, uint8_t *rxBuffer, uint32_t size)
{
    uint32_t i;

    for(i = 0; i < size; i++)
    {
        /* Escribe el dato a transmitir */
        LPSPI_WriteData(SPI_INSTANCE, (uint32_t)txBuffer[i]);
        /* Espera hasta que la transferencia se complete */
        while (!LPSPI_GetStatusFlag(SPI_INSTANCE, LPSPI_TRANSFER_COMPLETE))
        {
            ; /* Espera activa */
        }
        /* Lee el dato recibido */
        rxBuffer[i] = (uint8_t)LPSPI_ReadData(SPI_INSTANCE);
    }
}
