#include "include.h"
#include "OLED_Font.h"

// 软件SPI发送字节
void SPI_SendByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        OLED_SCK_Clr();
        if (byte & 0x80) {
            OLED_MOSI_Set();
        } else {
            OLED_MOSI_Clr();
        }
        OLED_SCK_Set();
        byte <<= 1;
    }
}

// 发送命令
void OLED_WriteCommand(uint8_t command) {
    OLED_DC_Clr(); // 命令模式
    SPI_SendByte(command);
}

// 发送数据
void OLED_WriteData(uint8_t data) {
    OLED_DC_Set(); // 数据模式
    SPI_SendByte(data);
}

// OLED初始化
void OLED_Init(void) {
    // GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIO时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // 配置SCK、MOSI、DC、RES引脚为输出模式
    GPIO_InitStructure.GPIO_Pin = OLED_SCK_Pin | OLED_MOSI_Pin | OLED_DC_Pin | OLED_RES_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // OLED复位
    OLED_RES_Clr();
    for(volatile uint32_t i = 0; i < 50000; i++); // 简单的延迟
    OLED_RES_Set();
    for(volatile uint32_t i = 0; i < 50000; i++); // 简单的延迟

    // OLED初始化指令序列
    // OLED_WriteCommand(0xAE); // 关闭显示
    OLED_WriteCommand(0x20); // 设置内存寻址模式
    OLED_WriteCommand(0x10); // 页地址模式
    OLED_WriteCommand(0xB0); // 设置页起始地址
    OLED_WriteCommand(0xC8); // 设置COM输出扫描方向
    OLED_WriteCommand(0x00); // 设置低列地址
    OLED_WriteCommand(0x10); // 设置高列地址
    OLED_WriteCommand(0x40); // 设置起始行地址
    OLED_WriteCommand(0x81); // 设置对比度控制
    OLED_WriteCommand(0xFF); // 对比度值
    OLED_WriteCommand(0xA1); // 设置段重映射
    OLED_WriteCommand(0xA6); // 设置正常显示
    OLED_WriteCommand(0xA8); // 设置多路复用比率
    OLED_WriteCommand(0x3F); // 1/64
    OLED_WriteCommand(0xA4); // 输出RAM内容显示
    OLED_WriteCommand(0xD3); // 设置显示偏移
    OLED_WriteCommand(0x00); // 无偏移
    OLED_WriteCommand(0xD5); // 设置显示时钟分频比/振荡器频率
    OLED_WriteCommand(0xF0); // 设置分频比
    OLED_WriteCommand(0xD9); // 设置预充电期
    OLED_WriteCommand(0x22);
    OLED_WriteCommand(0xDA); // 设置COM引脚硬件配置
    OLED_WriteCommand(0x12);
    OLED_WriteCommand(0xDB); // 设置VCOMH
    OLED_WriteCommand(0x20); // 0.77xVcc
    OLED_WriteCommand(0x8D); // 设置电荷泵
    OLED_WriteCommand(0x14);
    OLED_WriteCommand(0xAF); // 打开显示
}

// 清屏操作
void OLED_Clear(void) {
    for (uint8_t page = 0; page < 8; page++) {
        OLED_WriteCommand(0xB0 + page); // 设置页地址
        OLED_WriteCommand(0x00); // 设置列低地址
        OLED_WriteCommand(0x10); // 设置列高地址
        for (uint8_t col = 0; col < 128; col++) {
            OLED_WriteData(0x00);
        }
    }
}

// 显示字符
void OLED_ShowChar(uint8_t x, uint8_t y, char chr) {
    uint8_t c = chr - ' '; // 获取字符的字库索引
    if (x > 127) {
        x = 0;
        y++;
    }
    OLED_WriteCommand(0xB0 + y);
    OLED_WriteCommand(((x & 0xF0) >> 4) | 0x10);
    OLED_WriteCommand((x & 0x0F) | 0x01);
    for (uint8_t i = 0; i < 6; i++) {
        OLED_WriteData(F6x8[c][i]);
    }
}

// 显示字符串
void OLED_ShowString(uint8_t x, uint8_t y, char *chr) {
    while (*chr != '\0') {
        OLED_ShowChar(x, y, *chr);
        x += 6;
        if (x > 122) {
            x = 0;
            y++;
        }
        chr++;
    }
}

// 显示数字
void OLED_ShowNumber(uint8_t x, uint8_t y, int32_t num) {
    char buffer[12]; // 足够容纳一个32位整数和符号
    sprintf(buffer, "%d", num);
    OLED_ShowString(x, y, buffer);
}

// 显示示例数据
void OLED_ShowExample(void) {
    OLED_ShowString(0, 0, "Hello, OLED!");
}

void OLED_ShowUTF8String(uint8_t x, uint8_t y, char *chr) {
    while (*chr != '\0') {
        if (*chr & 0x80) {  // 检测是否为UTF-8多字节字符
            // 对UTF-8字符的处理（这里简单跳过处理，只作为示例）
            // 您可能需要用自定义的字库来处理这些字符
            chr += 3;  // 假设是3字节的中文字符
            x += 12;   // 假设字符占据12像素宽度
        } else {
            OLED_ShowChar(x, y, *chr);  // 显示单字节ASCII字符
            x += 6;
        }

        if (x > 122) {
            x = 0;
            y++;
        }
        chr++;
    }
}


