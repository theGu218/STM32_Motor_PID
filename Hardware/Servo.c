#include "stm32f10x.h"                  // Device header
#include "PWM.h"


void Servo_Init(void)
{
	PWM_Init();									
}


void Servo_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);	
	
}
/*
	这个是根据舵机的控制协议来算的，
	角度为0度时，高电平时间为0.5ms，CCR为500，
	角度90，高电平时间为1.5ms，CCR为1500，
	角度180，高电平时间为2.5ms，CCR为2500，
	线性方程算一下就算出来角度和CCR的关系
*/
