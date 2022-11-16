/***************************************************************************************
 * Project  :CAN-Normal-STM32
 * Describe :Use two CAN HAT to send and receive each other
 * Experimental Platform :STM32F103C8T6 + CAN HAT
 * Hardware Connection :STM32F103 -> CAN HAT
 *			3V3	 ->	3V3					PA11 -> CANRX
 *			GND	 ->	GND					PA12 -> CANTX
 * Library Version :ST_V3.5
 * Author		   :Christian
 * Web Site		   :www.seengreat.com
***************************************************************************************/
#include "usart.h"
#include "delay.h"
#include "can.h"

u8 CAN_BUF_SEND[8]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
u8 CAN_BUF_RECEIVE[8];

int main(void)
{
	u8 res,len,i;
	SystemInit();
	Uart1Init(9600,0,0);
	printf("\r\n---------- CAN-HAT ----------\r\n");
	printf("STM32F103C8T6 ");
	printf("V1.0.0 Build 2022/06/18 09:22\r\n");
	delay_init();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//Mode:Normal,Baud:500Kbps
	while(1)
	{
		printf("\r\nStart sending data:");
		res=Can_Send_Msg(CAN_BUF_SEND,8);
		if(res)
			printf("send ok\r\n");
		len=Can_Receive_Msg(CAN_BUF_RECEIVE);
		printf("len:%d\r\n",len);
		if(len)
		{
			printf("The received data is:");
			for(i=0;i<len;i++)
			{
				printf("%02X ",CAN_BUF_RECEIVE[i]);
			}
		}
		delay_ms(500);
	}
}

