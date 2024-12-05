#include <REGX52.H>
#include "PowSelector.h"


sbit LCD_RS = P2 ^ 4;
sbit LCD_RW = P2 ^ 5;
sbit LCD_EN = P2 ^ 6;
#define LCD_DataPort P0

/**
  * @brief  1ms @ 12MHz
  */
void LCD_Delay() {
    unsigned char i, j;
    for (i = 2; i; i--) for (j = 246; j; j--);
}

/**
  * @brief  写命令
  * @param  Command 要写入的命令
  */
void LCD_WriteCommand(unsigned char Command) {
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DataPort = Command;
    LCD_EN = 1;
    LCD_Delay();
    LCD_EN = 0;
    LCD_Delay();
}

/**
  * @brief  写数据
  * @param  Data 要写入的数据
  */
void LCD_WriteData(unsigned char Data) {
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DataPort = Data;
    LCD_EN = 1;
    LCD_Delay();
    LCD_EN = 0;
    LCD_Delay();
}

/**
  * @brief  设置光标位置
  * @param  Line 行位置，范围: 2
  * @param  Col 列位置，范围: 16
  * @retval 无
  */
void LCD_SetCursor(unsigned char Line, unsigned char Col) {
    if (Line) {
        LCD_WriteCommand(0x80 | 0x40 | Col);
    }
    else {
        LCD_WriteCommand(0x80 | 0x00 | Col);
    }
}

/**
  * @brief  初始化函数
  */
void LCD_Init() {
    LCD_WriteCommand(0x38); // 八位数据接口，两行显示，5*7点阵
    LCD_WriteCommand(0x0C); // 显示开，光标关，闪烁关
    LCD_WriteCommand(0x06); // 数据读写操作后，光标自动加一，画面不动
    LCD_WriteCommand(0x01); // 光标复位，清屏
}

/**
  * @brief  指定位置显示字符
  * @param  Line 行位置，范围: 2
  * @param  Col 列位置，范围: 16
  * @param  Char 要显示的字符
  */
void LCD_ShowChar(unsigned char Line, unsigned char Col, char Char) {
    LCD_SetCursor(Line, Col);
    LCD_WriteData(Char);
}

/**
 * @brief  指定位置显示重复字符, 左闭右闭
 * @param  Line 行位置，范围: 2
 * @param  ColStart 起始列位置，范围: 16
 * @param  ColEnd 结束列位置，范围: 16
 * @param  Char 要显示的字符
 */
void LCD_ShowRepeatChar(unsigned char Line, unsigned char ColStart, unsigned char ColEnd, char Char) {
    LCD_SetCursor(Line, ColStart);
    for (; ColStart <= ColEnd; ColStart++) {
        LCD_WriteData(Char);
    }
}

/**
 * @brief  清空指定行指定列后的所有字符
 * @param  Line 行位置，范围: 2
 * @param  ColStart 起始列位置，范围: 16
 */
void LCD_Flush(unsigned char Line, unsigned char ColStart) {
    LCD_SetCursor(Line, ColStart);
    LCD_ShowRepeatChar(Line, ColStart, 15, ' ');
}

/**
  * @brief  指定位置开始显示字符串
  * @param  Line 行位置，范围: 2
  * @param  Col 起始列位置，范围: 16
  * @param  String 要显示的字符串
  */
void LCD_ShowString(unsigned char Line, unsigned char Col, char* String) {
    LCD_SetCursor(Line, Col);
    for (; *String; String++) {
        LCD_WriteData(*String);
    }
}

/**
  * @brief  指定位置开始以无符号十进制显示所给数字
  * @param  Line 行位置，范围: 2
  * @param  Col 起始列位置，范围: 16
  * @param  Number 要显示的数字，范围: 0 - 65535
  * @param  Length 要显示数字的长度，范围: 1 - 5
  */
void LCD_ShowNum(unsigned char Line, unsigned char Col, unsigned int Number, unsigned char Length) {
    LCD_SetCursor(Line, Col);
    for (; Length; Length--) {
        LCD_WriteData(Number / LCD_Pow(10, Length - 1) % 10 + '0');
    }
}

/**
  * @brief  指定位置开始以有符号十进制显示所给数字
  * @param  Line 行位置，范围: 2
  * @param  Col 起始列位置，范围: 16
  * @param  Number 要显示的数字，范围: -32768 - 32767
  * @param  Length 要显示数字的长度，范围: 1 - 5
  */
void LCD_ShowSignedNum(unsigned char Line, unsigned char Col, int Number, unsigned char Length) {
    LCD_SetCursor(Line, Col);
    if (Number >= 0) {
        LCD_WriteData('+');
    }
    else {
        LCD_WriteData('-');
        Number = -Number;
    }
    for (; Length; Length--) {
        LCD_WriteData(Number / LCD_Pow(10, Length - 1) % 10 + '0');
    }
}

/**
  * @brief  指定位置开始以十六进制显示所给数字
  * @param  Line 行位置，范围: 2
  * @param  Col 起始列位置，范围: 16
  * @param  Number 要显示的数字，范围: 0 - 0xFFFF
  * @param  Length 要显示数字的长度，范围: 1 - 4
  */
void LCD_ShowHexNum(unsigned char Line, unsigned char Col, unsigned int Number, unsigned char Length) {
    unsigned char digit;
    LCD_SetCursor(Line, Col);
    for (; Length; Length--) {
        // digit = Number / LCD_Pow_H[Length - 1] % 16;
        digit = Number / LCD_Pow(16, Length - 1) % 16;
        if (digit < 10) {
            LCD_WriteData(digit + '0');
        }
        else {
            LCD_WriteData(digit - 10 + 'A');
        }
    }
}

/**
  * @brief  指定位置开始以二进制显示所给数字
  * @param  Line 行位置，范围: 2
  * @param  Col 起始列位置，范围: 16
  * @param  Number 要显示的数字，范围: 0 - 0xFFFF
  * @param  Length 要显示数字的长度，范围: 1 - 16
  */
void LCD_ShowBinNum(unsigned char Line, unsigned char Col, unsigned int Number, unsigned char Length) {
    LCD_SetCursor(Line, Col);
    for (; Length; Length--) {
        LCD_WriteData(((Number >> (Length - 1)) & 0x01) + '0');
    }
}
