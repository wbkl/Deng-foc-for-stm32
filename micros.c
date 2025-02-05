#include "stm32f10x.h"                  // Device header

// 定义一个全局变量来存储系统启动时的 SysTick 计数值
static uint32_t SysTick_start_value;

// 初始化 SysTick 定时器
void SysTick_Init(void) {
    // 设置 SysTick 时钟源为 HCLK（假设 HCLK 为 72MHz）
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    // 计算 SysTick 定时器的重载值，使定时器以 1 微秒的时间间隔递减
    // 72MHz 时钟频率，每 72 个时钟周期为 1 微秒
    SysTick_Config(SystemCoreClock / 1000000);
    // 记录系统启动时的 SysTick 计数值
    SysTick_start_value = SysTick->VAL;
}
// 实现类似 micros() 的函数
uint32_t micros(void) {
    uint32_t current_value = SysTick->VAL;
    uint32_t elapsed_ticks;
    // 计算经过的 SysTick 计数值
    if (current_value <= SysTick_start_value) {
        elapsed_ticks = SysTick_start_value - current_value;
    } else {
        // 处理 SysTick 计数器溢出的情况
        elapsed_ticks = SysTick->LOAD + 1 + SysTick_start_value - current_value;
    }
    // 将经过的计数值转换为微秒数
    return elapsed_ticks;
}
int micros_stm(void) {
    // 初始化 SysTick 定时器
    SysTick_Init();
    while (1) {
        // 获取自系统启动以来经过的微秒数
        uint32_t elapsed_micros = micros();
				return elapsed_micros;
    }
}
