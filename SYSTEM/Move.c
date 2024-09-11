#include "include.h"

extern Move_moter_speed Move_moters_speed;

int vy_hold,vx_hold;

//vx:the speed on x
//vy:the speed on y
//omega: yhe speed 
//
//
void Move_line(float vy, float vx,float omega,float r)
{
	int speed_A,speed_B,speed_C,speed_D;



	speed_A = (int16_t)(vy - vx + omega * r)  ; // ???
    speed_B = (int16_t)(vy + vx - omega * r); // ???
    speed_C = -(int16_t)(vy - vx + omega * r); // ???
    speed_D = -(int16_t)(vy + vx - omega * r); // ???

	
	
	Move_moters_speed.moter_speed_1 = speed_A;
	Move_moters_speed.moter_speed_2 = speed_B;
	Move_moters_speed.moter_speed_3 = speed_C;
	Move_moters_speed.moter_speed_4 = speed_D;



}


