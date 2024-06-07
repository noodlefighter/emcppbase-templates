#pragma once

#include "embase_macros_bits.h"

#define __PORT_PINS   16
#define __PORTA       0
#define __PORTB       1
#define __PORTC       2
#define __PORTD       3
#define __PORTE       4

// 定义pin值
#define __PIN_VALUE(port, num)    ( SBF(port, 4) | num )
#define __PIN_TO_PORT(pin)        ( BITS_GET(pin, 4, 4) )
#define __PIN_TO_NUM(pin)         ( BITS_GET(pin, 0, 4) )

#define PIN_PA0     __PIN_VALUE(__PORTA, 0)
#define PIN_PA1     __PIN_VALUE(__PORTA, 1)
#define PIN_PA2     __PIN_VALUE(__PORTA, 2)
#define PIN_PA3     __PIN_VALUE(__PORTA, 3)
#define PIN_PA4     __PIN_VALUE(__PORTA, 4)
#define PIN_PA5     __PIN_VALUE(__PORTA, 5)
#define PIN_PA6     __PIN_VALUE(__PORTA, 6)
#define PIN_PA7     __PIN_VALUE(__PORTA, 7)
#define PIN_PA8     __PIN_VALUE(__PORTA, 8)
#define PIN_PA9     __PIN_VALUE(__PORTA, 9)
#define PIN_PA10    __PIN_VALUE(__PORTA, 10)
#define PIN_PA11    __PIN_VALUE(__PORTA, 11)
#define PIN_PA12    __PIN_VALUE(__PORTA, 12)
#define PIN_PA13    __PIN_VALUE(__PORTA, 13)
#define PIN_PA14    __PIN_VALUE(__PORTA, 14)
#define PIN_PA15    __PIN_VALUE(__PORTA, 15)

#define PIN_PB0     __PIN_VALUE(__PORTB, 0)
#define PIN_PB1     __PIN_VALUE(__PORTB, 1)
#define PIN_PB2     __PIN_VALUE(__PORTB, 2)
#define PIN_PB3     __PIN_VALUE(__PORTB, 3)
#define PIN_PB4     __PIN_VALUE(__PORTB, 4)
#define PIN_PB5     __PIN_VALUE(__PORTB, 5)
#define PIN_PB6     __PIN_VALUE(__PORTB, 6)
#define PIN_PB7     __PIN_VALUE(__PORTB, 7)
#define PIN_PB8     __PIN_VALUE(__PORTB, 8)
#define PIN_PB9     __PIN_VALUE(__PORTB, 9)
#define PIN_PB10    __PIN_VALUE(__PORTB, 10)
#define PIN_PB11    __PIN_VALUE(__PORTB, 11)
#define PIN_PB12    __PIN_VALUE(__PORTB, 12)
#define PIN_PB13    __PIN_VALUE(__PORTB, 13)
#define PIN_PB14    __PIN_VALUE(__PORTB, 14)
#define PIN_PB15    __PIN_VALUE(__PORTB, 15)

#define PIN_PC0     __PIN_VALUE(__PORTC, 0)
#define PIN_PC1     __PIN_VALUE(__PORTC, 1)
#define PIN_PC2     __PIN_VALUE(__PORTC, 2)
#define PIN_PC3     __PIN_VALUE(__PORTC, 3)
#define PIN_PC4     __PIN_VALUE(__PORTC, 4)
#define PIN_PC5     __PIN_VALUE(__PORTC, 5)
#define PIN_PC6     __PIN_VALUE(__PORTC, 6)
#define PIN_PC7     __PIN_VALUE(__PORTC, 7)
#define PIN_PC8     __PIN_VALUE(__PORTC, 8)
#define PIN_PC9     __PIN_VALUE(__PORTC, 9)
#define PIN_PC10    __PIN_VALUE(__PORTC, 10)
#define PIN_PC11    __PIN_VALUE(__PORTC, 11)
#define PIN_PC12    __PIN_VALUE(__PORTC, 12)
#define PIN_PC13    __PIN_VALUE(__PORTC, 13)
#define PIN_PC14    __PIN_VALUE(__PORTC, 14)
#define PIN_PC15    __PIN_VALUE(__PORTC, 15)

#define PIN_PD0     __PIN_VALUE(__PORTD, 0)
#define PIN_PD1     __PIN_VALUE(__PORTD, 1)
#define PIN_PD2     __PIN_VALUE(__PORTD, 2)
#define PIN_PD3     __PIN_VALUE(__PORTD, 3)
#define PIN_PD4     __PIN_VALUE(__PORTD, 4)
#define PIN_PD5     __PIN_VALUE(__PORTD, 5)
#define PIN_PD6     __PIN_VALUE(__PORTD, 6)
#define PIN_PD7     __PIN_VALUE(__PORTD, 7)
#define PIN_PD8     __PIN_VALUE(__PORTD, 8)
#define PIN_PD9     __PIN_VALUE(__PORTD, 9)
#define PIN_PD10    __PIN_VALUE(__PORTD, 10)
#define PIN_PD11    __PIN_VALUE(__PORTD, 11)
#define PIN_PD12    __PIN_VALUE(__PORTD, 12)
#define PIN_PD13    __PIN_VALUE(__PORTD, 13)
#define PIN_PD14    __PIN_VALUE(__PORTD, 14)
#define PIN_PD15    __PIN_VALUE(__PORTD, 15)

#define PIN_PE0     __PIN_VALUE(__PORTE, 0)
#define PIN_PE1     __PIN_VALUE(__PORTE, 1)
#define PIN_PE2     __PIN_VALUE(__PORTE, 2)
#define PIN_PE3     __PIN_VALUE(__PORTE, 3)
#define PIN_PE4     __PIN_VALUE(__PORTE, 4)
#define PIN_PE5     __PIN_VALUE(__PORTE, 5)
#define PIN_PE6     __PIN_VALUE(__PORTE, 6)
#define PIN_PE7     __PIN_VALUE(__PORTE, 7)
#define PIN_PE8     __PIN_VALUE(__PORTE, 8)
#define PIN_PE9     __PIN_VALUE(__PORTE, 9)
#define PIN_PE10    __PIN_VALUE(__PORTE, 10)
#define PIN_PE11    __PIN_VALUE(__PORTE, 11)
#define PIN_PE12    __PIN_VALUE(__PORTE, 12)
#define PIN_PE13    __PIN_VALUE(__PORTE, 13)
#define PIN_PE14    __PIN_VALUE(__PORTE, 14)
#define PIN_PE15    __PIN_VALUE(__PORTE, 15)


#include "SoftwareSPI.h"

extern SoftwareSPI SPI;
