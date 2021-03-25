/*
 * @file name: 
 * @Descripttion: 
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-03-22 10:08:33
 * @LastEditors: zgw
 * @LastEditTime: 2021-03-22 15:21:28
 */

#include "PAJ7620.h"
#include "soc_i2c.h"

CONST UCHAR_T PAJ7620Global_InitArray[][2] ={
    {0xEF,0x00},
	{0x37,0x07},
    {0x38,0x17},
	{0x39,0x06},
	{0x41,0x00},
	{0x42,0x00},
	{0x46,0x2D},
	{0x47,0x0F},
	{0x48,0x3C},
	{0x49,0x00},
	{0x4A,0x1E},
	{0x4C,0x20},
	{0x51,0x10},
	{0x5E,0x10},
	{0x60,0x27},
	{0x80,0x42},
	{0x81,0x44},
	{0x82,0x04},
	{0x8B,0x01},
	{0x90,0x06},
	{0x95,0x0A},
	{0x96,0x0C},
	{0x97,0x05},
	{0x9A,0x14},
	{0x9C,0x3F},
	{0xA5,0x19},
	{0xCC,0x19},
	{0xCD,0x0B},
	{0xCE,0x13},
	{0xCF,0x64},
	{0xD0,0x21},
	{0xEF,0x01},
	{0x02,0x0F},
	{0x03,0x10},
	{0x04,0x02},
	{0x25,0x01},
	{0x27,0x39},
	{0x28,0x7F},
	{0x29,0x08},
	{0x3E,0xFF},
	{0x5E,0x3D},
	{0x65,0x96},
	{0x67,0x97},
	{0x69,0xCD},
	{0x6A,0x01},
	{0x6D,0x2C},
	{0x6E,0x01},
	{0x72,0x01},
	{0x73,0x35},
	{0x74,0x00},
	{0x77,0x01},
};


CONST UCHAR_T PAJ7620Gesture_InitArray[][2] ={
	{0xEF,0x00},
	{0x41,0x00},
	{0x42,0x00},
	{0xEF,0x00},
	{0x48,0x3C},
	{0x49,0x00},
	{0x51,0x10},
	{0x83,0x20},
	{0x9F,0xF9},
	{0xEF,0x01},
	{0x01,0x1E},
	{0x02,0x0F},
	{0x03,0x10},
	{0x04,0x02},
	{0x41,0x40},
	{0x43,0x30},
	{0x65,0x96},
	{0x66,0x00},
	{0x67,0x97},
	{0x68,0x01},
	{0x69,0xCD},
	{0x6A,0x01},
	{0x6B,0xB0},
	{0x6C,0x04},
	{0x6D,0x2C},
	{0x6E,0x01},
	{0x74,0x00},
	{0xEF,0x00},
	{0x41,0xFF},
	{0x42,0x01},
};


STATIC int __iic_start(VOID)
{
    vI2CSDASet();
    vI2CSCLSet();

    vI2CDelay(5);

    vI2CSDAReset();

    vI2CDelay(5);

    vI2CSCLReset();

    return 0;
}


STATIC int __iic_stop(VOID)
{   
    vI2CSCLReset();
    vI2CSDAReset();

    vI2CDelay(5);
    
    vI2CSCLSet();
    vI2CSDASet();

    vI2CDelay(5);

    return 0;      
}


STATIC VOID __iic_send_ack(VOID)
{   
    vI2CSCLReset();
        
    vI2CSDAReset();

    vI2CDelay(2);
    vI2CSCLSet();

    vI2CDelay(2);

    vI2CSCLReset();
}

STATIC VOID __iic_send_nack(VOID)
{   
    vI2CSCLReset();
        
    vI2CSDASet();

    vI2CDelay(2);
    vI2CSCLSet();

    vI2CDelay(2);

    vI2CSCLReset();
}

STATIC UINT8_T __iic_recv_ack(VOID)
{   
    UINT8_T ucErrTime=0;
    UINT8_T recv_ack;
    vI2CSDARelease();
    vI2CSCLSet();
    vI2CDelay(5);
    
    while(ucI2CSDAInputRead()) {
        ucErrTime++;
        if(ucErrTime>250) {
			__iic_stop();
            PR_NOTICE("-------iic ack error-----");
			return 1;
		}
    }

    
    vI2CSCLReset();

    return 0;
}

STATIC VOID __iic_send_byte(UCHAR_T sendbyte)
{
    UCHAR_T i = 0;
    vI2CSCLReset;
    for(i = 0x80; i > 0; i >>= 1)
    {
        if((sendbyte & i) == 0) {
            vI2CSDAReset();
        } else {
            vI2CSDASet();
        }
        vI2CDelay(2);   
        vI2CSCLSet();
        vI2CDelay(2); //vI2CDelay(5);
        vI2CSCLReset();
        vI2CDelay(2);
    }
}

