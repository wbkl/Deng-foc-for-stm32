#include <stdio.h>
#include "pwm.h"
#include <math.h>
#include "stm32f10x.h"                  // Device header
#include "micros.h"

//初始化变量
#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
/*
定义变量
*/
float pi=3.1415926;
float voltage_power_supply=12.6;
float shaft_angle=0,open_loop_timestamp=0;
float zero_electric_angle=0,Ualpha,Ubeta=0,Ua=0,Ub=0,Uc=0,dc_a=0,dc_b=0,dc_c=0;

//电角度求解
float _electricalAngle(float shaft_angle,int pole_pairs){
return (shaft_angle * pole_pairs);
}

//归一化角度{0,2pi}
float _normalizeAngle(float angle){
	float a = fmod(angle,2*pi);
	return a >=0?a:(a+2*pi);
}

//设置占空比
void setPwm(float Ua,float Ub,float Uc)
{
	pwm_Init();
  dc_a = _constrain(Ua / voltage_power_supply, 0.0f , 1.0f );
  dc_b = _constrain(Ub / voltage_power_supply, 0.0f , 1.0f );
  dc_c = _constrain(Uc / voltage_power_supply, 0.0f , 1.0f );
	
	/*
	写入占空比
	Ua--compare1;
	Ub--compare2;
	Uc--compare3;
	*/
	void setcompare(float Ua,float Ub,float Uc);
}

//变换
void setPhaseVoltage(float Uq,float Ud,float angle_el)
{
	angle_el = _normalizeAngle(angle_el + zero_electric_angle);
	 // 帕克逆变换
  Ualpha =  -Uq*sin(angle_el); 
  Ubeta =   Uq*cos(angle_el); 
	//克拉克逆变换
	Ua = Ualpha + voltage_power_supply/2;
  Ub = (sqrt(3)*Ubeta-Ualpha)/2 + voltage_power_supply/2;
  Uc = (-Ualpha-sqrt(3)*Ubeta)/2 + voltage_power_supply/2;
	setPwm(Ua,Ub,Uc);
}

//开环速度控制
float velocityOpenloop(float target_velocity){
  unsigned long now_us = micros_stm();
	 float Ts = (now_us - open_loop_timestamp) * 1e-6f;
  if(Ts <= 0 || Ts > 0.5f) Ts = 1e-3f;
  shaft_angle = _normalizeAngle(shaft_angle + target_velocity*Ts);
  float Uq = voltage_power_supply/3;
  setPhaseVoltage(Uq,  0, _electricalAngle(shaft_angle, 7));
  open_loop_timestamp = now_us;  //用于计算下一个时间间隔
  return Uq;
}







