#include "include.h"

#define CAN_ID_BASE 0x200
#define CAN_DATA_LENGTH 8
#define MOTOR_ID_OFFSET 0x201
#define MAX_MOTOR_ID 4

#define FILTER_ALPHA 0.5f  // 滤波系数，可以根据需要调整

extern MotorFeedback motors[MOTOR_COUNT];

void CAN_Config(void) {
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef       GPIO_InitStructure;
    NVIC_InitTypeDef       NVIC_InitStructure;
    
    // 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    // 配置GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);
    
    // 配置CAN
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
    CAN_InitStructure.CAN_Prescaler = 3;  // 42MHz / (1+9+4) / 3 = 1Mbps
    CAN_Init(CAN1, &CAN_InitStructure);
    
    // 配置CAN过滤器
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    // 配置NVIC for CAN1 接收中断
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 使能CAN接收中断
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

void M2006_SetCurrent(uint8_t id, int16_t current) {
    if (id < 1 || id > MAX_MOTOR_ID) {
        return;
    }

    CanTxMsg TxMessage;
    TxMessage.StdId = CAN_ID_BASE;
    TxMessage.IDE = CAN_Id_Standard;
    TxMessage.RTR = CAN_RTR_Data;
    TxMessage.DLC = CAN_DATA_LENGTH;
    
    memset(TxMessage.Data, 0, CAN_DATA_LENGTH);
    
    TxMessage.Data[(id-1)*2] = (uint8_t)((current >> 8) & 0xFF);
    TxMessage.Data[(id-1)*2+1] = (uint8_t)(current & 0xFF);
    
    CAN_Transmit(CAN1, &TxMessage);
}

void CAN_RX_ISR(void) {
    CanRxMsg RxMessage;
    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET) {
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
        
        if (RxMessage.StdId >= MOTOR_ID_OFFSET && RxMessage.StdId < MOTOR_ID_OFFSET + MAX_MOTOR_ID) {
            uint8_t id = RxMessage.StdId - MOTOR_ID_OFFSET;
            if (id < MOTOR_COUNT) {
                // 读取新的反馈值
                uint16_t new_angle = (uint16_t)((RxMessage.Data[0] << 8) | RxMessage.Data[1]);
                int16_t new_speed = (int16_t)((RxMessage.Data[2] << 8) | RxMessage.Data[3]);
                int16_t new_current = (int16_t)((RxMessage.Data[4] << 8) | RxMessage.Data[5]);
                uint8_t new_temperature = RxMessage.Data[6];
                
                // 应用低通滤波
                motors[id].angle = (uint16_t)(FILTER_ALPHA * new_angle + (1 - FILTER_ALPHA) * motors[id].angle);
                motors[id].speed = (int16_t)(FILTER_ALPHA * new_speed + (1 - FILTER_ALPHA) * motors[id].speed);
                motors[id].current = ((int16_t)(FILTER_ALPHA * new_current + (1 - FILTER_ALPHA) * motors[id].current));
                
                // 温度不需要滤波，直接更新
                motors[id].temperature = new_temperature;
                
                // 处理角度跳变和计算圈数
                int16_t angle_diff = (int16_t)new_angle - (int16_t)motors[id].last_angle;
                if (abs(angle_diff) > 4096) {  // 如果角度差大于半圈
                    if (angle_diff > 0) {
                        motors[id].rotations--;
                    } else {
                        motors[id].rotations++;
                    }
                }
                motors[id].last_angle = new_angle;
                
                // 计算总角度（包括圈数）
                motors[id].total_angle = motors[id].rotations * 8192 + motors[id].angle;
                
                // 计算圈数（包括小数部分）
                motors[id].revolutions = (float)motors[id].total_angle / 8192.0f;
            }
        }
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
    }
}

void M2006_SetCurrent_ALL(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {
    CanTxMsg TxMessage;
    TxMessage.StdId = CAN_ID_BASE;
    TxMessage.IDE = CAN_Id_Standard;
    TxMessage.RTR = CAN_RTR_Data;
    TxMessage.DLC = CAN_DATA_LENGTH;

    TxMessage.Data[0] = (uint8_t)((iq1 >> 8) & 0xFF);
    TxMessage.Data[1] = (uint8_t)(iq1 & 0xFF);
    TxMessage.Data[2] = (uint8_t)((iq2 >> 8) & 0xFF);
    TxMessage.Data[3] = (uint8_t)(iq2 & 0xFF);
    TxMessage.Data[4] = (uint8_t)((iq3 >> 8) & 0xFF);
    TxMessage.Data[5] = (uint8_t)(iq3 & 0xFF);
    TxMessage.Data[6] = (uint8_t)((iq4 >> 8) & 0xFF);
    TxMessage.Data[7] = (uint8_t)(iq4 & 0xFF);
    
    CAN_Transmit(CAN1, &TxMessage);
}