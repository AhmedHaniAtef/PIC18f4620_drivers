/* 
 * File:   ecu_led.c
 * Author: Ahmed Hani Atef
 *
 * Created on September 2, 2023
 */

#include "ecu_led.h"


/**
 * @brief initialize the pin to be as output for an external led 
 * 
 * @param __led a pointer to the led which include the index of the pin in a specific port
 * @return std_returntype
 * @retval (STD_OK)     : if the function run successfully
 * @retval (STD_NOT_OK) : if something goes wrong
 */
std_returntype led_initialize (led_config_t *__led)
{
    std_returntype ret = STD_OK;

    if (NULL == __led)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t led = { .port = __led->port,
                            .pin = __led->pin,
                            .direction = GPIO_OUTPUT,
                            .logic = __led->status};
        
        ret = gpio_pin_initialize(&led, GPIO_OUTPUT, __led->status);
    }

    return ret;
}

/**
 * @brief turn on the led
 * 
 * @param __led a pointer to the led which include the index of the pin in a specific port
 * @return std_returntype
 * @retval (STD_OK)     : if the function run successfully
 * @retval (STD_NOT_OK) : if something goes wrong
 */
std_returntype led_turn_on (led_config_t *__led)
{
    std_returntype ret = STD_OK;

    if (NULL == __led)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t led = { .port       = __led->port,
                            .pin        = __led->pin,
                            .direction  = GPIO_OUTPUT,
                            .logic      = __led->status};
        
        ret = gpio_pin_write(&led, GPIO_HIGH);
    }

    return ret;
}

/**
 * @brief turn off the led
 * 
 * @param __led a pointer to the led which include the index of the pin in a specific port
 * @return std_returntype
 * @retval (STD_OK)     : if the function run successfully
 * @retval (STD_NOT_OK) : if something goes wrong
 */
std_returntype led_turn_off (led_config_t *__led)
{
    std_returntype ret = STD_OK;

    if (NULL == __led)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t led = { .port       = __led->port,
                            .pin        = __led->pin,
                            .direction  = GPIO_OUTPUT,
                            .logic      = __led->status};
        
        ret = gpio_pin_write(&led, GPIO_LOW);
    }

    return ret;
}

/**
 * @brief toggle the status of the led
 * 
 * @param __led a pointer to the led which include the index of the pin in a specific port
 * @return std_returntype
 * @retval (STD_OK)     : if the function run successfully
 * @retval (STD_NOT_OK) : if something goes wrong
 */
std_returntype led_turn_toggle (led_config_t *__led)
{
    std_returntype ret = STD_OK;

    if (NULL == __led)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        pin_cofig_t led = { .port       = __led->port,
                            .pin        = __led->pin,
                            .direction  = GPIO_OUTPUT,
                            .logic      = __led->status};
        
        ret = gpio_pin_toggle(&led);
    }

    return ret;
}

/********************************************************************************
 * log
 * ******************************************************************************
 * author               date            details
 * ******************************************************************************
 * Ahmed Hani Atef      02-09-2023      - create the file
 * Ahmed Hani Atef      04-09-2023      - creating the interface of led module 
 *                                        including the implementation.
 */
