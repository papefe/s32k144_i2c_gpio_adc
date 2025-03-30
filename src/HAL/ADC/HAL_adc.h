/******************************************************************************/
/*                                                                            */
/*   S32K144 ADC HAL Module                                                   */
/*                                                                            */
/*   Author:  Pablo Pérez Fernández                                           */
/*   Date:    30/03/2025                                                      */
/*                                                                            */
/*   This module provides functions for initializing the ADC to read two     */
/*   single-ended channels (referenced to GND), reading the raw ADC           */
/*   conversion result from a specified channel, and converting that raw      */
/*   value into the corresponding input voltage (in volts). The conversion     */
/*   accounts for an external voltage divider which scales an input range of    */
/*   5–20 V down to an acceptable range for the ADC (e.g., 0–3.3 V).           */
/*                                                                            */
/*   This software is provided free of charge.                                                    */
/*                                                                            */
/******************************************************************************/

#ifndef HAL_ADC_HAL_ADC_H_
#define HAL_ADC_HAL_ADC_H_

#include <stdint.h>

/**
 * \brief Initializes the ADC for reading two simple channels.
 *
 * \details This function sets up the ADC converter with default parameters
 *          and prepares the ADC for reading two single-ended channels, referenced
 *          to GND.
 *
 * \return void.
 */
void HAL_ADC_Init(void);

/**
 * \brief Reads the specified ADC channel.
 *
 * \details Configures and triggers a conversion on the specified ADC channel,
 *          then waits for the conversion to complete and returns the raw result.
 *
 * \param[in] channel ADC channel number (e.g., 0 or 1).
 *
 * \return A 16-bit unsigned integer representing the raw ADC conversion result.
 */
uint16_t HAL_ADC_ReadChannel(uint8_t channel);

/**
 * \brief Converts the raw ADC value to the actual input voltage.
 *
 * \details This function converts the raw ADC reading (assumed to be an 8-bit value
 *          in the range 0-255) to the corresponding voltage at the input before the
 *          voltage divider. For example, if the ADC reference is 3.3 V and the divider
 *          scales the input voltage by 0.15, the conversion is as follows:
 *          \n V_adc = (adcValue / 255.0) * 3.3
 *          \n V_in  = V_adc / 0.15
 *
 * \param[in] adcValue Raw ADC conversion result.
 *
 * \return A float representing the input voltage (in volts).
 */
float HAL_ADC_ConvertToVoltage(uint16_t adcValue);

#endif /* HAL_ADC_HAL_ADC_H_ */
