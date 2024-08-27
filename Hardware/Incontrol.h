#ifndef __INCONTROL_H
#define __INCONTROL_H

void IRremote_Init(void);      // 红外遥控器初始化
uint8_t IRremote_Counttime();  // 红外遥控器计数时间

//定义全局变量
extern uint32_t IR_Receivecode;
extern uint8_t  IR_Receiveflag;

#endif

