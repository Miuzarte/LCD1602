#include <REGX52.H>
#include "LCD1602.h"
#include "LCD1602_LongExt.h"

void Delay(unsigned int ms) {
    for (; ms; ms--) LCD_Delay();
}

void TestShowChar() {
    LCD_ShowChar(0, 1, 'H');
    LCD_ShowChar(1, 14, 'I');
}

void TestShowRepeatChar() {
    LCD_ShowRepeatChar(0, 1, 15, 'A');
    LCD_ShowRepeatChar(1, 0, 14, 'V');
}

void TestFlush() {
    LCD_ShowString(0, 0, "0123456789ABCDEF");
    LCD_ShowString(1, 0, "0123456789abcdef");
    Delay(1000);
    LCD_Flush(0, 2);
    LCD_Flush(1, 8);
}

void TestShowString() {
    LCD_ShowString(0, 1, "Hello, world!");
    LCD_ShowString(1, 2, "!dlrow ,olleH");
}

void TestShowNum() {
    LCD_ShowNum(0, 1, 1234, 5);
    LCD_ShowNum(1, 10, 54321, 5);
}

void TestShowSignedNum() {
    LCD_ShowSignedNum(0, 1, 1234, 5);
    LCD_ShowSignedNum(1, 9, -32100, 5);
}

void TestShowHexNum() {
    LCD_ShowHexNum(0, 1, 0x1234, 4);
    LCD_ShowHexNum(1, 11, 0xFEDC, 4);
}

void TestShowBinNum() {
    // 1010 0101 1010 1111
    //      1010 1111
    LCD_ShowBinNum(0, 0, 0xA5AF, 16);
    LCD_ShowBinNum(1, 4, 0xAF, 8);
}

void TestShowNum_Long() {
    LCD_ShowNum_Long(0, 1, 1234567890, 10);
    LCD_ShowNum_Long(1, 5, 1234567890, 10);
}

void TestShowSignedNum_Long() {
    LCD_ShowSignedNum_Long(0, 1, 1234567890, 10);
    LCD_ShowSignedNum_Long(1, 4, -1234567890, 10);
}

void TestShowHexNum_Long() {
    LCD_ShowHexNum_Long(0, 1, 0xABCDEFFF, 8);
    LCD_ShowHexNum_Long(1, 7, 0xABCDEFFF, 8);
}

void TestShowBinNum_Long0() {
    //    0 1011 1101 0
    // 1010 0101 1010 1111
    LCD_ShowBinNum_Long(0, 3, 0x17A, 10);
    LCD_ShowBinNum_Long(1, 0, 0xA5AF, 16);
}

void TestShowBinNum_Long1() {
    // 1010 1111 0011 0111
    // 1011 1111 1111 11
    LCD_ShowBinNum_Long(0, 0, 0x2BCDEFFF, 30);
}

void TestShowBinNum_Long2() {
    //  101 0111 1001 1011
    // 1101 1111 1111 111
    LCD_ShowBinNum_Long(0, 1, 0x2BCDEFFF, 30);
}

void TestShowBinNum_Long3() {
    //   10 1011 1100 1101
    // 1110 1111 1111 1111
    LCD_ShowBinNum_Long(0, 2, 0x2BCDEFFF, 30);
}

void TestShowBinNum_Long4() {
    //   10 1011 1100 1101
    // 1110 1111 1111 1111
    LCD_ShowBinNum_Long(0, 8, 0x2BCDEFFF, 30);
}

void TestDone() {
    LCD_ShowString(0, 0, "DONE");
}

typedef void (*TestFunc)();
const TestFunc testFuncs[] = {
    TestShowChar,
    TestShowRepeatChar,
    TestFlush,
    TestShowString,
    TestShowNum,
    TestShowSignedNum,
    TestShowHexNum,
    TestShowBinNum,
    TestShowNum_Long,
    TestShowSignedNum_Long,
    TestShowHexNum_Long,
    TestShowBinNum_Long0,
    TestShowBinNum_Long1,
    TestShowBinNum_Long2,
    TestShowBinNum_Long3,
    TestShowBinNum_Long4,
    TestDone,
};

void main() {
    unsigned char i;
    LCD_Init();
    Delay(1000);
    while (1) {
        LCD_ShowString(0, 0, "Starting in ");
        for (i = 3; i; i--) {
            LCD_ShowChar(1, 0, i + '0');
            Delay(1000);
        }
        LCD_WriteCommand(0x01);
        Delay(1000);

        for (i = 0; i < sizeof(testFuncs) / sizeof(testFuncs[0]); i++) {
            testFuncs[i]();
            Delay(2000);
            LCD_WriteCommand(0x01);
            Delay(1000);
        }

        while (P3_3);

    }
}
