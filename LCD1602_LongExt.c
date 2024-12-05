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

/**
  * @brief  指定位置开始以二进制显示所给数字
  * @param  Line 行位置，范围: 2
  * @param  Col 起始列位置，范围: 16
  * @param  Number 要显示的数字，范围: 0 - 0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围: 1 - 32
  * @note   Length > 16 时, 必须使用两行显示, 此时将无视 Line 参数, 且给予的 Col 参数不足以显示 Length 位时会自动调整
  *
  * @code   codes and results:
  *
  *         ---
  *
  *         \/\/ 1010 1111 0011 0111
  *
  *         \/\/ 1011 1111 1111 11
  *
  *         LCD_ShowBinNum_Long(0, 0, 0x2BCDEFFF, 30);
  *
  *         ---
  *
  *         \/\/  101 0111 1001 1011
  *
  *         \/\/ 1101 1111 1111 111
  *
  *         LCD_ShowBinNum_Long(0, 1, 0x2BCDEFFF, 30);
  *
  *         ---
  *
  *         \/\/   10 1011 1100 1101
  *
  *         \/\/ 1110 1111 1111 1111
  *
  *         LCD_ShowBinNum_Long(0, 2, 0x2BCDEFFF, 30);
  *
  *         LCD_ShowBinNum_Long(0, 8, 0x2BCDEFFF, 30); // 从 8 开始不足以显示 30 位, 自动调整为 2
  */
void LCD_ShowBinNum_Long(unsigned char Line, unsigned char Col, unsigned long Number, unsigned char Length) {
    if (Length <= 16) {
        LCD_ShowBinNum(Line, Col, Number, Length);
    }
    else {
        if (Col > 32 - Length) { Col = 32 - Length; } // 给予的 Col 不合理 (不足以显示 Length 位)
#define LowBitsLen Length - (16 - Col)
        LCD_ShowBinNum(0, Col, (Number >> (LowBitsLen)) & 0xFFFF, 16 - Col); // high bits
        LCD_ShowBinNum(1, 0, Number & (0xFFFF >> (16 - (LowBitsLen))), LowBitsLen); // low bits
    }
}
