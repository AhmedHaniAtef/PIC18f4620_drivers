/**
 * @file ecu_relay.h
 * @author Ahmed Hani Atef
 * @brief this file contains the interface of relay
 * @date 2023-09-07
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/****************** Start of Section : includes ********************/
#include "../../MCAL_Layer/hal_gpio/hal_gpio.h"
/******************* End of Section : includes *********************/

/*************** Start of Section : new data types *****************/

typedef enum 
{
    RELAY_OFF = 0,
    RELAY_ON
}relay_status_t;

typedef struct 
{
    uint8_t port : 4;
    uint8_t pin  : 3;
    uint8_t status : 1;
}relay_config_t;


/****************** End of Section :new data types *****************/



/************ Start of Section : function declaration **************/

std_returntype relay_initialize (const relay_config_t *__relay);
std_returntype relay_turn_on (const relay_config_t *__relay);
std_returntype relay_turn_off (const relay_config_t *__relay);

/************ End of Section :  function declaration ***************/


#endif	/* ECU_RELAY_H */

/********************************************************************************
 * log
 * ******************************************************************************
 * author               date            details
 * ******************************************************************************
 * Ahmed Hani Atef      07-09-2023      - create the file
 * Ahmed Hani Atef      07-09-2023      - creating the interface of led 
 */
