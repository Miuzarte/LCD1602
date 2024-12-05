#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Delay();
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_SetCursor(unsigned char Line, unsigned char Col);
void LCD_Init();
void LCD_ShowChar(unsigned char Line, unsigned char Col, char Char);
void LCD_ShowRepeatChar(unsigned char Line, unsigned char ColStart, unsigned char ColEnd, char Char);
void LCD_Flush(unsigned char Line, unsigned char ColStart);
void LCD_ShowString(unsigned char Line, unsigned char Col, char* String);
void LCD_ShowNum(unsigned char Line, unsigned char Col, unsigned int Number, unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line, unsigned char Col, int Number, unsigned char Length);
void LCD_ShowHexNum(unsigned char Line, unsigned char Col, unsigned int Number, unsigned char Length);
void LCD_ShowBinNum(unsigned char Line, unsigned char Col, unsigned int Number, unsigned char Length);

#endif
