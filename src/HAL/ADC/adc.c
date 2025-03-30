#include "adc.h"
#include "adc_driver.h"

/* Variable global para guardar la configuración del convertidor ADC */
static adc_converter_config_t s_adcConfig;

void HAL_ADC_Init(void)
{
    /* Inicializa la estructura de configuración del ADC a valores por defecto */
    ADC_DRV_InitConverterStruct(&s_adcConfig);

    /* Ajusta los parámetros si es necesario. Por ejemplo: */
    s_adcConfig.resolution = ADC_RESOLUTION_8BIT;         /* Usamos 8 bits */
    s_adcConfig.trigger = ADC_TRIGGER_SOFTWARE;           /* Disparo por software */
    s_adcConfig.continuousConvEnable = false;             /* Conversión única */
    s_adcConfig.dmaEnable = false;
    s_adcConfig.voltageRef = ADC_VOLTAGEREF_VREF;          /* Referencia interna VREF */

    /* Configura el convertidor del ADC (se usa la instancia 0) */
    ADC_DRV_ConfigConverter(0, &s_adcConfig);

    /* Opcional: Realiza la auto-calibración */
    ADC_DRV_AutoCalibration(0);
}

uint16_t HAL_ADC_ReadChannel(uint8_t channel)
{
    adc_chan_config_t chanConfig;
    uint16_t result = 0U;

    /* Inicializa la estructura de configuración del canal con valores seguros */
    ADC_DRV_InitChanStruct(&chanConfig);

    /* Selecciona el canal de entrada que se desea leer (ej. 0 o 1) */
    chanConfig.channel = channel;
    chanConfig.interruptEnable = false;   /* Usaremos polling para la conversión */

    /* Configura el canal para la instancia 0, usando el canal índice 0.
       (En este ejemplo se asume que se usa un único canal de control; si tu ADC tiene más canales,
       deberás ajustar el índice de control según corresponda.) */
    ADC_DRV_ConfigChan(0, 0, &chanConfig);

    /* Para disparar la conversión en modo software, se activa el pretrigger */
    ADC_DRV_SetSwPretrigger(0, ADC_SW_PRETRIGGER_0);

    /* Espera a que la conversión finalice */
    ADC_DRV_WaitConvDone(0);

    /* Obtiene el resultado de la conversión del canal configurado */
    ADC_DRV_GetChanResult(0, 0, &result);

    return result;
}

float HAL_ADC_ConvertToVoltage(uint16_t adcValue)
{
    /* Ejemplo de conversión:
       - ADC de 8 bits: rango 0-255.
       - La referencia interna es 3.3V (aunque podrías usar 3.0V según tu configuración).
       - Se usa un divisor de tensión para que la señal real (5-20V) se reduzca a un rango aceptable.
         Supongamos que el divisor reduce la señal real a un 15% de su valor (0.15 factor).

       Primero, convierte el valor ADC a voltaje en la entrada del ADC:
         V_adc = (adcValue / 255.0) * 3.3
       Luego, calcula el voltaje real aplicado antes del divisor:
         V_in = V_adc / 0.15
    */
    float v_adc = ((float)adcValue / 255.0f) * 3.3f;
    float v_in = v_adc / 0.15f;
    return v_in;
}
