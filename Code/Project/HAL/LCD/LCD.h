/*
 * LCD.h
 *
 *  Created on: Sep 10, 2022
 *      Author: Mostafa Sayed
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "LCD_config.h"
#include "../../Units.h"

#define cal(x,y) (x+y*64)

void LCD_init();
void LCD_SendCMD(unit8 cmd);
void LCD_SendData(unit8 data);

void LCD_SendString(unit8* data);
void LCD_SendStringxy(unit8* data,unit8 x,unit8 y);

#endif /* HAL_LCD_LCD_H_ */
