/*
 * @file name: 
 * @Descripttion: 
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-03-22 10:08:15
 * @LastEditors: zgw
 * @LastEditTime: 2021-03-22 12:05:48
 */

#ifndef __PAJ7620_H__
#define __PAJ7620_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"


// DEVICE ID
#define PAJ7620_I2C_ADDR  0x73

#define PAJ7620_ADDR_BASE				0xEF
#define PAJ_GET_INT_FLAG1               0X43
// PAJ7620_REGITER_BANK_SEL
#define PAJ7620_BANK0	0
#define PAJ7620_BANK1	1

//手势识别效果
#define BIT(x) 1<<(x)

#define GES_UP              BIT(0) //向上
#define GES_DOWM            BIT(1) //向下
#define GES_LEFT            BIT(2) //向左
#define GES_RIGHT           BIT(3) //向右
#define GES_FORWARD         BIT(4) //向前
#define GES_BACKWARD        BIT(5) //向后
#define GES_CLOCKWISE       BIT(6) //顺时针
#define GES_COUNT_CLOCKWISE BIT(7) //逆时针
#define GES_WAVE            BIT(8) //挥动


typedef struct 
{
    UCHAR_T SDA_PIN;            ///< SDA pin
    UCHAR_T SCL_PIN;            ///< SCL pin 
}PAJ7620_init_t;

VOID paj7620_init(PAJ7620_init_t* param);
UINT8_T paj7620_read_gesture_state(VOID);

#endif