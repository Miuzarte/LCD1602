#include "LCD1602.h"


// 打表太占空间
long LCD_Pow_Long(unsigned char base, unsigned char exp) {
    long result = 1;
    for (; exp; exp--) {
        result *= base;
    }
    return result;
}

/**
  * @brief  指定位置开始以无符号十进制显示所给数字
  * @param  Line 行位置，范围：2
  * @param  Col 起始列位置，范围：16
  * @param  Number 要显示的数字，范围：0 - 4,294,967,295
  * @param  Length 要显示数字的长度，范围：1 - 10
  */
void LCD_ShowNum_Long(unsigned char Line, unsigned char Col, unsigned long Number, unsigned char Length) {
    LCD_SetCursor(Line, Col);
    for (; Length; Length--) {
        LCD_WriteData(Number / LCD_Pow_Long(10, Length - 1) % 10 + '0');
    }
}

/**
  * @brief  指定位置开始以有符号十进制显示所给数字
  * @param  Line 行位置，范围：2
  * @param  Col 起始列位置，范围：16
  * @param  Number 要显示的数字，范围：-2,147,483,648 - 2,147,483,647
  * @param  Length 要显示数字的长度，范围：1 - 10
  */
void LCD_ShowSignedNum_Long(unsigned char Line, unsigned char Col, long Number, unsigned char Length) {
    LCD_SetCursor(Line, Col);
    if (Number >= 0) {
        LCD_WriteData('+');
    }
    else {
        LCD_WriteData('-');
        Number = -Number;
    }
    for (; Length; Length--) {
        LCD_WriteData(Number / LCD_Pow_Long(10, Length - 1) % 10 + '0');
    }
}

/**
  * @brief  指定位置开始以十六进制显示所给数字
  * @param  Line 行位置，范围：2
  * @param  Col 起始列位置，范围：16
  * @param  Number 要显示的数字，范围：0 - 0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1 - 8
  */
void LCD_ShowHexNum_Long(unsigned char Line, unsigned char Col, unsigned long Number, unsigned char Length) {
    LCD_SetCursor(Line, Col);
    for (; Length; Length--) {
        unsigned char digit = Number / LCD_Pow_Long(16, Length - 1) % 16;
        if (digit < 10) {
            LCD_WriteData(digit + '0');
        }
        else {
            LCD_WriteData(digit - 10 + 'A');
        }
    }
}
