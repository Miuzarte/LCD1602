#ifndef __LCD1602_LONGEXT_H__
#define __LCD1602_LONGEXT_H__

long LCD_Pow_Long(unsigned char base, unsigned char exp);
void LCD_ShowNum_Long(unsigned char Line, unsigned char Col, unsigned long Number, unsigned char Length);
void LCD_ShowSignedNum_Long(unsigned char Line, unsigned char Col, long Number, unsigned char Length);
void LCD_ShowHexNum_Long(unsigned char Line, unsigned char Col, unsigned long Number, unsigned char Length);

#endif
