# IIC

## 使用示例

```c++


```

## 实例化IIC


IIC::IIC(const GPIO &SCL,const GPIO &SDA)

```c++
	
GPIO SCL(GPIOB,GPIO_PIN_7);
GPIO SDA(GPIOB,GPIO_PIN_8);

IIC myIIC(SCL,SDA);

```

## 发送起始信号
IIC::start()


```c++

myIIC.start();

```

## 发送终止信号


IIC::stop()

```c++
myIIC.stop();
```

## 发送8位数据


IIC::write(uint8_t val)

```c++
myIIC.write(0x01);
```

## 读取8位数据

IIC::read(uint8_t ack)


ack:是否回应ack    0：不回应  1：回应

```c++
char res;
res = read(1);


```