#include <REGX52.H>
#include "LCD1602.h"

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
