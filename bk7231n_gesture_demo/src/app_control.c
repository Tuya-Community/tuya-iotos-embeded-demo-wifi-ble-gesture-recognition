/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: sht21.h
 * @Description: SHT21 IIC drive src file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2020-12-16 18:51:29
 * @LastEditTime: 2021-03-22 15:37:39
 */

#include "app_control.h"
#include "tuya_gpio.h"
#include "tuya_uart.h"
#include "BkDriverUart.h"
#include "sys_timer.h"
#include "uni_time.h"
#include "PAJ7620.h"
#include "app_gesture.h"
/***********************************************************
*************************types define***********************
***********************************************************/
typedef enum
{
    LOW = 0,
    HIGH,
}default_level;

APP_CTRL_DATA_T app_ctrl_data = {0};

/***********************************************************
*************************IO control device define***********
***********************************************************/

/***********************************************************
*************************about adc init*********************
***********************************************************/
#define IIC_SDA_PIN                         (6)
#define IIC_SCL_PIN                         (7)

STATIC PAJ7620_init_t paj7620_init_param = {IIC_SDA_PIN, IIC_SCL_PIN};


/***********************************************************
*************************about iic init*********************
***********************************************************/

/***********************************************************
*************************function***************************
***********************************************************/

STATIC VOID __ctrl_gpio_init(CONST TY_GPIO_PORT_E port, CONST BOOL_T high)
{   
    //Set IO port as output mode
    tuya_gpio_inout_set(port, FALSE);
    //Set IO port level
    tuya_gpio_write(port, high);
}


VOID app_device_init(VOID)
{

    paj7620_init(&paj7620_init_param);
    tuya_hal_system_sleep(500);
}



VOID app_ctrl_handle(VOID)
{   
    app_ctrl_data.gesture_state = paj7620_read_gesture_state();
    if(app_ctrl_data.gesture_state != app_ctrl_data.gesture_state_old) {
        PR_NOTICE("------------gesture state = %d------------",app_ctrl_data.gesture_state);
        app_report_all_dp_status();
    }
    app_ctrl_data.gesture_state_old = app_ctrl_data.gesture_state_old;
}

VOID app_ctrl_all_off(VOID)
{   

}

 