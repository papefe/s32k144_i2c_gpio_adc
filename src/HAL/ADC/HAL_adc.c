/******************************************************************************/
/*                                                                            */
/*   S32K144 ADC HAL Module                                                   */
/*                                                                            */
/*   Author:  Pablo Pérez Fernández                                           */
/*   Date:    30/03/2025                                                      */
/*                                                                            */
/*   This module provides functions for initializing the ADC, reading a     */
/*   specified ADC channel, and converting the raw ADC value to the actual    */
/*   input voltage. The ADC is configured for 8-bit resolution and software   */
/*   triggering. The conversion accounts for an external voltage divider      */
/*   scaling a 5–20 V signal to an acceptable ADC input range.                */
/*                                                                            */
/*   This software is provided free of charge.                                                      */
/*                                                                            */
/******************************************************************************/

#include <HAL_adc.h>
#include "adc_driver.h"

/******************************************************************************/
/*                   Definition of local variables                            */
/******************************************************************************/
/** \brief Global variable to store the ADC converter configuration. */
static adc_converter_config_t s_adcConfig;

/******************************************************************************/
/*                      Definition of exported functions                      */
/******************************************************************************/

/**
 * \brief Initializes the ADC hardware.
 *
 * This function initializes the ADC converter configuration structure with
 * default values, modifies selected parameters (e.g., resolution, trigger mode,
 * voltage reference), configures the ADC converter instance 0 and performs
 * auto-calibration.
 *
 * \return void.
 *
 * \note The ADC is configured for 8-bit resolution and software triggering.
 */
void HAL_ADC_Init(void)
{
    /* Initialize the ADC converter configuration structure with default values */
    ADC_DRV_InitConverterStruct(&s_adcConfig);

    /* Adjust parameters if needed:
     * - Use 8-bit resolution.
     * - Use software trigger.
     * - Single conversion (non-continuous).
     * - Disable DMA.
     * - Use internal voltage reference (VREF).
     */
    s_adcConfig.resolution = ADC_RESOLUTION_8BIT;         /* 8-bit resolution */
    s_adcConfig.trigger = ADC_TRIGGER_SOFTWARE;           /* Software trigger */
    s_adcConfig.continuousConvEnable = false;             /* Single conversion mode */
    s_adcConfig.dmaEnable = false;                        /* DMA disabled */
    s_adcConfig.voltageRef = ADC_VOLTAGEREF_VREF;          /* Use VREF as internal reference */

    /* Configure the ADC converter for instance 0 */
    ADC_DRV_ConfigConverter(0, &s_adcConfig);

    /* Optional: Perform auto-calibration */
    ADC_DRV_AutoCalibration(0);
}

/**
 * \brief Reads the specified ADC channel.
 *
 * This function configures the ADC channel control structure for the given channel,
 * initiates a software-triggered conversion, waits for the conversion to complete,
 * and retrieves the conversion result.
 *
 * \param[in] channel ADC channel number (e.g., 0 or 1).
 *
 * \return The raw ADC conversion result as a 16-bit value.
 *
 */
uint16_t HAL_ADC_ReadChannel(uint8_t channel)
{
    adc_chan_config_t chanConfig;
    uint16_t result = 0U;

    /* Initialize the ADC channel configuration structure with safe defaults */
    ADC_DRV_InitChanStruct(&chanConfig);

    /* Select the ADC input channel to read (e.g., 0 or 1) */
    chanConfig.channel = channel;
    chanConfig.interruptEnable = false;   /* Use polling mode for conversion */

    /* Configure the ADC channel for instance 0 using control channel index 0 */
    ADC_DRV_ConfigChan(0, 0, &chanConfig);

    /* Trigger the conversion in software mode by enabling the pretrigger.
     * According to the driver enumeration, ADC_SW_PRETRIGGER_0 is used.
     */
    ADC_DRV_SetSwPretrigger(0, ADC_SW_PRETRIGGER_0);

    /* Wait until the conversion is complete */
    ADC_DRV_WaitConvDone(0);

    /* Retrieve the conversion result from the configured channel */
    ADC_DRV_GetChanResult(0, 0, &result);

    return result;
}

/**
 * \brief Converts the raw ADC value to the actual input voltage.
 *
 * This function converts the raw ADC value (assumed to be 8-bit, i.e., range 0-255)
 * to the input voltage in volts. It assumes:
 *  - The ADC reference voltage is 3.3 V.
 *  - An external voltage divider scales the actual input voltage (5-20 V)
 *
 * The conversion is performed as follows:
 *   V_adc = (adcValue / 255.0) * 3.3
 *   V_in  = V_adc / 0.15
 *
 * \param[in] adcValue Raw ADC conversion result.
 *
 * \return The calculated input voltage (in volts).
 *
 */
float HAL_ADC_ConvertToVoltage(uint16_t adcValue)
{
    float v_adc = ((float)adcValue / 255.0f) * 3.3f;
    float v_in = v_adc / 0.15f;
    return v_in;
}
