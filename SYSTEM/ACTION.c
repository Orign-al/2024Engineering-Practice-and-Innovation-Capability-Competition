#include "stm32f4xx.h"                  // Device header
#include "PACK_ONE.h"   
#include "delay.h"

void pick_yuantai_green() {     //机械臂前伸，视觉（转盘）

	pick_yuantai();
	delay_ms(400);
	put_zhongjian();
	delay_ms(400);
}


void pick_yuantai_red() {  
//	抓取转盘 放在左边
	pick_yuantai();
	delay_ms(400);
	put_zuobian();
	delay_ms(400);
}



void pick_yuantai_blue() {  
//	抓取转盘 放在右边

	pick_yuantai();
	delay_ms(400);
	put_youbian();
	delay_ms(400);
}



void pick_car_out_red() {  
//	抓车上的左边物料 放在蓝色
	pick_car_zuo();		//取车上左边物料
	delay_ms(1000);
	put_zuobian_car_out();
	delay_ms(1000);
	pick_zhong_move_zuo();
}


void pick_car_out_blue() {  
  // 抓取车上右边物料到左边的靶
	pick_car_you();		//取车上右边物料
	delay_ms(1000);
	put_youbian_car_out();
	delay_ms(1000);
	pick_zhong_move_zuo();
}


void pick_car_out_green() {  //	抓取车上中间物料 放在绿色

	pick_car_zhong();
	delay_ms(1000);
	put_zhongjian_car_out();
	delay_ms(1000);
	pick_zhong_move_zuo();
}


void pick_car_out_red_cemian() {  
//	抓车上的左边物料 放在蓝色
	pick_car_zuo_cemian();		//取车上左边物料
	delay_ms(1000);
	put_zuobian_car_out_cemian();
	delay_ms(1000);
	pick_zhong_move_zuo();
}


void pick_car_out_blue_cemian() {  
  // 抓取车上右边物料到左边的靶
	pick_car_you_cemian();		//取车上右边物料
	delay_ms(1000);
	put_youbian_car_out_cemian();
	delay_ms(1000);
	pick_zhong_move_zuo();
}


void pick_car_out_green_cemian() {  //	抓取车上中间物料 放在绿色

	pick_car_zhong_cemian();
	delay_ms(1000);
	put_zhongjian_car_out_cemian();
	delay_ms(1000);
	pick_zhong_move_zuo();
}