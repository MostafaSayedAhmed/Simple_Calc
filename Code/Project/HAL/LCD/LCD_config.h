/*
 * LCD_config.h
 *
 *  Created on: Sep 11, 2022
 *      Author: Mostafa Sayed
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

#define RS PORTA_1
#define RW PORTA_2
#define E  PORTA_3
#define D4 PORTA_4
#define D5 PORTA_5
#define D6 PORTA_6
#define D7 PORTA_7

#define CLEAR_DISPLAY 0x01
#define CURSOR_MOVE_RIGHT 0x06
#define CURSOR_BLINK_ON 0x0f
#define BIT4MODE 0x32


#endif /* HAL_LCD_LCD_CONFIG_H_ */
