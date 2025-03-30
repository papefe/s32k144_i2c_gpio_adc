/******************************************************************************/
/*                                                                            */
/*   S32K144 DIO HAL Module                                                   */
/*                                                                            */
/*   Author:  Pablo Pérez Fernández                                           */
/*   Date:    30/03/2025                                                      */
/*                                                                            */
/*   This module provides functions for initializing the 8 GPIO pins used    */
/*   for digital input and for reading their current state. The pins are      */
/*   configured using the S32K144 pin driver.                                 */
/*                                                                            */
/*   This software is provided free of charge.                                                     */
/*                                                                            */
/******************************************************************************/

#include <HAL_dio.h>       /* Interface for DIO HAL functions */
#include "pins_driver.h"   /* Definitions for pin_settings_config_t, PINS_Init, etc. */
#include "S32K144.h"       /* Microcontroller-specific constants */

/******************************************************************************/
/*                   Definition of local types and enums                      */
/******************************************************************************/

/******************************************************************************/
/*                     Definition of exported functions                     */
/******************************************************************************/

/**
 * \brief Initializes 8 GPIO pins.
 *
 * \details This function defines an array of 8 pin configurations for digital
 *          input. Each configuration structure specifies the port base, pin
 *          index, pull configuration, multiplexer setting (set to GPIO), and the
 *          direction (input). Then, it calls the pins driver initialization function
 *          (PINS_DRV_Init) to configure all pins in a single call.
 *
 * \return void.
 *
 */
void HAL_GPIO_Init(void)
{
    /* Define configuration for 8 DIO pins.
       Adjust base, pinPortIdx and other parameters as per your hardware design. */
    pin_settings_config_t pinConfig[] = {
        { .base = PORTC, .pinPortIdx = 7U,  .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTC, .pinPortIdx = 6U,  .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 17U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 14U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 15U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 16U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTC, .pinPortIdx = 14U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTC, .pinPortIdx = 3U,  .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
          .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION }
    };

    /* Initialize all 8 pins with a single call */
    PINS_DRV_Init(sizeof(pinConfig) / sizeof(pinConfig[0]), pinConfig);
}

/**
 * \brief Reads the state of the 8 DIO pins.
 *
 * \details This function reads the current state of the pins from the hardware ports.
 *          For optimization, it reads the state of each port (PORTB and PORTC) once,
 *          then maps the specific bits corresponding to the configured pins to a single
 *          8-bit value. Each bit in the returned byte corresponds to one DIO pin.
 *
 * \return A uint8_t where each bit represents the state of one DIO pin (1 = high, 0 = low).
 *
 * \note The mapping is as follows:
 *         - Bit 0: PORTC pin 7.
 *         - Bit 1: PORTC pin 6.
 *         - Bit 2: PORTB pin 17.
 *         - Bit 3: PORTB pin 14.
 *         - Bit 4: PORTB pin 15.
 *         - Bit 5: PORTB pin 16.
 *         - Bit 6: PORTC pin 14.
 *         - Bit 7: PORTC pin 3.
 */
uint8_t HAL_GPIO_ReadInputs(void)
{
    uint8_t estado = 0;

    /* Read the state of each port once to optimize performance */
    uint32_t portB_state = PINS_DRV_ReadPins(PTB);
    uint32_t portC_state = PINS_DRV_ReadPins(PTC);

    /* Map each configured pin to the corresponding bit in the 'estado' byte */
    if (portC_state & (1 << 7))   { estado |= (1 << 0); }  /* Bit 0: PORTC pin 7 */
    if (portC_state & (1 << 6))   { estado |= (1 << 1); }  /* Bit 1: PORTC pin 6 */
    if (portB_state & (1 << 17))  { estado |= (1 << 2); }  /* Bit 2: PORTB pin 17 */
    if (portB_state & (1 << 14))  { estado |= (1 << 3); }  /* Bit 3: PORTB pin 14 */
    if (portB_state & (1 << 15))  { estado |= (1 << 4); }  /* Bit 4: PORTB pin 15 */
    if (portB_state & (1 << 16))  { estado |= (1 << 5); }  /* Bit 5: PORTB pin 16 */
    if (portC_state & (1 << 14))  { estado |= (1 << 6); }  /* Bit 6: PORTC pin 14 */
    if (portC_state & (1 << 3))   { estado |= (1 << 7); }  /* Bit 7: PORTC pin 3 */

    return estado;
}
