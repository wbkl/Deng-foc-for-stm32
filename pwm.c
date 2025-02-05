#include "stm32f10x.h"                  // Device header

void pwm_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIO引脚
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能定时器
	
	GPIO_InitTypeDef GPIO_InitStructure;//GPIO结构体
	TIM_TimeBaseInitTypeDef TIM_TimeInitStructure;//tim结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//输出对比结构体
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//初始化PA0
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置输出速度为50mhz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//初始化PA1
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置输出速度为50mhz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//初始化PA2
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置输出速度为50mhz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//初始化PA3
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置输出速度为50mhz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeInitStructure.TIM_ClockDivision=0;
	TIM_TimeInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeInitStructure.TIM_Period=100-1;
	TIM_TimeInitStructure.TIM_Prescaler=36-1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeInitStructure);//初始化TIM2
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//通道1
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//通道2
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//通道3
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//通道4
	
	//预装载
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//使能定时器
	TIM_Cmd(TIM2,ENABLE);
	
}


void setcompare(float Ua,float Ub,float Uc)
{
	TIM_SetCompare1(TIM2,Ua*255);
	TIM_SetCompare2(TIM2,Ub*255);
	TIM_SetCompare3(TIM2,Uc*255);
}
