#include <stdint.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"
#include "LCD1602.h"
#include "SYSTICK.h"
#include "PLL_80MHZ.h"

void PLL_Init80MHZ(void);

void init_port_E() {
   volatile unsigned long tmp;
   tmp = SYSCTL_RCGCGPIO_R;
   SYSCTL_RCGC2_R |= 0x10;
   GPIO_PORTE_LOCK_R = 0x4C4F434B;
   GPIO_PORTE_DIR_R = 0xC0;
   GPIO_PORTE_PUR_R = 0x3F;
   GPIO_PORTE_DEN_R = 0x3F;
}

unsigned char msg1[] ="-----------";
unsigned char *msg[] = {msg1};

unsigned char msg2[] ="----------------";
unsigned char *msgA[] = {msg2};

unsigned char y1[] ="Yirmilik";
unsigned char *y[] = {y1};

unsigned char o1[] ="Onluk---------";
unsigned char *o[] = {o1};

unsigned char b1[] ="Beslik--------";
unsigned char *b[] = {b1};

unsigned char bi1[] ="Birlik--------";
unsigned char *bi[] = {bi1};

unsigned char ya1[] ="Yarimlik------";
unsigned char *ya[] = {ya1};

unsigned char c1[] ="Ceyreklik-----";
unsigned char *c[] = {c1};

unsigned char m1[] ="Metelik-------";
unsigned char *m[] = {m1};

unsigned char k1[] ="Kurusluk------";
unsigned char *k[] = {k1};

unsigned char bosluk[] =" ";
unsigned char *bos[] = {bosluk};

unsigned char nokta[] =".";
unsigned char *nn[] = {nokta};

int main(void){
	volatile unsigned long delay;
	init_port_E();
	int buton10,buton1,butonN,butonN1,butonN10,butonENTER;
    unsigned int counter1=0,counter2=0,counter3=0,counter4=0;
    int yirmilik,onluk,beslik,birlik,yarimlik,ceyreklik,metelik,kurusluk;
    PLL_Init80MHZ();
    SysTick_Init();
    LCD1602_Init();
    r:

	counter1=0,counter2=0,counter3=0,counter4=0;

	LCD1602_DisplayPosition(LINE1,13);
	LCD1602_DisplayString(bos[0]);
    LCD1602_DisplayPosition(LINE1,0);
    LCD1602_DisplayString(msg[0]);
    LCD1602_DisplayPosition(LINE2,0);
    LCD1602_DisplayString(msgA[0]);

  while(1)
  {
        buton10 = GPIO_PORTE_DATA_R & 0b00001;
        buton1 =  GPIO_PORTE_DATA_R & 0b00010;
        butonN = GPIO_PORTE_DATA_R & 0b00100;
        butonN1 = GPIO_PORTE_DATA_R & 0b01000;
        butonN10 =  GPIO_PORTE_DATA_R & 0b10000;
        butonENTER = GPIO_PORTE_DATA_R & 0b100000;
        if(buton10==0){
        	counter1++;
        	if(counter1==10){
        		counter1=0;
        	}
        }
        if(butonN==0){
        	LCD1602_DisplayPosition(LINE1,13);
        	LCD1602_DisplayString(nn[0]);
        	SysTick_Delay1ms(275);
        	butonN = GPIO_PORTE_DATA_R & 0b00100;
        	if(butonN==0){
        		SysTick_Delay1ms(2725);
        		butonN = GPIO_PORTE_DATA_R & 0b00100;
        		if(butonN==0)
        			goto r;
        	}
                }
        if(buton1==0){
                	counter2++;
                	if(counter2==10){
                		counter2=0;
                	}
                }
        if(butonN1==0){
                	counter3++;
                	if(counter3==10){
                		counter3=0;
                	}
                }
        if(butonN10==0){
                	counter4++;
                	if(counter4==10){
                		counter4=0;
                	}
                }


        if(butonENTER==0){

        	yirmilik=(counter1*10)/20;
                	counter1=counter1-(yirmilik*2);
                	if(yirmilik>0){
                		LCD1602_DisplayPosition(LINE2,0);
                		LCD1602_DisplayDec(yirmilik);
                		LCD1602_DisplayPosition(LINE2,2);
                		LCD1602_DisplayString(y[0]);
                        LCD1602_DisplayPosition(LINE1,11);
                        LCD1602_DisplayDec(counter1);
                		SysTick_Delay1ms(3000);
                	}
                	onluk=counter1;
                	counter1=counter1-onluk;
                	if(onluk>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(onluk);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(o[0]);
						LCD1602_DisplayPosition(LINE1,11);
						LCD1602_DisplayDec(counter1);
						SysTick_Delay1ms(3000);
                	}
                	beslik=counter2/5;
                	counter2=counter2-(beslik*5);
                	if(beslik>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(beslik);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(b[0]);
						LCD1602_DisplayPosition(LINE1,12);
						LCD1602_DisplayDec(counter2);
						SysTick_Delay1ms(3000);
                	}
                	birlik=counter2;
                	counter2=0;
                	if(birlik>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(birlik);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(bi[0]);
						LCD1602_DisplayPosition(LINE1,12);
						LCD1602_DisplayDec(counter2);
						SysTick_Delay1ms(3000);
                	}
                	yarimlik=counter3/5;
                	counter3=counter3-(yarimlik*5);
                	if(yarimlik>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(yarimlik);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(ya[0]);
						LCD1602_DisplayPosition(LINE1,14);
						LCD1602_DisplayDec(counter3);
						SysTick_Delay1ms(3000);
                	}
                	if(counter3>=2 && counter4>=5){
                		ceyreklik=1;
                		counter3=counter3-2;
                		counter4=counter4-5;
                	}else if(counter3>2 && counter4<5){
                		ceyreklik=1;
                		counter3=counter3-3;
                		counter4=counter4+5;
                	}else
                		ceyreklik=0;
                	if(ceyreklik>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(ceyreklik);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(c[0]);
						LCD1602_DisplayPosition(LINE1,14);
						LCD1602_DisplayDec(counter3);
						LCD1602_DisplayPosition(LINE1,15);
						LCD1602_DisplayDec(counter4);
						SysTick_Delay1ms(3000);
                	}
                	metelik=counter3;
                	counter3=counter3-metelik;
                	if(metelik>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(metelik);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(m[0]);
						LCD1602_DisplayPosition(LINE1,14);
						LCD1602_DisplayDec(counter3);
						SysTick_Delay1ms(3000);
                	}
                	kurusluk=counter4;
                	counter4=0;
                	if(kurusluk>0){
						LCD1602_DisplayPosition(LINE2,0);
						LCD1602_DisplayDec(kurusluk);
						LCD1602_DisplayPosition(LINE2,2);
						LCD1602_DisplayString(k[0]);
						LCD1602_DisplayPosition(LINE1,15);
						LCD1602_DisplayDec(counter4);
						SysTick_Delay1ms(3000);
                	}
                        }

        LCD1602_DisplayPosition(LINE1,11);
        LCD1602_DisplayDec(counter1);
        LCD1602_DisplayPosition(LINE1,12);
        LCD1602_DisplayDec(counter2);
        LCD1602_DisplayPosition(LINE1,14);
        LCD1602_DisplayDec(counter3);
        LCD1602_DisplayPosition(LINE1,15);
        LCD1602_DisplayDec(counter4);
        SysTick_Delay1ms(100);
    }
}
