#include "include.h"

#define MOTOR_COUNT 4

struct SAngle {
    short Angle[3];
    short T;
} stcAngle;

#define POSITION_DEADBAND 13  // 死区值，单位取决于编码器的单位



#define ACC_UPDATE        0x01
#define GYRO_UPDATE       0x02
#define ANGLE_UPDATE      0x04
#define MAG_UPDATE        0x08
#define READ_UPDATE       0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;

Move_moter_speed Move_moters_speed;
MotorFeedback motors[MOTOR_COUNT];
PIDController angle_pid_controllers;  // 单一角度PID控制器
PIDController position_pid_controllers[MOTOR_COUNT];
PIDController speed_pid_controllers[MOTOR_COUNT];
PIDController current_pid_controllers[MOTOR_COUNT];


#define BUFFER_SIZE 512  // 接收缓冲区大小

#define UART_BUFFER_SIZE 256  //祝秋

volatile char uartReceiveBuffer[UART_BUFFER_SIZE];  //祝秋
volatile uint16_t uartReceiveIndex = 0;  //祝秋


volatile uint8_t rx_buffer[BUFFER_SIZE];  // 接收缓冲区
volatile uint16_t rx_index = 0;           // 接收缓冲区索引
volatile uint8_t rx_complete = 0;         // 接收完成标志位


int position_x, position_y;
int sign_move, flag_arr_speed_1, flag_arr_speed_2, flag_arr_speed_3, flag_arr_speed_4;
int x_pi, y_pi;
int pi_put_obj_fir = 999;
int pi_put_obj_sec = 999;
int vy, vx, omega, r;
float target_positions[MOTOR_COUNT] = {0};  // 目标位置数组
float target_yaw = 0.0f;  // 目标Yaw角
int Move_num = 1;
int run_num = 1;
int left = 0, right = 0, up = 0, down = 0;
// uint8_t data;

volatile uint32_t system_ticks = 0;
volatile uint8_t update_display = 0;



#define MAX_ACCELERATION 3000.0f  // 最大加速度，单位根据具体情况调整

float current_speeds[MOTOR_COUNT] = {0};  // 当前速度数组，用于加速度控制

void CAN1_RX0_IRQHandler(void) {
    CAN_RX_ISR();
}


float LimitAcceleration(float current_speed, float target_speed) {
    float speed_diff = target_speed - current_speed;
    if (fabs(speed_diff) > MAX_ACCELERATION) {
        if (speed_diff > 0) {
            return current_speed + MAX_ACCELERATION;
        } else {
            return current_speed - MAX_ACCELERATION;
        }
    }
    return target_speed;
}

void set_target_position(int pos_y, int pos_x, int omega_self, int r_self) {

    flag_arr_speed_1 = 0;
    flag_arr_speed_2 = 0;
    flag_arr_speed_3 = 0;
    flag_arr_speed_4 = 0;

    vy = pos_y;
    vx = pos_x;
    omega = omega_self;
    r = r_self;

    // 计算每个电机的目标速度
    float target_speed_2 = (float)(vy + vx + omega * r);  // 右上角电机（2号）
    float target_speed_3 = (float)(-vy - vx + omega * r); // 左下角电机（1号）
    float target_speed_1 = (float)(vy - vx - omega * r);  // 右下角电机（0号）
    float target_speed_4 = (float)(-vy + vx - omega * r); // 左上角电机（3号）

    // 应用加速度限制
    Move_moters_speed.moter_speed_2 = LimitAcceleration(current_speeds[0], target_speed_2);
    Move_moters_speed.moter_speed_3 = LimitAcceleration(current_speeds[1], target_speed_3);
    Move_moters_speed.moter_speed_1 = LimitAcceleration(current_speeds[2], target_speed_1);
    Move_moters_speed.moter_speed_4 = LimitAcceleration(current_speeds[3], target_speed_4);

    // 更新当前速度
    current_speeds[0] = Move_moters_speed.moter_speed_2;
    current_speeds[1] = Move_moters_speed.moter_speed_3;
    current_speeds[2] = Move_moters_speed.moter_speed_1;
    current_speeds[3] = Move_moters_speed.moter_speed_4;

    run_num++;
}





