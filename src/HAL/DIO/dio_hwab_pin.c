/*
 * dio_hwab_pin.c
 *
 *  Created on: 30 mar. 2025
 *      Author: pabper3710
 */

#include "dio_hwab_pin.h"
#include "conf.h"  // Aquí se encuentran las definiciones PIN_DIO_1, etc.

/*
  Mapeo lógico:
  - PIN_DIO_1 (80U)  -> PTC7
  - PIN_DIO_2 (81U)  -> PTC6
  - PIN_DIO_3 (63U)  -> PTB17
  - PIN_DIO_4 (66U)  -> PTB14
  - PIN_DIO_5 (65U)  -> PTB15
  - PIN_DIO_6 (64U)  -> PTB16
  - PIN_DIO_7 (46U)  -> PTC14
  - PIN_DIO_8 (29U)  -> PTC3
  Ajusta estos valores según la asignación física en tu placa.
*/
const dio_hwab_pin_t dio_hwab_pin[] = {
    { PIN_DIO_1, PORTC, 7U, PTC },
    { PIN_DIO_2, PORTC, 6U, PTC },
    { PIN_DIO_3, PORTB, 17U, PTB },
    { PIN_DIO_4, PORTB, 14U, PTB },
    { PIN_DIO_5, PORTB, 15U, PTB },
    { PIN_DIO_6, PORTB, 16U, PTB },
    { PIN_DIO_7, PORTC, 14U, PTC },
    { PIN_DIO_8, PORTC, 3U, PTC }
};

