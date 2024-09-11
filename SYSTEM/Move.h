#ifndef _MOVE_H_
#define _MOVE_H_


typedef struct 
{
    int moter_speed_1;
    int moter_speed_2;
    int moter_speed_3;
    int moter_speed_4;
}Move_moter_speed;

void Move_line(float vy, float vx,float omega,float r);




#endif