void InitPIDControllers(void) {
    // 初始化角度环PID控制器

    PID_Init(&angle_pid_controllers, 3.0f,4.0f, 0.001f, 360.0f);  // 角度环参数

    // 初始化位置环PID控制器
    PID_Init(&position_pid_controllers[0], 30.0f, 1.9f, 0.0f, 1000.0f);
    PID_Init(&position_pid_controllers[1], 30.0f, 1.7f, 0.0f, 1000.0f);
    PID_Init(&position_pid_controllers[2], 30.0f, 1.7f, 0.0f, 1000.0f);
    PID_Init(&position_pid_controllers[3], 30.0f, 1.9f, 0.0f, 1000.0f);

    // 初始化速度环PID控制器
    PID_Init(&speed_pid_controllers[0], 1.8f, 2.5f, 0.012f, 100.0f);
    PID_Init(&speed_pid_controllers[1], 1.8f, 2.5f, 0.012f, 100.0f);
    PID_Init(&speed_pid_controllers[2], 1.8f, 2.7f, 0.012f, 100.0f);
    PID_Init(&speed_pid_controllers[3], 1.8f, 2.5f, 0.012f, 100.0f);

    // 初始化电流环PID控制器
    PID_Init(&current_pid_controllers[0], 1.1f, 0.00f, 0.0022f, 1000.0f);
    PID_Init(&current_pid_controllers[1], 1.1f, 0.00f, 0.0022f, 1000.0f);
    PID_Init(&current_pid_controllers[2], 1.1f, 0.00f, 0.0022f, 1000.0f);
    PID_Init(&current_pid_controllers[3], 1.1f, 0.00f, 0.0022f, 1000.0f);

    // 设置输出限幅
    for (int i = 0; i < MOTOR_COUNT; i++) {
        PID_SetOutputLimits(&position_pid_controllers[i], -10000, 10000);
        PID_SetOutputLimits(&speed_pid_controllers[i], -2800, 2800);
        PID_SetOutputLimits(&current_pid_controllers[i], -6000, 6000);
    }
    // 角度环限幅只需对一个控制器进行设置
    PID_SetOutputLimits(&angle_pid_controllers, -360, 360);



}

void CopeSerial4Data(unsigned char ucData) {
    static unsigned char ucRxBuffer[250];
    static unsigned char ucRxCnt = 0;

    ucRxBuffer[ucRxCnt++] = ucData; // 将收到的数据存入缓冲区
    if (ucRxBuffer[0] != 0x55) { // 数据头不对，则重新开始寻找0x55数据头
        ucRxCnt = 0;
        return;
    }
    if (ucRxCnt < 11) return; // 数据不满11个，则返回
    else {
        switch (ucRxBuffer[1]) { // 判断数据是哪种类型，并将其拷贝到对应的结构体中
            case 0x53:
                memcpy(&stcAngle, &ucRxBuffer[2], 8);
                break;
        }
        ucRxCnt = 0; // 清空缓冲区
    }
}

void UART4_IRQHandler(void) {
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) {
        CopeSerial4Data((unsigned char)UART4->DR); // 处理数据
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    }
    USART_ClearITPendingBit(UART4, USART_IT_ORE);
}

void ClearRxBuffer(void) {
    memset(rx_buffer, 0, BUFFER_SIZE);  // 清空缓冲区
    rx_index = 0;                       // 重置索引
    rx_complete = 0;                    // 重置接收完成标志
}


