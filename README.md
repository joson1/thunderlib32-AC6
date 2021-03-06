# ThubnderLib3

thunderLib3是使用C++语言为STM32系列单片机编写的库，库底层直接操作寄存器，相比官方库依赖文件少，易于配置工程，但失去了灵活性，比如不能够很方便的设置GPIO速度，默认配置了最大速度。如果你追求功耗的灵活调控，不建议使用这个库。

## 关于使用C++进行单片机编程的一些想法

C++被称作是“更好的C语言”，C++在保留了对C语言语法兼容的基础上增加了很多的特性，如面向对象、重载、模板等等，这些特性给编程带来了更多的工具，使代码不论从可读性还是从功能实现上来说，都有着很大的提升。


但是面向对象式的编程对内存是有一定开销的，比如实例化了GPIO类，GPIO已经被初始化了，但是实例本身还会占用一定的空间，所以本库在开发时也保留了C语言风格的编程，你可以使用静态函数，可以不实例化类从而对外设进行初始化，可以一定程度上节省一些内存。


## 支持列表
### 开发环境

- KEILv5 MDK
- 编译器 ARM Compiler V6.1 更快的编译速度
- 支持CLANG，GNU++11标准
- 编码 utf-8


### 目前支持的型号


- stm32f10x

## 使用示例
```c++
#include "gpio.h"
#include "sys.h"


int main()
{

    GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
    LED1.set(0);
    sys.delay_ms(200);
    while(1){
		LED1.toggle();
		sys.delay_ms(500);
        
    }
    
}
```

## [文档](/doc)