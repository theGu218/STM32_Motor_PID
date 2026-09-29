#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;			
float Angle;			

int main(void)
{
	
	OLED_Init();		
	Servo_Init();		
	Key_Init();			
	
	
	OLED_ShowString(1, 1, "Angle:");
	/*
	每次按下按键，角度自增30度，到180度时直接归零，用OLED屏显示转过的角度方便量算，看看什么时候能搞个编码器吧
	*/
	
	while (1)
	{
		KeyNum = Key_GetNum();			
		if (KeyNum == 1)				
		{
			Angle += 30;				
			if (Angle > 180)			
			{
				Angle = 0;				
			}
		}
		Servo_SetAngle(Angle);			
		OLED_ShowNum(1, 7, Angle, 3);	
	}
}
