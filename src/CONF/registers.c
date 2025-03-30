/*******************************************************************************
 *   Registers Module Implementation
 *
 *   Author:  Pablo Pérez Fernández
 *   Date:    30/03/2025
 *
 *   This module implements a simple register map and a state machine to process
 *   incoming I²C bytes. The first byte received is interpreted as the register
 *   index, and the following byte is written to that register.
 *
 *   This software is provided free of charge.
 *
 ******************************************************************************/

/*==============================================================================
                                 INCLUDE FILES
==============================================================================*/
#include "registers.h"
#include <string.h>

/*==============================================================================
                        LOCAL SYMBOLIC CONSTANTS
==============================================================================*/
// (None required for this module)

/*==============================================================================
                           LOCAL TYPES (typedef, enum, struct)
==============================================================================*/
// (No additional local types required)

/*==============================================================================
                          LOCAL VARIABLE DECLARATIONS
==============================================================================*/
/**
 * \brief Array of registers (each register is 1 byte).
 */
static uint8_t g_registers[NUM_REGISTERS] = {0};

/**
 * \brief Flag indicating if the SPI configuration register was modified.
 */
static bool g_configChanged = false;

/**
 * \brief Current register index received from I²C.
 */
static uint8_t g_currentRegIndex = 0U;

/**
 * \brief State flag for the I²C state machine.
 * \details false: waiting for register index; true: waiting for data.
 */
static bool g_waitingForData = false;

/*==============================================================================
                         LOCAL FUNCTION PROTOTYPES
==============================================================================*/
// (No additional local functions)

/*==============================================================================
                            GLOBAL FUNCTION DEFINITIONS
==============================================================================*/

/**
 * \brief Initializes the registers module.
 *
 * \details This function initializes all registers to zero and resets the state
 *          machine used for processing incoming I²C bytes.
 *
 * \return void.
 */
void registers_init(void)
{
    /* Initialize all registers to 0 */
    memset(g_registers, 0, sizeof(g_registers));
    /* Reset state machine variables */
    g_currentRegIndex = 0U;
    g_waitingForData = false;
    g_configChanged = false;
}

/**
 * \brief Updates the GPIO register with the current 8-bit value.
 *
 * \param[in] gpioVal  8-bit value read from the GPIO pins.
 *
 * \return void.
 */
void registers_updateGPIO(uint8_t gpioVal)
{
    g_registers[REG_GPIO] = gpioVal;
}

/**
 * \brief Updates the ADC register for the specified channel.
 *
 * \param[in] channel  ADC channel number (0 or 1).
 * \param[in] adcVal   8-bit value from the ADC conversion.
 *
 * \return void.
 */
void registers_updateADC(uint8_t channel, uint8_t adcVal)
{
    if (channel == 0U)
    {
        g_registers[REG_ADC0] = adcVal;
    }
    else if (channel == 1U)
    {
        g_registers[REG_ADC1] = adcVal;
    }
}

/**
 * \brief Returns the current SPI configuration register value.
 *
 * \return The value stored in the SPI configuration register.
 */
uint8_t registers_getConfig(void)
{
    return g_registers[REG_SPICFG];
}

/**
 * \brief Writes a new value to the SPI configuration register and marks a change.
 *
 * \param[in] newConfig  New configuration value.
 *
 * \return void.
 */
void registers_setConfig(uint8_t newConfig)
{
    g_registers[REG_SPICFG] = newConfig;
    g_configChanged = true;
}

/**
 * \brief Clears the configuration change flag.
 *
 * \return void.
 */
void registers_clearConfigFlag(void)
{
    g_configChanged = false;
}

/**
 * \brief Indicates whether the SPI configuration register has been modified.
 *
 * \return true if the configuration register was changed; false otherwise.
 */
bool registers_configChanged(void)
{
    return g_configChanged;
}

/**
 * \brief Reads the value from a register.
 *
 * \param[in] regIndex  The index of the register to read.
 *
 * \return The value stored in the register, or 0 if the index is out of range.
 */
uint8_t registers_read(uint8_t regIndex)
{
    if (regIndex < NUM_REGISTERS)
    {
        return g_registers[regIndex];
    }
    return 0U;
}

/**
 * \brief Writes a value to a register.
 *
 * \param[in] regIndex  The index of the register to write to.
 * \param[in] value     The value to write.
 *
 * \return void.
 */
void registers_write(uint8_t regIndex, uint8_t value)
{
    if (regIndex < NUM_REGISTERS)
    {
        g_registers[regIndex] = value;
        if (regIndex == REG_SPICFG)
        {
            g_configChanged = true;
        }
    }
}

/**
 * \brief Processes an incoming I²C byte according to the state machine.
 *
 * \details This function implements a simple state machine:
 *          - If waiting for the register index, the received byte is stored as the index.
 *          - Otherwise, the received byte is written to the previously stored register,
 *            and the state machine resets.
 *
 * \param[in] byteReceived  The byte received via I²C.
 *
 * \return void.
 */
void registers_processByte(uint8_t byteReceived)
{
    if (!g_waitingForData)
    {
        /* First byte: treat it as the register index */
        g_currentRegIndex = byteReceived;
        g_waitingForData = true;
    }
    else
    {
        /* Second byte: treat it as data to write into the register */
        registers_write(g_currentRegIndex, byteReceived);
        g_waitingForData = false;
    }
}

/*******************************************************************************
 *                              EOF
 ******************************************************************************/
