/*
 * dio_hwab_pin.h
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */

#ifndef HAL_DIO_DIO_HWAB_PIN_H_
#define HAL_DIO_DIO_HWAB_PIN_H_

#include "S32K144.h"  // Asegúrate de que incluye las definiciones de PORTC, PORTB, etc.

/* Estructura que mapea un pin lógico a la configuración de hardware */
typedef struct {
    uint32_t pinIdentifier;   /* Puede ser el número lógico, por ejemplo, 80, 81, etc. */
    PORT_Type *port_base;     /* Base del puerto, por ejemplo, PORTC o PORTB */
    uint8_t pinPortIdx;       /* Índice del pin dentro del puerto */
    GPIO_Type *gpio_base;     /* Base del GPIO correspondiente, por ejemplo, PTC o PTB */
} dio_hwab_pin_t;

/* Declaración del array de mapeo para los 8 pines */
extern const dio_hwab_pin_t dio_hwab_pin[];

#endif /* HAL_DIO_DIO_HWAB_PIN_H_ */
