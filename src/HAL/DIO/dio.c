/*
 * dio.c
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */


#include "dio.h"
#include "pins_driver.h"   // Incluye la definición de pin_settings_config_t, PINS_Init, etc.
#include "S32K144.h"       // Para definiciones de constantes
#include "dio_hwab_pin.h"

/* Definir tipos para la dirección, configuración y valor, según tu diseño. Por ejemplo: */
typedef enum {
    DIO_INPUT,
    DIO_OUTPUT
} DIO_pin_direction_t;

typedef enum {
    DIO_NO_PULL,
    DIO_PULLUP,
    DIO_PULLDOWN
} DIO_pin_configuration_t;

typedef enum {
    DIO_LOW,
    DIO_HIGH
} DIO_pin_value_t;

typedef enum {
    DIO_RESULT_SUCCESS = 0,
    DIO_RESULT_ERROR
} DIO_result_t;


void DIO_Init(void)
{
    /* Definición de la configuración de los 8 pines */
    pin_settings_config_t pinConfig[] = {
        /* Ejemplo para 8 pines; ajusta base, índice y demás parámetros según tu hardware */
        { .base = PORTC, .pinPortIdx = 7U,  .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTC, .pinPortIdx = 6U,  .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 17U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 14U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 15U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTB, .pinPortIdx = 16U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTC, .pinPortIdx = 14U, .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION },
        { .base = PORTC, .pinPortIdx = 3U,  .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED, .mux = PORT_MUX_AS_GPIO, .direction = GPIO_INPUT_DIRECTION }
    };

    /* Inicializa todos los pines de una sola llamada */
    PINS_DRV_Init(8, pinConfig);
}

uint8_t HAL_GPIO_ReadInputs(void) {
    uint8_t estado = 0;

    // Leemos una sola vez el estado de cada puerto para optimizar
    uint32_t portB_state = PINS_DRV_ReadPins(PTB);
    uint32_t portC_state = PINS_DRV_ReadPins(PTC);

    // Mapeamos cada pin configurado al bit correspondiente del byte 'estado'
    // Bit 0: Pin en PORTC, índice 7
    if (portC_state & (1 << 7)) {
        estado |= (1 << 0);
    }
    // Bit 1: Pin en PORTC, índice 6
    if (portC_state & (1 << 6)) {
        estado |= (1 << 1);
    }
    // Bit 2: Pin en PORTB, índice 17
    if (portB_state & (1 << 17)) {
        estado |= (1 << 2);
    }
    // Bit 3: Pin en PORTB, índice 14
    if (portB_state & (1 << 14)) {
        estado |= (1 << 3);
    }
    // Bit 4: Pin en PORTB, índice 15
    if (portB_state & (1 << 15)) {
        estado |= (1 << 4);
    }
    // Bit 5: Pin en PORTB, índice 16
    if (portB_state & (1 << 16)) {
        estado |= (1 << 5);
    }
    // Bit 6: Pin en PORTC, índice 14
    if (portC_state & (1 << 14)) {
        estado |= (1 << 6);
    }
    // Bit 7: Pin en PORTC, índice 3
    if (portC_state & (1 << 3)) {
        estado |= (1 << 7);
    }

    return estado;
}

/* Función que inicializa los 8 pines configurados como entradas con pull-up */
void DIO_InitAll(void)
{
    /* Inicializa PIN_DIO_1 (corresponde a PTC7) */
    if (DIO_HwAb_Init(PIN_DIO_1, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error, por ejemplo, detener ejecución o registrar error */
    }

    /* Inicializa PIN_DIO_2 (corresponde a PTC6) */
    if (DIO_HwAb_Init(PIN_DIO_2, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }

    /* Inicializa PIN_DIO_3 (corresponde a PTB17) */
    if (DIO_HwAb_Init(PIN_DIO_3, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }

    /* Inicializa PIN_DIO_4 (corresponde a PTB14) */
    if (DIO_HwAb_Init(PIN_DIO_4, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }

    /* Inicializa PIN_DIO_5 (corresponde a PTB15) */
    if (DIO_HwAb_Init(PIN_DIO_5, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }

    /* Inicializa PIN_DIO_6 (corresponde a PTB16) */
    if (DIO_HwAb_Init(PIN_DIO_6, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }

    /* Inicializa PIN_DIO_7 (corresponde a PTC14) */
    if (DIO_HwAb_Init(PIN_DIO_7, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }

    /* Inicializa PIN_DIO_8 (corresponde a PTC3) */
    if (DIO_HwAb_Init(PIN_DIO_8, DIO_INPUT, DIO_PULLUP, DIO_LOW) != DIO_RESULT_SUCCESS)
    {
        /* Manejo de error */
    }
}
