#include "stm32f4xx.h"   
#include "usart.h"
#include "delay.h"

//uint8_t data[13] = {255,255,0,9,3,42,0,0,0,0,0,0,0};
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

void initial_pos() {  
move_robot_arm_speed(1,3146, 2000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(2, 3359, 2000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(3, 1507, 2000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(4, 3814, 2000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 3524, 2000);
//    // 延时
   delay_ms(1000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2186, 2000);
//    // 延时
	
}


void watch_Initial_Position1() {     //机械臂前伸，视觉（转盘）
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1736, 2000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3115, 2000);
    // 延时
  delay_ms(50);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2033, 2000);
//    // 延时
    delay_ms(100);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1687, 2000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(300);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2015, 2000);
//    // 延时
   delay_ms(100);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2186, 2000);
//    // 延时
  
}

void watch_Initial_Position2() {     //机械臂前伸，视觉（平地）
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,2048, 1000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1065, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2100, 1000);
//    // 延时
    delay_ms(1000);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1498, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2142, 1000);
//    // 延时
   delay_ms(1000);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2186, 2000);
//    // 延时
  
}

void pick_yuantai() {     //在转盘处的抓取

	    move_robot_arm_speed(3, 2034, 2000);
		delay_ms(100);
		move_robot_arm_speed(4, 591, 2000);
		delay_ms(300);
	
	
	
		move_robot_arm_speed(3, 1645, 2000);
		delay_ms(500);
		move_robot_arm_speed(4, 889, 2000);
		delay_ms(200);
		move_robot_arm_speed(6, 3100, 2000);
}

void put_zhongjian() {     //放转盘上绿色到车上
			//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3610, 2000);
//    // 延时
  delay_ms(50);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2190, 2000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1542, 2000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2560, 2000);
//    // 延时
   delay_ms(1800);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2860, 2000);
//    // 延时
  
}

void put_zuobian() {     //放转盘上红色到车上
			//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3618, 2000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3115, 2000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2494, 2000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1542, 2000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2563, 2000);
//    // 延时
   delay_ms(1800);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2860, 2000);
//    // 延时
  
  
}

void put_youbian() {     //放转盘上蓝色的到车上
		//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3618, 2000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3115, 2000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1770, 2000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1542, 2000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2563, 2000);
//    // 延时
   delay_ms(1800);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2860, 2000);
//    // 延时
  
}



void pick_car_zhong() {     //抓取
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1065, 1000);
    // 延时
  delay_ms(500);
   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2673, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3618, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1504, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(800);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2116, 1000);
//    // 延时
    delay_ms(500);



 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3100, 1000);
//    // 延时
}


void pick_car_zuo() {     //机械臂前伸，视觉（平地）
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1065, 1000);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2481, 1000);
//    // 延时
    delay_ms(50);

   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2581, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3614, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1454, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3100, 1000);
//    // 延时
}


void pick_car_you() {     //机械臂前伸，视觉（平地）
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1065, 1000);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1758, 1000);
//    // 延时
    delay_ms(50);

   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2581, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3614, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1454, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3100, 1000);
//    // 延时
}


void put_zhongjian_car_out() {     //机械臂前伸，视觉（平地）
	//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(2, 2013, 300);
	delay_ms(2500);
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1266, 300);
//    // 延时
  delay_ms(2500);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(5, 2233, 300);
    // 延时
  delay_ms(2500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(3, 1550, 300);
//    // 延时
    delay_ms(2500);
	   move_robot_arm_speed(3, 1155, 300);
//    // 延时
    delay_ms(2500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(4, 1251, 300);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(2500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2040, 300);
//    // 延时
   delay_ms(2000);


//    // 延时
  
}

void put_zuobian_car_out() {     //机械臂前伸，视觉（平地）
	//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(4, 1526, 1000);
	delay_ms(200);
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(5,2280, 1000);
//    // 延时
  delay_ms(200);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(3, 1560, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1690, 1000);
//    // 延时
    delay_ms(500);
	   move_robot_arm_speed(4, 1458, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1129, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);
 move_robot_arm_speed(6, 2050, 1000);
//	


//    // 延时
  
}

void put_youbian_car_out() {     //机械臂前伸，视觉（平地）
	//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(4, 1526, 1000);
	delay_ms(200);
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(5,2280, 1000);
//    // 延时
  delay_ms(200);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(3, 1560, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2279, 1000);
//    // 延时
    delay_ms(500);
	   move_robot_arm_speed(4, 1458, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1129, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);
 move_robot_arm_speed(6, 2050, 1000);
//	


//    // 延时
  
}

void put_zhong_car_out() {     //机械臂前伸，视觉（平地）
	//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(2, 1956, 1000);
	delay_ms(500);
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(3,1850, 1000);
//    // 延时
  delay_ms(500);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(5, 2033, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(4, 921, 1000);
//    // 延时
    delay_ms(500);
	   move_robot_arm_speed(3, 1164, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(4, 1240, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2038, 1000);
//    // 延时
   delay_ms(200);
	move_robot_arm_speed(6, 2038, 1000);

//    // 延时
  
}

void pick_zhong_move_zuo() {     //机械臂前伸，视觉（平地）

	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1654, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整

}
