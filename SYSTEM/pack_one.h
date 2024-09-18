#ifndef _pack_one_H_
#define _pack_one_H_

#include "stm32f4xx.h" 

// 全局数据数组
extern uint8_t data[13];
extern void move_robot_arm_speed (void);
extern void Initial_Position (void);
extern void watch_Initial_Position1(void);
extern void watch_Initial_Position2(void);
extern void pack_green_1(void);
extern void pack_green_2(void);
extern void pack_blue_1(void);
extern void pack_blue_2(void);
extern void pack_red_1(void);
extern void pack_red_2(void);
extern void Preparation_to_pack(void);
extern void pack_yuantai_1(void);



#endif


