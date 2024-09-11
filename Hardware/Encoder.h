#ifndef _Encoder_H_
#define _Encoder_H_




#define ENCODER_A_Pin1    GPIO_Pin_15
#define ENCODER_A_Pin2    GPIO_Pin_3
#define ENCODER_A_1_GPIO_Port  GPIOA 
#define ENCODER_A_2_GPIO_Port  GPIOB

#define ENCODER_B_Pin1    GPIO_Pin_4
#define ENCODER_B_Pin2    GPIO_Pin_5
#define ENCODER_B_GPIO_Port  GPIOB

#define ENCODER_C_Pin1    GPIO_Pin_6
#define ENCODER_C_Pin2    GPIO_Pin_7
#define ENCODER_C_GPIO_Port  GPIOB

#define ENCODER_D_Pin1    GPIO_Pin_0
#define ENCODER_D_Pin2    GPIO_Pin_1
#define ENCODER_D_GPIO_Port  GPIOA

void Encoder_Init(void);
int32_t Encoder_GetValue(char encoder);



#endif