void UART5_IRQHandler(void) {
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
        uint8_t received_byte = USART_ReceiveData(UART5);

        if (received_byte == '\r') {
            USART_ClearITPendingBit(UART5, USART_IT_RXNE);  // 清除中断标志位
            return;
        }

        if (rx_index < BUFFER_SIZE - 1) {
            rx_buffer[rx_index++] = received_byte;
            


        }

        // 检测到换行符或缓冲区满时，表示一帧接收完成
        if (received_byte == '\n' || rx_index >= BUFFER_SIZE - 1) {
            rx_buffer[rx_index] = '\0';  // 添加字符串终止符
            rx_complete = 1;             // 设置接收完成标志

            // // 清空缓冲区
            // ClearRxBuffer();
        }



        USART_ClearITPendingBit(UART5, USART_IT_RXNE);  // 清除中断标志位
    }
}

// 祝秋
void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        char receivedChar = USART_ReceiveData(USART2);
        if (uartReceiveIndex < UART_BUFFER_SIZE - 1) {
            uartReceiveBuffer[uartReceiveIndex++] = receivedChar;
            if (receivedChar == '\n') {
                uartReceiveBuffer[uartReceiveIndex] = '\0';

                // ??: ProcessReceivedMessage((char*)uartReceiveBuffer);
                uartReceiveIndex = 0;
            }
        } else {
            uartReceiveIndex = 0; 
        }
    }
}



void ProcessReceivedData(void) {
    if (rx_complete) {
        OLED_Clear();  // 清屏
        OLED_ShowUTF8String(0, 0, (char*)rx_buffer);  // 将接收到的字符串显示到OLED

        // 清除接收完成标志
        rx_complete = 0;
    }
}

void UART5_Transmit(uint8_t *pData, uint16_t Size) {
    for (uint16_t i = 0; i < Size; i++) {
        // 等待发送寄存器为空
        while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
        
        // 发送数据
        USART_SendData(UART5, pData[i]);

        // 等待发送完成
        while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
    }
}



void UpdateOLEDDisplay(void) {
    OLED_Clear();


    OLED_ShowNumber(0, 2, x_pi);
    OLED_ShowNumber(24, 2,y_pi);
    
    OLED_ShowNumber(0, 6, pi_put_obj_fir);
    OLED_ShowNumber(24, 6, pi_put_obj_sec);

    // OLED_ShowNumber(0, 6, flag_arr_speed_4);
    // OLED_ShowNumber(24, 6, motors[2].revolutions);

}

void pi_data_process(char *rx_buffer ,int *x ,int *y, int *put_obj_fir , int *put_obj_sec) {
    int strlenmax;
    strlenmax = strlen(rx_buffer);
    if(rx_buffer[0] == 'A' && rx_buffer[1] == 'Z' && rx_buffer[strlenmax-2] == 'Z' && rx_buffer[strlenmax -1] == 'A' ){
        sscanf(rx_buffer, "AZx%dy%dZA", x, y); 
        // ClearRxBuffer();       
    }
    if(rx_buffer[0] == 'B' && rx_buffer[1] == 'Z' && rx_buffer[strlenmax-2] == 'Z' && rx_buffer[strlenmax -1] == 'B' ){
        sscanf(rx_buffer, "BZ%d+%dZB", put_obj_fir, put_obj_sec);
        // ClearRxBuffer();        
    }

}


void TIM6_DAC_IRQHandler(void) {
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        system_ticks++;
        ProcessReceivedData();
        pi_data_process(rx_buffer ,&x_pi ,&y_pi, &pi_put_obj_fir , &pi_put_obj_sec);

        
        if (system_ticks % 500 == 0) {
            update_display = 1;
        }
    }
}

