#ifndef _m2006driver_H_
#define _m2006driver_H_

void CAN_Config(void);
void M2006_SetCurrent(uint8_t id, int16_t current);
void CAN_RX_ISR(void);

void M2006_SetCurrent_ALL(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
typedef struct {
    uint16_t angle;         // 转子机械角度 (0-8191)
    int16_t speed;          // 转子转速 (RPM)
    int16_t current;        // 实际转矩电流
    uint8_t temperature;    // 电机温度
    int32_t rotations;      // 完整旋转次数
    int32_t total_angle;    // 总角度（包括多圈）
    uint16_t last_angle;  // 上一次的角度值
    float revolutions;    // 圈数（包括小数部分）
} MotorFeedback;


#endif
