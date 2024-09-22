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
move_robot_arm_speed(1,3146, 1000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(2, 3359, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(3, 1507, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(4, 3814, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 3524, 1000);
//    // 延时
   delay_ms(1000);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2186, 1000);
//    // 延时
	
}


void watch_Initial_Position1() {     //机械臂前伸，视觉（转盘）
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,1736, 1500);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3115, 1500);
    // 延时
  delay_ms(50);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2033, 1500);
//    // 延时
    delay_ms(100);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1687, 1500);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(300);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2224, 1500);
//    // 延时
   delay_ms(100);
//	 // 执行动作6：移动到位置 2000，速度 800
   move_robot_arm_speed(6, 2186, 1500);
//    // 延时
  
}

void watch_Initial_Position2() {     //机械臂前伸，视觉（平地）
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,2048, 1000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1010, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2077, 1000);
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
   move_robot_arm_speed(6, 2186, 1000);
//    // 延时
  
}

void watch_Initial_Position3() {     //机械臂前伸，视觉（侧面平地）
	//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,2048, 1000);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 2062, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2077, 1000);
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
   move_robot_arm_speed(6, 2186, 1000);
//    // 延时
  
}

void pick_yuantai() {     //在转盘处的抓取

	    move_robot_arm_speed(3, 2034, 2000);
		delay_ms(500);
		move_robot_arm_speed(4, 591, 2000);
		delay_ms(500);
		move_robot_arm_speed(3, 1820, 2000);
		delay_ms(500);
		move_robot_arm_speed(4, 795, 2000);
		delay_ms(400);
		move_robot_arm_speed(6, 3150, 2500);
		delay_ms(400);
}

void put_zhongjian() {     //放转盘上绿色到车上
			//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3610, 1500);
//    // 延时
  delay_ms(50);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2190, 1500);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1542, 1500);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2560, 1500);
//    // 延时
   delay_ms(1700);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2930, 1500);
//    // 延时
  
}

void put_zuobian() {     //放转盘上红色到车上
			//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3613, 1500);
//    // 延时
  delay_ms(50);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2568, 1000);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1478, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2515, 1000);
//    // 延时
   delay_ms(1500);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2930, 1000);
//    // 延时
  
  
}

void put_youbian() {     //放转盘上蓝色的到车上
		//    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3611, 1500);
//    // 延时
  delay_ms(50);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 3115, 1300);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1770, 1300);
//    // 延时
    delay_ms(500);
//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1480, 1300);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(500);

//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2515, 1500);
//    // 延时
   delay_ms(1500);
//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 2930, 1000);
//    // 延时
  
}



void pick_car_zhong() {     //抓取绿色
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1010, 1000);
    // 延时
  delay_ms(500);
   move_robot_arm_speed(6, 2960, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2618, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3621, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1524, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(800);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2119, 1000);
//    // 延时
    delay_ms(2000);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3100, 1000);
//    // 延时
}


void pick_car_zuo() {     //机械臂前伸，视觉（平地）
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1020, 1000);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2481, 1000);
//    // 延时
    delay_ms(50);

   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2491, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3614, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1503, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3150, 1000);
//    // 延时
}


void pick_car_you() {     //机械臂前伸，视觉（平地）
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 1020, 1000);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1758, 1000);
//    // 延时
    delay_ms(50);

   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2485, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3611, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1500, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3150, 1000);
//    // 延时
}


void put_zhongjian_car_out() {     //机械臂前伸，视觉（平地）
	//	 // 执行动作6：移动到位置 200，速度 800
		//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(1, 1010, 1500);
   move_robot_arm_speed(2, 2077, 1500);
	move_robot_arm_speed(4, 953, 1500);
  delay_ms(500);
	move_robot_arm_speed(3, 1982, 1500);
  delay_ms(500);	
	
	move_robot_arm_speed(5, 1861, 1500);  //1861
  delay_ms(500);
	move_robot_arm_speed(3, 1707, 1500);
  delay_ms(600);
		move_robot_arm_speed(3, 1407, 300);
	delay_ms(2000);
	move_robot_arm_speed(4, 1237, 1500);
	delay_ms(300);
	move_robot_arm_speed(3, 1294, 1500);
	delay_ms(300);

	move_robot_arm_speed(6, 2547, 1500);
	delay_ms(6000);

}



void put_zuobian_car_out() {     //机械臂前伸，视觉（平地）红色
	//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(4, 1526, 1000);
	delay_ms(200);
	   move_robot_arm_speed(5, 1986, 1000);
  delay_ms(500);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(3, 1560, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2078, 1000);
//    // 延时
    delay_ms(500);	
	   move_robot_arm_speed(4, 1500, 1000);
	delay_ms(500);	
	  move_robot_arm_speed(3, 1686, 1000);
  delay_ms(500);
	 move_robot_arm_speed(3, 1721, 1000);
  delay_ms(500);
	 move_robot_arm_speed(4, 938, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1615, 1000);
  delay_ms(500);

 move_robot_arm_speed(4, 1465, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1072, 1000);
  delay_ms(500);
  move_robot_arm_speed(6, 2547, 2000);
  
}

