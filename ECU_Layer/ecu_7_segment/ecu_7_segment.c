/**
 * @file ecu_7_segment.c
 * @author Ahmed Hani Atef
 * @brief this file contains the interface of 7 segment display
 * @date 2023-09-08
 */

#include "ecu_7_segment.h"

std_returntype _7_segment_initialize(const _7_segment_cfg_t *__7_segment)
{
    std_returntype ret = STD_OK;
    uint8_t new_value = 0;
    pin_cofig_t __pin;
    register uint8_t counter = 0;
    uint8_t index_of_pins[] = {__7_segment->pins_cfg.led_pins.G_led,
                               __7_segment->pins_cfg.led_pins.F_led,
                               __7_segment->pins_cfg.led_pins.E_led,
                               __7_segment->pins_cfg.led_pins.D_led,
                               __7_segment->pins_cfg.led_pins.C_led,
                               __7_segment->pins_cfg.led_pins.B_led,
                               __7_segment->pins_cfg.led_pins.A_led,
                               __7_segment->pins_cfg.led_pins.DP_led};

    uint8_t index_of_ports[] = {__7_segment->ports_cfg.led_ports.G_led,
                                __7_segment->ports_cfg.led_ports.F_led,
                                __7_segment->ports_cfg.led_ports.E_led,
                                __7_segment->ports_cfg.led_ports.D_led,
                                __7_segment->ports_cfg.led_ports.C_led,
                                __7_segment->ports_cfg.led_ports.B_led,
                                __7_segment->ports_cfg.led_ports.A_led,
                                __7_segment->ports_cfg.led_ports.DP_led};
    if (NULL == __7_segment)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__7_segment->connection)
        {
        case INDIVIDUAL_PINS:

            for (counter = 0; counter < NUMBER_OF_LEDS; counter++)
            {
                __pin.port = index_of_ports[counter];
                __pin.pin = index_of_pins[counter];
                __pin.direction = GPIO_OUTPUT;

                if (counter == INDEX_OF_DP_LED)
                {
                    __pin.logic = __7_segment->dp_status;
                }
                else
                {
                    ACCESS_BIT_IN_VALUE_LED(__7_segment->value, counter, __pin.logic);
                }

                if (COMMON_CATHODE == __7_segment->type)
                {
                    ret |= gpio_pin_initialize(&__pin, GPIO_OUTPUT, __pin.logic);
                }
                else if (COMMON_ANODE == __7_segment->type)
                {
                    ret |= gpio_pin_initialize(&__pin, GPIO_OUTPUT, !(__pin.logic));
                }
                else
                {
                    ret = STD_NOT_OK;
                }
            }

            break;

        case SEQUENTIAL_PINS:
            new_value = __7_segment->value;
            EDIT_VALUE_WITH_DP_STATUS(new_value, __7_segment->dp_status);

            if (COMMON_CATHODE == __7_segment->type)
            {
                ret = gpio_port_initialize(__7_segment->ports_cfg.sequential_ports, GPIO_OUTPUT, new_value);
            }
            else if (COMMON_ANODE == __7_segment->type)
            {
                ret = gpio_port_initialize(__7_segment->ports_cfg.sequential_ports, GPIO_OUTPUT, CC_TO_CA_VALUE(new_value));
            }
            else
            {
                ret = STD_NOT_OK;
            }
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}

std_returntype _7_segment_write(const _7_segment_cfg_t *__7_segment, const _7_segment_value_t __value, const _7_segment_dp_status_t __status)
{
    std_returntype ret = STD_OK;
    uint8_t new_value = 0;
    pin_cofig_t __pin;
    register uint8_t counter = 0;
    uint8_t index_of_pins[] = {__7_segment->pins_cfg.led_pins.G_led,
                               __7_segment->pins_cfg.led_pins.F_led,
                               __7_segment->pins_cfg.led_pins.E_led,
                               __7_segment->pins_cfg.led_pins.D_led,
                               __7_segment->pins_cfg.led_pins.C_led,
                               __7_segment->pins_cfg.led_pins.B_led,
                               __7_segment->pins_cfg.led_pins.A_led,
                               __7_segment->pins_cfg.led_pins.DP_led};

    uint8_t index_of_ports[] = {__7_segment->ports_cfg.led_ports.G_led,
                                __7_segment->ports_cfg.led_ports.F_led,
                                __7_segment->ports_cfg.led_ports.E_led,
                                __7_segment->ports_cfg.led_ports.D_led,
                                __7_segment->ports_cfg.led_ports.C_led,
                                __7_segment->ports_cfg.led_ports.B_led,
                                __7_segment->ports_cfg.led_ports.A_led,
                                __7_segment->ports_cfg.led_ports.DP_led};
    if (NULL == __7_segment)
    {
        ret = STD_NOT_OK;
    }
    else
    {
        switch (__7_segment->connection)
        {
        case INDIVIDUAL_PINS:

            for (counter = 0; counter < NUMBER_OF_LEDS; counter++)
            {
                __pin.port = index_of_ports[counter];
                __pin.pin = index_of_pins[counter];
                __pin.direction = GPIO_OUTPUT;

                if (counter == INDEX_OF_DP_LED)
                {
                    __pin.logic = __status;
                }
                else
                {
                    ACCESS_BIT_IN_VALUE_LED(__value, counter, __pin.logic);
                }

                if (COMMON_CATHODE == __7_segment->type)
                {
                    ret |= gpio_pin_write(&__pin, __pin.logic);
                }
                else if (COMMON_ANODE == __7_segment->type)
                {
                    ret |= gpio_pin_write(&__pin, !(__pin.logic));
                }
                else
                {
                    ret = STD_NOT_OK;
                }
            }

            break;

        case SEQUENTIAL_PINS:
            new_value = __value;
            EDIT_VALUE_WITH_DP_STATUS(new_value, __status);

            if (COMMON_CATHODE == __7_segment->type)
            {
                ret = gpio_port_write(__7_segment->ports_cfg.sequential_ports, new_value);
            }
            else if (COMMON_ANODE == __7_segment->type)
            {
                ret = gpio_port_write(__7_segment->ports_cfg.sequential_ports,  CC_TO_CA_VALUE(new_value));
            }
            else
            {
                ret = STD_NOT_OK;
            }
            break;

        default:
            ret = STD_NOT_OK;
            break;
        }
    }
    return ret;
}