/* 
 * File:   ecu_push_btn.c
 * Author: Ahmed Hani Atef
 *
 * Created on September 4, 2023
 */

#include "push_btn.h"

/**
 * @brief initialize a pin as input for a push button
 * 
 * @param __btn a pointer to the push button 
 * @return std_returntype 
 * @retval (STD_OK)     : if the function run successfully
 * @retval (STD_NOT_OK) : if something goes wrong
 */
std_returntype push_btn_initialize (push_btn_config_t *__btn)
{
    std_returntype ret = STD_OK;
    if (NULL == __btn)
    {
        ret = STD_NOT_OK;
    }
    else 
    {
        pin_cofig_t btn = { .port       = __btn->port,
                            .pin        = __btn->pin,
                            .direction  = GPIO_INPUT,
                            .logic      = GPIO_LOW};

        ret = gpio_pin_direction_initialize(&btn, GPIO_INPUT);
    }

    return ret;
}

/**
 * @brief read the status of a push button
 * 
 * @note when call this function it reads the value of port register using @ref gpio_pin_read, it includes a part of code to hold the state of holding the push button
 * @param __btn a pointer to the push button 
 * @param __status a pointer to where the status will be stored
 * @return std_returntype 
 * @retval (STD_OK)     : if the function run successfully
 * @retval (STD_NOT_OK) : if something goes wrong
 */
std_returntype push_btn_read (push_btn_config_t *__btn, logic_t *__status)
{
    std_returntype ret = STD_OK;
    if ((NULL == __btn) || (NULL == __status))
    {
        ret = STD_NOT_OK;
    }
    else 
    {
        pin_cofig_t btn = { .port       = __btn->port,
                            .pin        = __btn->pin,
                            .direction  = GPIO_INPUT,
                            .logic      = GPIO_LOW};
        ret = gpio_pin_read(&btn, __status);

        logic_t __real_status = GPIO_LOW;
        do 
        {
            ret |= gpio_pin_read(&btn, __status);
            if (*__status)
            {
                __real_status = GPIO_HIGH;
            }
        }while (*__status);

        *__status = __real_status;
    }

    return ret;
}

/********************************************************************************
 * log
 * ******************************************************************************
 * author               date            details
 * ******************************************************************************
 * Ahmed Hani Atef      04-09-2023      - create the file
 * Ahmed Hani Atef      04-09-2023      - creating the interface of push button
 *                                        including the implementation 
 */