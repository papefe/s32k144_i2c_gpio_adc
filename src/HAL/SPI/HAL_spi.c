/*******************************************************************************
 *   SPI HAL Module Implementation
 *
 *   Author:  Pablo Pérez Fernández
 *   Date:    30/03/2025
 *
 *   This module provides basic initialization and communication functions
 *   for the SPI peripheral on the S32K144. The SPI is configured as a master,
 *   using LPSPI0. It is set up for:
 *      - A source clock frequency of 60 MHz.
 *      - A baud rate of 1 MHz.
 *      - Mode 3 operation (CPOL = 1, CPHA = 1), 8-bit frames, MSB first.
 *      - Chip Select (PCS) active low.
 *
 *   This software is provided free of charge.
 *
 ******************************************************************************/

/*==============================================================================
                           INCLUDE FILES
==============================================================================*/
#include <HAL_spi.h>
#include "lpspi_hw_access.h"   /* Includes LPSPI driver definitions and functions */

/*==============================================================================
                 LOCAL SYMBOLIC CONSTANTS AND MACROS
==============================================================================*/
/** \brief SPI instance: using LPSPI0 base address */
#define SPI_INSTANCE    ((LPSPI_Type *)LPSPI0_BASE)

/** \brief Source clock frequency for SPI (60 MHz) */
static const uint32_t srcClk = 60000000U;
/** \brief Desired SPI baud rate (1 MHz) */
static const uint32_t baudrate = 1000000U;

/*==============================================================================
                      LOCAL FUNCTION PROTOTYPES
==============================================================================*/
// (None)

/*==============================================================================
                            GLOBAL FUNCTION DEFINITIONS
==============================================================================*/

/**
 * \brief Initializes the SPI peripheral.
 *
 * \details This function initializes the LPSPI module with the following settings:
 *          - The SPI module is reset to its default state.
 *          - The source clock is set to 60 MHz and the desired baud rate is 1 MHz.
 *          - The SPI operates in master mode with active-low chip select.
 *          - The Transmit Command Register (TCR) is configured for:
 *              - 8-bit frames.
 *              - Mode 3 operation: CPOL = 1 (clock idle high) and CPHA = 1 (data sampled on the second edge).
 *              - MSB first data order.
 *
 * \return void.
 */
void HAL_SPI_Init(void)
{
    lpspi_init_config_t spiInitConfig;
    lpspi_tx_cmd_config_t txCmdConfig;
    uint32_t prescale;

    /* Initialize the LPSPI module to default values */
    LPSPI_Init(SPI_INSTANCE);

    /* Set up the initialization structure */
    spiInitConfig.lpspiSrcClk = srcClk;
    spiInitConfig.baudRate = baudrate;
    spiInitConfig.lpspiMode = LPSPI_MASTER;
    spiInitConfig.pcsPol = LPSPI_ACTIVE_LOW; /* Chip select active low */

    /* Configure the baud rate and obtain the prescaler value for TCR */
    (void)LPSPI_SetBaudRate(SPI_INSTANCE, spiInitConfig.baudRate, spiInitConfig.lpspiSrcClk, &prescale);

    /* Configure the Transmit Command Register (TCR) for:
       - 8-bit frames.
       - Single bit transfer (normal mode).
       - No masking for transmit or receive.
       - No continuous command or transfer.
       - Byte swap disabled.
       - MSB first.
       - Use PCS2 (ensure it matches your pin mux settings).
       - Prescaler as obtained.
       - Mode 3 (CPOL = 1, CPHA = 1) configuration.
    */
    txCmdConfig.frameSize = 8U;                      /* 8 bits per frame */
    txCmdConfig.width = LPSPI_SINGLE_BIT_XFER;       /* Normal 1-bit transfer */
    txCmdConfig.txMask = false;
    txCmdConfig.rxMask = false;
    txCmdConfig.contCmd = false;                     /* No continuous commands */
    txCmdConfig.contTransfer = false;
    txCmdConfig.byteSwap = false;
    txCmdConfig.lsbFirst = false;                    /* MSB first */
    txCmdConfig.whichPcs = LPSPI_PCS2;               /* Ensure PCS matches your configuration */
    txCmdConfig.preDiv = prescale;                   /* Prescaler obtained above */
    txCmdConfig.clkPolarity = LPSPI_SCK_ACTIVE_HIGH; /* Clock idle high (CPOL = 1) */
    txCmdConfig.clkPhase = LPSPI_CLOCK_PHASE_2ND_EDGE; /* Data captured on second edge (CPHA = 1) */

    /* Apply the TCR configuration */
    LPSPI_SetTxCommandReg(SPI_INSTANCE, &txCmdConfig);

    /* Enable the SPI module */
    LPSPI_Enable(SPI_INSTANCE);
}

/**
 * \brief Transmits a single byte via SPI.
 *
 * \details This function writes a byte to the transmit data register (TDR)
 *          and polls until the transfer is complete.
 *
 * \param[in] data  The byte to transmit.
 *
 * \return void.
 */
void HAL_SPI_Transmit(uint8_t data)
{
    /* Write the data to the TDR */
    LPSPI_WriteData(SPI_INSTANCE, (uint32_t)data);

    /* Poll until the transfer complete flag is set */
    while (!LPSPI_GetStatusFlag(SPI_INSTANCE, LPSPI_TRANSFER_COMPLETE))
    {
        /* Active waiting */
    }

    /* Optionally, clear the transfer complete flag if required:
       LPSPI_ClearStatusFlag(SPI_INSTANCE, LPSPI_TRANSFER_COMPLETE);
    */
}

/**
 * \brief Performs a full-duplex SPI data transfer.
 *
 * \details This function sends a block of data via SPI and reads the data received
 *          simultaneously. It uses polling for each byte transfer.
 *
 * \param[in]  txBuffer  Pointer to the buffer containing data to transmit.
 * \param[out] rxBuffer  Pointer to the buffer where received data will be stored.
 * \param[in]  size      Number of bytes to transfer.
 *
 * \return void.
 */
void HAL_SPI_Transfer(uint8_t *txBuffer, uint8_t *rxBuffer, uint32_t size)
{
    uint32_t i;

    for (i = 0; i < size; i++)
    {
        /* Transmit the byte from the txBuffer */
        LPSPI_WriteData(SPI_INSTANCE, (uint32_t)txBuffer[i]);

        /* Wait until the transfer is complete */
        while (!LPSPI_GetStatusFlag(SPI_INSTANCE, LPSPI_TRANSFER_COMPLETE))
        {
            /* Active waiting */
        }

        /* Read the received byte into rxBuffer */
        rxBuffer[i] = (uint8_t)LPSPI_ReadData(SPI_INSTANCE);
    }
}

/*******************************************************************************
 *                              EOF
 ******************************************************************************/
