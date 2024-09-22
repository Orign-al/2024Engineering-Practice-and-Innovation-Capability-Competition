/*****************************************************************************
 ** File			: include.h
 ** Author			: Zheng23
 ** Date			: 20150608			
 ** Function		: ����ͷ�ļ�
/
*****************************************************************************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

typedef unsigned char	bool, BOOL;

typedef unsigned char	u8, U8, uint8, UINT8, BYTE;
typedef signed char		s8, S8, int8, INT8;

typedef unsigned short	u16, U16, uint16, UINT16, WORD;
typedef signed short	s16, S16, int16, INT16;

typedef unsigned long	 U32, uint32, UINT32, DWORD;
typedef signed long		 S32, int32, INT32;


typedef unsigned short	string;



//���õĺ궨��
#define BIT(n) (1<<(n))

#define     BYTE0(n)            ((unsigned char)((unsigned short)(n)))
#define     BYTE1(n)            ((unsigned char)(((unsigned short)(n))>>8))
#define     BYTE2(n)            ((unsigned char)(((unsigned short)(((unsigned long)(n))>>8))>>8))
#define     BYTE3(n)            ((unsigned char)(((unsigned short)(((unsigned long)(n))>>16))>>8))

#define TRUE   1
#define FALSE  0
#define NULL   0


#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����



#define ENCODER_MULTIPLE 4       /*��������Ƶ��ͨ����ʱ���ı�����ģʽ����*/
#define Wheel_R 65.0f//���Ӱ뾶  mm
#define PI 3.14159265358979f //Բ����
#define ENCODER_RESOLUTION 6.0f //ת����תһȦ�������� 
#define MOTOR_REDUCTION_RATIO 42.0f //���ٱ�
/*���תһȦ�ܵ�������(��ʱ���ܶ�����������) = ����������������*��������Ƶ*������ٱ� */
/* 6*1*42= 252*/
#define TOTAL_RESOLUTION ( ENCODER_RESOLUTION * ENCODER_MULTIPLE * MOTOR_REDUCTION_RATIO ) 

#define MPN (2*PI*Wheel_R)/(ENCODER_RESOLUTION*MOTOR_REDUCTION_RATIO) //һ�������߹���ֱ�߾���(�����ı�ƵMPN (2*PI*Wheel_R)/(4*NPN*Motor_i))(��λ:mm/s)
// #define T 100 //���������ʱ��(10e-3s) 1ms

#define Left_motor     8
#define Right_motor    2

#define POSITION_DEADBAND 10  // 位置死区，单位为圈
#define INTEGRAL_SEPARATOR 30  // 积分分离阈值，单位为圈
#define MOTOR_COUNT 4




//#include ""
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_can.h"
#include "stm32f4xx_usart.h"
#include "Delay.h"
//#include "HardI2C.h"
#include "OLED.h"

#include "pack_one.h"
#include "action.h"
#include "m2006driver.h"
#include "FineTune.h"

//#include "MPU6050.h"
//#include "MPU6050_Reg.h"
//#include "dmpKey.h"
//#include "dmpmap.h"
//#include "LED.h"

#include <stdint.h>
#include <string.h>
////#include "mpu6050.h"

//#include "inv_mpu_dmp_motion_driver.h"
//#include "inv_mpu.h"

////#include "MPU6050_Reg.h"
//#include "filter.h"

//#include "IIC.h"
#include "Motor.h"
#include "Move.h"
#include "Encoder.h"
#include "PID.h"
//#include "Timer.h"
#include "usart.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "wit_c_sdk.h"
#include "REG.h"






























#endif

