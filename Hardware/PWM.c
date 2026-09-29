#include "stm32f10x.h"                  // Device header

//该项目使用的GPIO口为PA1口，然后定时器是TIM2，首先写PWM的模块，旨在初始化PWM和设置占空比等

void PWM_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //开启GPIOA和TIM2的时钟			
	
	
	GPIO_InitTypeDef GPIO_InitStructure;                     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);			

/*
	对于GPIO口的初始化，首先这里用的是复用推挽输出
	因为pwm不是由CPU控制的，而且由stm32内部的定时器产生的，所以说复用
	推挽是为了使这个GPIO口能输出稳定的高低电平，其余参数正常配置即可
*/	
																	
	
	
	TIM_InternalClockConfig(TIM2); //内部APB总线，用来配置特定的定时器时钟，比如这里是TIM2

/*	
	下面就是配置时基单元，时基单元初始化，prescaler就是psc，然后TIM.Period就是arr的值，
	这其中频率 = 72Mhz /（ARR + 1 ）/（PSC + 1）
	占空比为 = CCR / （ARR+1）
	其余参数正常配置
*/
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;				
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;				
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);             
	
	 
	 TIM_OCInitTypeDef TIM_OCInitStructure;	    //在栈上分配一个结构体变量						
	TIM_OCStructInit(&TIM_OCInitStructure);     //初始化该结构体                   
	                                                                
	                                                               
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    
	/*
		这里模式选择PWM1，也就是cnt > = ccr的时候输出无效电平，
		然后cnt<crr的时候输出有效电平
	*/
	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //这个相当于规定有效电平就是高电平，也就是3.3V 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //使能
	TIM_OCInitStructure.TIM_Pulse = 0;		                        //CCR初始值为0						
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);                        
	
	
	TIM_Cmd(TIM2, ENABLE);	//使能，开启之后cnt会一直自增计数		
}


void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);		//compare其实就是ccr的值，需要多少直接写就行了
	
}
