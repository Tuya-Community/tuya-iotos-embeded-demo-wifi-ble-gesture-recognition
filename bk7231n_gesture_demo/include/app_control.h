/*
 * @file name: 
 * @Descripttion: 
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-03-01 10:44:58
 * @LastEditors: zgw
 * @LastEditTime: 2021-03-22 15:29:55
 */
#ifndef __APP_CONTROL_H__
#define __APP_CONTROL_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"

typedef enum {
    none = 0,
    up,
    down,
    left,
    right,
    forward,
    backward,
    clockwise,
    count_clockwise,
}gesture_state_t;

typedef struct {
    gesture_state_t gesture_state;
    gesture_state_t gesture_state_old;
}APP_CTRL_DATA_T;

/********************************************************************************
 * FUNCTION:       plant_device_init
 * DESCRIPTION:    device initialization
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_device_init(VOID);

/********************************************************************************
 * FUNCTION:       plant_get_adc_sensor_data
 * DESCRIPTION:    Get ADC sensor data
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_get_sensor_data(VOID);

/********************************************************************************
 * FUNCTION:       plant_ctrl_handle
 * DESCRIPTION:    sensor data deal handle
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_ctrl_handle(VOID);

/********************************************************************************
 * FUNCTION:       plant_ctrl_all_off
 * DESCRIPTION:    Close all control components
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_ctrl_all_off(VOID);

#endif