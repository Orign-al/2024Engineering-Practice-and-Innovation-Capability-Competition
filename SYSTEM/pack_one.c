#include "stm32f4xx.h"   
#include "usart.h"
#include "delay.h"

//uint8_t ZQ_data[13] = {255,255,0,9,3,42,0,0,0,0,0,0,0};
uint8_t ZQ_data[13] = {0xFF, 0xFF, 0x00, 0x09, 0x03, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void move_robot_arm_speed (uint8_t ID,uint16_t pos , uint16_t speed){
  ZQ_data[2] = ID;
  uint8_t temp_low;
  uint8_t temp_low1;
  uint8_t temp_high;
  uint8_t temp_high1;
  uint8_t check = 0;
	
  temp_low = pos&255;
  temp_high = pos/255;	
//    temp_low = pos & 0xFF; // 取低8位
//    temp_high = pos / 0xFF; // 取高8位（用0xFF进行除法）
//  
  ZQ_data[6] = temp_low;
  ZQ_data[7] = temp_high;

 temp_low1 = speed&255;
  temp_high1 = speed/255;
//	temp_low1 = speed & 0xFF;   // 取低8位
//    temp_high1 = speed / 0xFF; // 取高8位（用0xFF进行除法）
	
  ZQ_data[10] = temp_low1;
  ZQ_data[11] = temp_high1;

  for(int i =2; i<12; i++){
	check += ZQ_data[i];
  }
  if(check > 255){
	check = check&255;
  }  
  check = ~check;
  ZQ_data[12] = check;
	
 Usart_SendString(USART2,(uint8_t *)ZQ_data,13);//发送字符串
   
}



// move_robot_arm_speed 函数实现



//  各种动作函数定义
void Initial_Position() {     //初始姿势以及行走姿势
	 // 执行动作4：移动到位置 2000，速度 800
    move_robot_arm_speed(4, 3610, 1000);
    // 延时
  delay_ms(100);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(3, 998, 1000);
//    // 延时
    delay_ms(100);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(1, 2047, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(100);
//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(2,3513, 1000);
//    // 延时
  delay_ms(100);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2044, 1000);
//    // 延时
   delay_ms(100);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2212, 1000);
//    // 延时
  
}

void Preparation_to_pack(){   	//从初始姿势（行走姿势）转为要抓取的时候，在中间用

//	 // 执行动作3：移动到位置 2000，速度 800
   move_robot_arm_speed(3, 1590, 1000);
//    // 延时
   delay_ms(100);
//	 // 执行动作4：移动到位置 2000，速度 800
   move_robot_arm_speed(4, 2900, 1000);
//    // 延时
  //	 // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(2, 2048, 1000);
//    // 延时
   delay_ms(100);
  move_robot_arm_speed(6, 2039, 1000);
}

void watch_Initial_Position() {     //视觉观察的位置
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1381, 1000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3123, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2048, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1728, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 1782, 1000);
//    // 延时
   delay_ms(1000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2139, 1000);
//    // 延时
  
}

void pack_green_1() {        //抓取中间的绿色（平地抓取）阶段1
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3123, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作2：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2049, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作3：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1094, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);
//    // 执行动作4：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1193, 1000);
//    // 延时
  delay_ms(500);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2065, 1000);
//    // 延时
   delay_ms(1000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2740, 1000);
//    // 延时
}

void pack_green_2() {						//抓取中间的绿色（平地抓取）阶段2

	
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1387, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
   delay_ms(600);
			 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2080, 1000);
//    // 延时
   delay_ms(500);
		//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3600, 1000);
//    // 延时
 delay_ms(1500);		
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2633, 1000);
//    // 延时
  delay_ms(1500);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2548, 1000);     
   delay_ms(3000);
	//    // 执行动作3：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 988, 1000);

}

void pack_blue_1() {        //抓取左边的蓝色色（平地抓取）阶段1
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3123, 1000);
    // 延时
  delay_ms(500);
		 // 执行动作2：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1723, 1000);
//    // 延时
   delay_ms(500);
	//    // 执行动作4：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1432, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作3：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 988, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
   delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2174, 1000);
//    // 延时
   delay_ms(1000);    	
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2758, 1000);     
//    // 延时
}


void pack_blue_2() {						//抓取左边的蓝色（平地抓取）阶段2
		//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1394, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
   delay_ms(500);
		 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1811, 1000);
//    // 延时
   delay_ms(400);
//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3590, 1000);
//    // 延时
 delay_ms(1500);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2576, 1000);
//    // 延时
   delay_ms(1500);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2548, 1000);      
	delay_ms(3000);
	//    // 执行动作3：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 988, 1000);

}

void pack_red_1() {        //抓取左边的蓝色色（平地抓取）阶段1
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3123, 1000);
    // 延时
  delay_ms(1500);
	 // 执行动作2：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2287, 1000);
//    // 延时
    delay_ms(1500);
	//    // 执行动作4：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1489, 1000);
//    // 延时
  delay_ms(1500);
//    // 执行动作3：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 985, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2264, 1000);
//    // 延时
   delay_ms(1000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2758, 1000);       
//    // 延时
}


void pack_red_2() {						//抓取左边的蓝色（平地抓取）阶段2
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(3, 1360, 1000);
//    // 延时
   delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(2, 2368, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2610, 1000);
//    // 延时
	delay_ms(500);
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3606, 1000);
//    // 延时
  delay_ms(2000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2540, 1000);
//    // 延时
   delay_ms(3500);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(3, 988, 1000);     
 delay_ms(1000);
}


void pack_yuantai_1() {						//抓取转盘上的物块
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(1, 3123, 1000);
//    // 延时
   delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(2, 2061, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);
	//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(4, 535, 1000);
//    // 延时
  delay_ms(1000);
//	 // 执行动作1：移动到位置 2000，速度 800
	move_robot_arm_speed(3, 1786, 1000);
//    // 延时
 delay_ms(1000);

	//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2025, 1000);
//    // 延时
   delay_ms(1000);
	  move_robot_arm_speed(3, 1450, 1000);
	delay_ms(1000);
	//	 // 执行动作1：移动到位置 2000，速度 800
	move_robot_arm_speed(4, 836, 1000);
//    // 延时
 delay_ms(1000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2788, 1000);     
 delay_ms(1500);
}
