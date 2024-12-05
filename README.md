# 51 单片机 LCD1602 驱动

## 魔改基于 [[江协科技 51单片机入门教程资料]](https://jiangxiekeji.com/download.html#51)

### Features

原体积: `data=37.0 code=541`

- 行列位置从 0 开始数
- 改进循环逻辑, 去除多余变量
- 可选指数计算实现 `PowSelector.h`
  - 数组查表(默认) `data=45.0 code=405`
  - 函数查表 `data=27.0 code=472`
  - 硬算 `data=27.0 code=457`
- ~~去除二进制显示~~
- 重新实现二进制显示, 替代模取值, 改用位运算实现, 且支持显示大于 16 位的值时自动换行
- 增加 `LCD_ShowRepeatChar()`、`LCD_Flush()`
- 扩展 32 位类型显示 `LCD1602_LongExt.h`
