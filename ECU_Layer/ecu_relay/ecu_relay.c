/**
 * @file ecu_relay.c
 * @author Ahmed Hani Atef
 * @brief this file contains the interface of relay
 * @date 2023-09-07
 */


/****************** Start of Section : includes ********************/
#include "ecu_relay.h"
/******************* End of Section : includes *********************/


/************ Start of Section : function declaration **************/

std_returntype relay_initialize (const relay_config_t *__relay)
{
    std_returntype ret = STD_OK;
    if (NULL == __relay)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t __pin = {.port = __relay->port, .pin = __relay->pin, .direction = GPIO_INPUT, .logic = __relay->status};
        ret = gpio_pin_initialize(&__pin, GPIO_INPUT, __relay->status);
    }
    return  ret;
}

std_returntype relay_turn_on (const relay_config_t *__relay)
{
    std_returntype ret = STD_OK;
    if (NULL == __relay)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t __pin = {.port = __relay->port, .pin = __relay->pin, .direction = GPIO_INPUT, .logic = __relay->status};
        ret = gpio_pin_write(&__pin, GPIO_HIGH);
    }
    return  ret;
}

std_returntype relay_turn_off (const relay_config_t *__relay)
{
    std_returntype ret = STD_OK;
    if (NULL == __relay)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t __pin = {.port = __relay->port, .pin = __relay->pin, .direction = GPIO_INPUT, .logic = __relay->status};
        ret = gpio_pin_write(&__pin, GPIO_LOW);
    }
    return  ret;
}

/************ End of Section :  function declaration ***************/



/********************************************************************************
 * log
 * ******************************************************************************
 * author               date            details
 * ******************************************************************************
 * Ahmed Hani Atef      07-09-2023      - create the file
 * Ahmed Hani Atef      07-09-2023      - creating the interface of led 
 */