STATIC UINT8_T __iic_read_byte(UCHAR_T ack)
{
    UCHAR_T i = 0;
    
    UCHAR_T readbyte = 0;
    vI2CSDARelease();
    for(i = 0x80; i > 0; i >>= 1)
    {
        vI2CSCLReset();
        vI2CDelay(2);
        vI2CSCLSet();
        if(ucI2CSDAInputRead()) {
            readbyte |= i;    
        }
        vI2CDelay(2);
    }
    if(!ack) {
        __iic_send_nack(); 
    }else {
        __iic_send_ack();
    }
    
    return readbyte;    
}

VOID paj7620_iic_write(UINT8_T drv_addr, UINT8_T reg_addr, UINT8_T reg_data)
{   
	__iic_start();
	__iic_send_byte((drv_addr << 1));	   //发送从机地址写命令
	__iic_recv_ack();
	__iic_send_byte(reg_addr);
	__iic_recv_ack();
    __iic_send_byte(reg_data);
	__iic_recv_ack();
    __iic_stop();
}

VOID paj7620_iic_read(UINT8_T drv_addr, UINT8_T reg_addr, UINT8_T *p_data)
{   
	__iic_start();
	__iic_send_byte((drv_addr << 1) | 0x00);	   //发送从机地址写命令
	__iic_recv_ack();
	__iic_send_byte(reg_addr);
	__iic_recv_ack();
    __iic_send_byte((drv_addr << 1) | 0x01);
	__iic_recv_ack();
    *p_data = __iic_read_byte(1);
    __iic_stop();
}

VOID paj7620_wake_up(VOID)
{
    UINT8_T data = 0x0a;

    UINT8_T i =0;
    __iic_start();
    __iic_send_byte(PAJ7620_I2C_ADDR << 1);
    __iic_stop();
    vI2CDelay(1000);
    __iic_start();
    __iic_send_byte(PAJ7620_I2C_ADDR << 1);
    __iic_stop();
    paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620_ADDR_BASE,PAJ7620_BANK0);
    paj7620_iic_read(PAJ7620_I2C_ADDR, 0x00, &data);
    if(data!= 0x20) {
        PR_NOTICE("PAJ7620 init failed");
    }
}

UINT16_T paj7620_get_data(UINT8_T reg_addr)
{   
    UINT8_T i = 0;
    UINT8_T data;
	__iic_start();
	__iic_send_byte((PAJ7620_I2C_ADDR << 1) | 0x00);	   //发送从机地址写命令
	__iic_recv_ack();
	__iic_send_byte(reg_addr);
	__iic_recv_ack();
    __iic_start();
    __iic_send_byte((PAJ7620_I2C_ADDR << 1) + 1);
    __iic_recv_ack();

    data = __iic_read_byte(0);
    
    __iic_stop();

    paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620_ADDR_BASE,PAJ7620_BANK0);

    return data; 
}


VOID paj7620_init(PAJ7620_init_t* param)
{
    UINT8_T flag;
    UINT8_T i;

    i2c_pin_t i2c_config = {
        .ucSDA_IO = param ->SDA_PIN,
        .ucSCL_IO = param ->SCL_PIN,
    };
    
    opSocI2CInit(&i2c_config);          /* SDA&SCL GPIO INIT */
    vI2CDelay(100);

    paj7620_wake_up();
    paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620_ADDR_BASE,PAJ7620_BANK0);

    for(i = 0; i < 51; i++) {
        paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620Global_InitArray[i][0], PAJ7620Global_InitArray[i][1]);
    }

    paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620_ADDR_BASE,PAJ7620_BANK0);

    paj7620_wake_up();
    paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620_ADDR_BASE,PAJ7620_BANK0);

    for(i = 0; i < 30; i++) {
        paj7620_iic_write(PAJ7620_I2C_ADDR,PAJ7620Gesture_InitArray[i][0], PAJ7620Gesture_InitArray[i][1]);
    }

}

UINT8_T paj7620_read_gesture_state(VOID)
{
    switch (paj7620_get_data(PAJ_GET_INT_FLAG1))
    {
    case GES_UP://向上
        return 1;
    case GES_DOWM://向下
        return 2;
    case GES_LEFT://向左
        return 3;
    case GES_RIGHT://向右
        return 4;
    case GES_FORWARD://向前
        return 5;
    case GES_BACKWARD: //向后
        return 6;
    case GES_CLOCKWISE://顺时针
        return 7;
    case GES_COUNT_CLOCKWISE://逆时针
        return 8;
    case GES_WAVE://挥动
        return 9;
    default:
        return 0;
    }
}
