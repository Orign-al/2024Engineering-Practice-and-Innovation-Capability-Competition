#ifndef _pack_one_H_
#define _pack_one_H_

#include "stm32f4xx.h" 

// 全局数据数组
extern uint8_t ZQ_data[13];
extern void move_robot_arm_speed (void);
extern void watch_Initial_Position1(void);
extern void watch_Initial_Position2(void);

extern void put_zhongjian (void);
extern void put_zuobian(void);
extern void pick_yuantai(void);

extern void put_youbian (void);
extern void pick_car_zhong(void);
extern void pick_car_zuo(void);

extern void pick_car_you (void);
extern void put_zhongjian_car_out(void);
extern void put_zuobian_car_out(void);

extern void put_youbian_car_out (void);
extern void put_zhong_car_out(void);

extern void pick_zhong_move_zuo(void);


#endif


