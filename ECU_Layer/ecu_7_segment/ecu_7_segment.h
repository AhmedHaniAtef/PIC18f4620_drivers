/**
 * @file ecu_7_segment.h
 * @author Ahmed Hani Atef
 * @brief this file contains the interface of 7 segment display 
 * @date 2023-09-07
 */



#ifndef ECU_7_SEGMENT_H
#define ECU_7_SEGMENT_H


/****************** Start of Section : includes ********************/
#include "../../MCAL_Layer/hal_gpio/hal_gpio.h"
#include "ecu_7_segment_cfg.h"
/******************* End of Section : includes *********************/


/************** Start of Section : Macro defines *****************/

#define INDEX_OF_DP_LED (7)
#define NUMBER_OF_LEDS  (8)

/*************** End of Section : Macro defines ******************/


/************** Start of Section : Macro functions *****************/

#define CC_TO_CA_VALUE(_val)                                                ((_val ^ (0xFF)))
#define EDIT_VALUE_WITH_DP_STATUS(__val , __dp_status)                      (__val |= ((__dp_status) << 7))
#define ACCESS_BIT_IN_VALUE_LED(__val , __bit_position , __new_val)         (__new_val = ((__val) & (1 << (__bit_position))) >> (__bit_position))
#define ACCESS_BIT_IN_VALUE_LED_TOGGLED(__val , __bit_position , __new_val) (__new_val = !(((__val) & (1 << (__bit_position))) >> (__bit_position)))

/*************** End of Section : Macro functions ******************/


/*************** Start of Section : new data types *****************/

#ifdef NORMAL_7_SEG
typedef enum 
{
    COMMON_ANODE = 0,
    COMMON_CATHODE,
}_7_segment_type_t;

typedef enum
{
    INDIVIDUAL_PINS = 0,
    SEQUENTIAL_PINS,
}_7_segment_connection_t;

typedef enum 
{
    DECIMAL_POINT_OFF = 0,
    DECIMAL_POINT_ON,
}_7_segment_dp_status_t;

typedef enum
{
    VALUE_0 = 0x7E,
    VALUE_1 = 0x30,
    VALUE_2 = 0x6D,
    VALUE_3 = 0x79,
    VALUE_4 = 0x33,
    VALUE_5 = 0x5B,
    VALUE_6 = 0x5F,
    VALUE_7 = 0x70,
    VALUE_8 = 0x7F,
    VALUE_9 = 0x7B,
    VALUE_A = 0x77,
    VALUE_B = 0x1F,
    VALUE_C = 0x4E,
    VALUE_D = 0x3D,
    VALUE_E = 0x4F,
    VALUE_F = 0x47,
}_7_segment_value_t;

typedef struct
{
    uint8_t DP_led  : 3;
    uint8_t A_led   : 3;
    uint8_t B_led   : 3;
    uint8_t C_led   : 3;
    uint8_t D_led   : 3;
    uint8_t E_led   : 3;
    uint8_t F_led   : 3;
    uint8_t G_led   : 3;
}led_ports_t;  

typedef struct
{
    uint8_t DP_led  : 3;
    uint8_t A_led   : 3;
    uint8_t B_led   : 3;
    uint8_t C_led   : 3;
    uint8_t D_led   : 3;
    uint8_t E_led   : 3;
    uint8_t F_led   : 3;
    uint8_t G_led   : 3;
}led_pins_t;

typedef union 
{
    led_ports_t led_ports;
    uint8_t sequential_ports ; // here there is a reserved bit     
}_7_segment_ports_cfg_t;

typedef union 
{
    led_pins_t led_pins;
    uint8_t sequential_pins ; // here there is a reserved bit     
}_7_segment_pins_cfg_t;

typedef struct 
{
    _7_segment_ports_cfg_t ports_cfg;
    _7_segment_pins_cfg_t pins_cfg;

    uint8_t value       : 8; // because of the value enum i should make value of 8 bit but in future enhancement it could be only 7 bit
    uint8_t type        : 4; // here there is a reserved 3 bit 
    uint8_t dp_status   : 3; // here there is a reserved 2 bit 
    uint8_t connection  : 1;

}_7_segment_cfg_t;

#endif
/****************** End of Section :new data types *****************/


/************ Start of Section : function declaration **************/
std_returntype _7_segment_initialize (const _7_segment_cfg_t *__7_segment);
std_returntype _7_segment_write(const _7_segment_cfg_t *__7_segment, const _7_segment_value_t __value, const _7_segment_dp_status_t __status);
/************ End of Section :  function declaration ***************/



#endif // ECU_7_SEGMENT_H

/********************************************************************************
 * log
 * ******************************************************************************
 * author               date            details
 * ******************************************************************************
 * Ahmed Hani Atef      07-09-2023      - create the file
 * Ahmed Hani Atef      07-09-2023      - creating the interface of 7 segment
 */