void TIM7_IRQHandler(void) {
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

        int16_t motor_currents[MOTOR_COUNT];
        int motors_at_target = 0;  // 初始化为1，假定所有电机都到达目标

        // 获取当前偏航角度（Yaw角）
        float current_yaw = (float)stcAngle.Angle[2] / 32768.0f * 180.0f;

        // 计算Yaw角度误差并通过PID控制器计算校正值
        float yaw_error = target_yaw - current_yaw;
        float yaw_correction = PID_Compute(&angle_pid_controllers, yaw_error, 0);

        // 位置环PID计算，基于电机编码器反馈和目标位置，应用Yaw校正
        float position_pid_output1 = PID_Compute(&position_pid_controllers[0], Move_moters_speed.moter_speed_1 - yaw_correction, motors[0].revolutions);
        float position_pid_output2 = PID_Compute(&position_pid_controllers[1], Move_moters_speed.moter_speed_2 - yaw_correction, motors[1].revolutions);
        float position_pid_output3 = PID_Compute(&position_pid_controllers[2], Move_moters_speed.moter_speed_3 - yaw_correction, motors[2].revolutions);
        float position_pid_output4 = PID_Compute(&position_pid_controllers[3], Move_moters_speed.moter_speed_4 - yaw_correction, motors[3].revolutions);

        // 检查是否所有电机都已达到目标位置，并应用死区判断
        if (fabs(Move_moters_speed.moter_speed_1 - motors[0].revolutions) <= POSITION_DEADBAND) {
            flag_arr_speed_1 = 1;
        }


        if (fabs(Move_moters_speed.moter_speed_2 - motors[1].revolutions) <= POSITION_DEADBAND) {
            flag_arr_speed_2 = 1;
        }
        if (fabs(Move_moters_speed.moter_speed_3 - motors[2].revolutions) <= POSITION_DEADBAND) {
            flag_arr_speed_3 = 1;
        }
        if (fabs(Move_moters_speed.moter_speed_4 - motors[3].revolutions) <= POSITION_DEADBAND) {
            flag_arr_speed_4 = 1;
        }
        if(flag_arr_speed_4 + flag_arr_speed_1 + flag_arr_speed_2 + flag_arr_speed_3 > 0)
        {

            flag_arr_speed_4 = 1;
            flag_arr_speed_1 = 1;
            flag_arr_speed_2 = 1;
            flag_arr_speed_3 = 1;
            motors_at_target = 1;
        }


        if (motors_at_target) {
            // 如果所有电机都达到目标位置，停止电机
            M2006_SetCurrent_ALL(0, 0, 0, 0);
        } else {
            // 速度环PID计算
            float speed_pid_output1 = PID_Compute(&speed_pid_controllers[0], position_pid_output1, motors[0].speed);
            float speed_pid_output2 = PID_Compute(&speed_pid_controllers[1], position_pid_output2, motors[1].speed);
            float speed_pid_output3 = PID_Compute(&speed_pid_controllers[2], position_pid_output3, motors[2].speed);
            float speed_pid_output4 = PID_Compute(&speed_pid_controllers[3], position_pid_output4, motors[3].speed);
            
            // 电流环PID计算
            motor_currents[0] = (int16_t)PID_Compute(&current_pid_controllers[0], speed_pid_output1, motors[0].current);
            motor_currents[1] = (int16_t)PID_Compute(&current_pid_controllers[1], speed_pid_output2, motors[1].current);
            motor_currents[2] = (int16_t)PID_Compute(&current_pid_controllers[2], speed_pid_output3, motors[2].current);
            motor_currents[3] = (int16_t)PID_Compute(&current_pid_controllers[3], speed_pid_output4, motors[3].current);
            
            M2006_SetCurrent_ALL(motor_currents[0], motor_currents[1], motor_currents[2], motor_currents[3]);
        }
    }
}

