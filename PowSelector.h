// LCD_Pow 实现方式
#define LCD_POW_METHOD 1

#if LCD_POW_METHOD == 1 // 数组查表

static const unsigned int _LCD_Pow_D[] = { 1, 10, 100, 1000, 10000 };
static const unsigned int _LCD_Pow_H[] = { 0x1, 0x10, 0x100, 0x1000 };
#define LCD_Pow(base, exp) \
    (base == 10 ? _LCD_Pow_D[exp] : \
    (base == 16 ? _LCD_Pow_H[exp] : 0))

#elif LCD_POW_METHOD == 2 // 函数查表

static unsigned int _LCD_Pow(unsigned char base, unsigned char exp) {
    if (base == 10) {
        switch (exp) {
        case 0: return 1;
        case 1: return 10;
        case 2: return 100;
        case 3: return 1000;
        case 4: return 10000;
        }
    }
    else if (base == 16) {
        switch (exp) {
        case 0: return 0x1;
        case 1: return 0x10;
        case 2: return 0x100;
        case 3: return 0x1000;
        }
    }
    return 0;
}
#define LCD_Pow(base, exp) _LCD_Pow(base, exp)

#elif LCD_POW_METHOD == 3 // 硬算

static unsigned int _LCD_Pow(unsigned char base, unsigned char exp) {
    unsigned int result = 1;
    for (; exp; exp--) {
        result *= base;
    }
    return result;
}

#define LCD_Pow(base, exp) _LCD_Pow(base, exp)

#endif