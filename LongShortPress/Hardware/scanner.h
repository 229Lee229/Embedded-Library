#ifndef __SCANNER_H
#define __SCANNER_H


void Send_Manual_Cmd(void);
void Send_Continuous_Cmd(void);
void Send_ReadDeviceID_Cmd(void);

void Handle_RX_Scanner(void);   		// 处理接收到的scanner数据,并将数据传给usart1
void Handle_RX_CH340(void);				// 处理接收到的CH340数据,并将

void Send_Single_Cmd(int second);

void Send_Cmd_trig_Cmd(void);
void Send_Cmd_trig_ON_Cmd(void);
#endif
