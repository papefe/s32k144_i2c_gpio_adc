/*
 * adc.h
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */

#ifndef HAL_ADC_ADC_H_
#define HAL_ADC_ADC_H_

#include <stdint.h>

/* Inicializa el ADC para leer dos canales simples (referenciados a GND) */
void HAL_ADC_Init(void);

/* Lee el canal ADC indicado (ej. 0 o 1) y devuelve el valor bruto */
uint16_t HAL_ADC_ReadChannel(uint8_t channel);

/* Convierte el valor bruto ADC a voltaje real (en voltios)
   - Se asume que el ADC utiliza una referencia interna de 3.3V.
   - Se utiliza un divisor de tensión que reduce la señal real al rango del ADC.
   Por ejemplo, si el divisor reduce 20V a 3.0V, la relación es 0.15.
*/
float HAL_ADC_ConvertToVoltage(uint16_t adcValue);


#endif /* HAL_ADC_ADC_H_ */