int main(void) {
    SystemInit();                // 系统初始化
    OLED_Init();                 // OLED初始化
    OLED_Clear();                // 清空OLED
    delay_init(168);             // 延时初始化，基于168MHz的时钟

    TIM6_Int_Init(99, 839);      // 初始化定时器6中断，每秒1000次
    TIM7_Int_Init(99, 839);      // 初始化定时器7中断，每秒1000次
    
    InitPIDControllers();        // 初始化PID控制器
    CAN_Config();                // CAN总线配置
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); // 使能CAN1中断
    NVIC_EnableIRQ(CAN1_RX0_IRQn); // 使能CAN1接收中断
    sign_move = 0;
    // char test_message[] = "Hello, UART5!\n";
    USART4_Init(115200);     // 初始化USART4用于HWT101传感器通信
    USART5_Init();

    // 机械臂模块
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//使用了中断，则这一句必须要有	  
	USART2_IO_Conf();//配置串口的IO	  
	USART2_Conf(115200);//串口配置成波特率115200
	//Usart_SendString(USART1,(uint8_t *)data,5);//发送字符串
	delay_init(168);
    delay_ms(1000);	
    //行走、初始姿态
	 Initial_Position();        //初始动作 以及 行走动作
     delay_ms(500);
    Preparation_to_pack();      //  准备抓取动作

    while (1) {

        if (update_display) {
            UpdateOLEDDisplay();
            update_display = 0;
            
        }


        // 发送一些测试数据

        // UART5_Transmit((uint8_t *)test_message, strlen(test_message));

    

        // uint8_t received = USART5_ReceiveData();



        delay_ms(300); // 延时100ms，以便接收数据

        set_target_position(0, 40, 0, 0);
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(300);


        target_yaw = 48;        

        set_target_position(-80, 20, 0, 0);
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        // int i = 1 ;


       // while(1){

       //     if (pi_put_obj_fir != 999 && pi_put_obj_sec != 999)
       //     {
       //         break;
       //     }
            
      //  }


        

        delay_ms(3000);

        target_yaw = 47;
        set_target_position(-185, 20, 0, 0);
        right = 1;
        left = 0;
        up = 0;
        down = 0;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(300);
        watch_Initial_Position();   //视觉动作抬伸
		ACTION_PLATFORM_green();
		ACTION_PLATFORM_red();
		ACTION_PLATFORM_blue();

        delay_ms(1000);
        set_target_position(-90, 20, 0, 0);
        right = 0;
        left = 0;
        up = 1;
        down = 0;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(1000);

        set_target_position(-100, 150, 0, 0);
        right = 0;
        left = 0;
        up = 1;
        down = 0;
        InitPIDControllers();        // 初始化PID控制器        
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(1000);

        set_target_position(-100, 230, 0, 0);
        right = 0;
        left = 1;
        up = 0;
        down = 0;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(1000);
        
        set_target_position(-100, 100, 0, 0);
        right = 0;
        left = 1;
        up = 0;
        down = 0;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){ UpdateOLEDDisplay();};
        delay_ms(1000);

        set_target_position(-220, 120, 0, 0);
        right = 0;
        left = 0;
        up = 0;
        down = 1;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(1000);

        set_target_position(-90, 120, 0, 0);
        right = 0;
        left = 0;
        up = 0;
        down = 1;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(300);


        set_target_position(30, 120, 0, 0);
        right = 0;
        left = 0;
        up = 0;
        down = 1;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){ UpdateOLEDDisplay();};
        delay_ms(300);


        // set_target_position(0, 0, 0, 0);
        // right = 0;
        // left = 0;
        // up = 0;
        // down = 1;
        // InitPIDControllers();        // 初始化PID控制器
        // while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){ UpdateOLEDDisplay();};
        // delay_ms(300);


        set_target_position(0, 0, 0, 0);
        right = 0;
        left = 0;
        up = 0;
        down = 1;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){UpdateOLEDDisplay();};
        delay_ms(300);

        
        target_yaw = 0;
        set_target_position(0, -15, 0, 0);
        right = 0;
        left = 0;
        up = 0;
        down = 1;
        InitPIDControllers();        // 初始化PID控制器
        while (flag_arr_speed_1 != 1 || flag_arr_speed_2 != 1 || flag_arr_speed_3 != 1 || flag_arr_speed_4 != 1){ while (1){UpdateOLEDDisplay();}};
        delay_ms(300);



    }
}
