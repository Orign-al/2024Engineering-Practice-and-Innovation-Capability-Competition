#include "stm32f4xx.h"                  // Device header
#include "PACK_ONE.h"   
#include "delay.h"

void ACTION_GROUND_red(){

	watch_Initial_Position(); //视觉的初始位置
	pack_red_1();   //抓取前
	delay_ms(1000);
	pack_red_2();  //开始抓取并放置
	delay_ms(1000);
	Preparation_to_pack();
}

void ACTION_GROUND_blue(){

	watch_Initial_Position(); //视觉的初始位置
	pack_blue_1();   //抓取前
	delay_ms(1000);
	pack_blue_2();  //开始抓取并放置
	delay_ms(1000);
	Preparation_to_pack();
}

void ACTION_GROUND_green(){

	watch_Initial_Position(); //视觉的初始位置
	pack_green_1();   //抓取前
	delay_ms(1000);
	pack_green_2();  //开始抓取并放置
	delay_ms(1000);
	Preparation_to_pack();
}

void ACTION_PLATFORM_green(){

	Preparation_to_pack();
	delay_ms(1000);
	pack_yuantai_1();  //抓取中间
	pack_green_2();  //放置到中间
	delay_ms(2000);
}

void ACTION_PLATFORM_red(){

	Preparation_to_pack();
	delay_ms(1000);
	pack_yuantai_1();  //抓取中间
	pack_red_2();  //放置到左边
	delay_ms(2000);
}

void ACTION_PLATFORM_blue(){

	Preparation_to_pack();
	delay_ms(1000);
	pack_yuantai_1();  //抓取中间
	pack_blue_2();  //放置到右边
	delay_ms(2000);
}