void put_youbian_car_out() {     //机械臂前伸，视觉（平地） 蓝色
	//	 // 执行动作6：移动到位置 200，速度 800
	 move_robot_arm_speed(1, 1010, 1000);
	delay_ms(200);
   move_robot_arm_speed(4, 1526, 1000);
	delay_ms(200);
	   move_robot_arm_speed(5, 1986, 1000);
  delay_ms(500);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(3, 1560, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1859, 1000);
//    // 延时
    delay_ms(500);	
	   move_robot_arm_speed(4, 1500, 1000);
	delay_ms(500);	
	  move_robot_arm_speed(3, 1686, 1000);
  delay_ms(500);
	 move_robot_arm_speed(3, 1721, 1000);
  delay_ms(500);
	 move_robot_arm_speed(4, 938, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1615, 1000);
  delay_ms(500);

 move_robot_arm_speed(4, 1465, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1072, 1000);
  delay_ms(500);
  move_robot_arm_speed(6, 2547, 2000);
    // 延时
//    delay_ms(500);
////    // 执行动作1：移动到位置 1000，速度 1000
//    move_robot_arm_speed(3, 1189, 1000);
////    // 可能需要一些延时，具体延时值根据需求调整
//    delay_ms(500);
// move_robot_arm_speed(6, 2050, 1000);
////	


//    // 延时
  
}



void pick_zhong_move_zuo() {     //机械臂前伸，视觉（平地）
	move_robot_arm_speed(4, 972, 1000);
	delay_ms(100);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 2047, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整

}












void pick_car_zhong_cemian() {     //抓取侧面绿色
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 2060, 1000);
    // 延时
  delay_ms(500);
   move_robot_arm_speed(6, 2960, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2618, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3621, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1524, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(800);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2119, 1000);
//    // 延时
    delay_ms(2000);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3100, 1000);
//    // 延时
}


void pick_car_zuo_cemian() {     //机械臂前伸，视觉（平地）
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 2060, 1000);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2481, 1000);
//    // 延时
    delay_ms(50);

   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2491, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3614, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1503, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3150, 1000);
//    // 延时
}


void pick_car_you_cemian() {     //机械臂前伸，视觉（平地）
//	 // 执行动作6：移动到位置 200，速度 800
		 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(1, 2060, 1000);

	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1758, 1000);
//    // 延时
    delay_ms(50);

   move_robot_arm_speed(6, 2860, 1000);
//	 // 执行动作5：移动到位置 2000，速度 800
   move_robot_arm_speed(5, 2485, 1000);
//    // 延时
   delay_ms(200);
	  //    // 执行动作2：移动到位置 2000，速度 800
   move_robot_arm_speed(4,3611, 1000);
//    // 延时
  delay_ms(500);
	//    // 执行动作1：移动到位置 1000，速度 1000
    move_robot_arm_speed(3, 1500, 1000);
//    // 可能需要一些延时，具体延时值根据需求调整
    delay_ms(1500);
 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(6, 3150, 1000);
//    // 延时
}


void put_zhongjian_car_out_cemian() {     //机械臂前伸，视觉（平地）
	//	 // 执行动作6：移动到位置 200，速度 800
		//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(1, 2060, 1500);
   move_robot_arm_speed(2, 2077, 1500);
	move_robot_arm_speed(4, 953, 1500);
  delay_ms(500);
	move_robot_arm_speed(3, 1982, 1500);
  delay_ms(500);	
	
	move_robot_arm_speed(5, 1861, 1500);  //1861
  delay_ms(500);
	move_robot_arm_speed(3, 1707, 1500);
  delay_ms(600);
		move_robot_arm_speed(3, 1407, 300);
	delay_ms(2000);
	move_robot_arm_speed(4, 1237, 1500);
	delay_ms(300);
	move_robot_arm_speed(3, 1294, 1500);
	delay_ms(300);

	move_robot_arm_speed(6, 2547, 1500);
	delay_ms(6000);

}



void put_zuobian_car_out_cemian() {     //机械臂前伸，视觉（平地）红色
	//	 // 执行动作6：移动到位置 200，速度 800
   move_robot_arm_speed(4, 1526, 1000);
	delay_ms(200);
	   move_robot_arm_speed(5, 1986, 1000);
  delay_ms(500);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(3, 1560, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 2078, 1000);
//    // 延时
    delay_ms(500);	
	   move_robot_arm_speed(4, 1500, 1000);
	delay_ms(500);	
	  move_robot_arm_speed(3, 1686, 1000);
  delay_ms(500);
	 move_robot_arm_speed(3, 1721, 1000);
  delay_ms(500);
	 move_robot_arm_speed(4, 938, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1615, 1000);
  delay_ms(500);

 move_robot_arm_speed(4, 1465, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1072, 1000);
  delay_ms(500);
  move_robot_arm_speed(6, 2547, 2000);
  
}

void put_youbian_car_out_cemian() {     //机械臂前伸，视觉（平地） 蓝色
	//	 // 执行动作6：移动到位置 200，速度 800
	 move_robot_arm_speed(1, 2063, 1000);
	delay_ms(200);
   move_robot_arm_speed(4, 1526, 1000);
	delay_ms(200);
	   move_robot_arm_speed(5, 1986, 1000);
  delay_ms(500);
	 // 执行动作1：移动到位置 2000，速度 800
    move_robot_arm_speed(3, 1560, 1000);
    // 延时
  delay_ms(500);
	 // 执行动作3：移动到位置 3000，速度 1000
   move_robot_arm_speed(2, 1859, 1000);
//    // 延时
    delay_ms(500);	
	   move_robot_arm_speed(4, 1500, 1000);
	delay_ms(500);	
	  move_robot_arm_speed(3, 1686, 1000);
  delay_ms(500);
	 move_robot_arm_speed(3, 1721, 1000);
  delay_ms(500);
	 move_robot_arm_speed(4, 938, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1615, 1000);
  delay_ms(500);

 move_robot_arm_speed(4, 1465, 1000);
  delay_ms(500);
   move_robot_arm_speed(3, 1072, 1000);
  delay_ms(500);
  move_robot_arm_speed(6, 2547, 2000);

  
}