#include "stm32f4xx.h"                  // Device header
#include "PACK_ONE.h"   
#include "delay.h"

void pick_yuantai_green() {     //机械臂前伸，视觉（转盘）

//	watch_Initial_Position1();
	delay_ms(500);
	pick_yuantai();
	delay_ms(1400);
	put_zhongjian();

}


void pick_yuantai_red() {  
//	抓取转盘 放在左边
//	watch_Initial_Position1(); //视觉的初始位置
	delay_ms(500);
	pick_yuantai();
	delay_ms(1400);
	put_zuobian();

}


void pick_yuantai_blue() {  
//	抓取转盘 放在右边
//	watch_Initial_Position1(); //视觉的初始位置
	delay_ms(500);
	pick_yuantai();
	delay_ms(1400);
	put_youbian();
}



void pick_car_out_red() {  
//	抓车上的左边物料 放在蓝色
	watch_Initial_Position2();
	delay_ms(1000);
	pick_car_zuo();		//取车上左边物料
	delay_ms(1000);
	put_youbian_car_out();
	delay_ms(1000);
}


void pick_car_out_blue() {  
  // 抓取车上右边物料到左边的靶
	watch_Initial_Position2();
	delay_ms(1000);
	pick_car_you();		//取车上右边物料
	delay_ms(1000);
	put_zuobian_car_out();
	delay_ms(1000);
}


void pick_car_out_green() {  
	//	抓取车上中间物料 放在绿色
	//抓中间  打靶子中间
	pick_zhong_move_zuo();
	delay_ms(1000);
	watch_Initial_Position2();
	delay_ms(1000);
	pick_car_zhong();
	delay_ms(1000);
	put_zhong_car_out();
	delay_ms(1000);
}