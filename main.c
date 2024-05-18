#include<reg51.h>

#include "LCDD.h"

	void lcdDisplayTime();
void lcdDisplayDate();
void MODE_1();
//void MODE_2();


	char	hours=23;
	char minute=0;
	char second=0;         // intialization

char day = 18;
char month =5;
int year =2024;

char *days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat","Sun"};



void main()
{

	LCD_Init();

	LCD_SendCommand(0x83);     
	LCD_SendString("WELCOME") ;
	LCD_SendCommand(0xC3);     //Second Line
	LCD_SendString(" Eman *_*");
	
	LCD_Clear();
	LCD_SendString("  	MODE 24	:) ");   //mode of 24
	LCD_Clear();
	
	 LCD_SendCommand(0x80); 
	LCD_SendString("DATE:");
	LCD_SendCommand(0xC0);     
	LCD_SendString("CLOCK:") ;
	LCD_Clear();

	while(1)
	{
	
		MODE_1();
	}
	
}


void MODE_1()
{			
second++;
if(second==60)
{
    second = 0;
    minute++;	
    if(minute==60)
    {
        minute = 0;
        hours++;	
        
        if(hours==24)
        {
            hours = 0;
            day++;
            if (day > 31)
            {
                day = 1;
                month++;
                if (month > 12) 
                {
                    month = 1;
                    year++;			
                }
            }
        }
    }
}   
lcdDisplayDate();
lcdDisplayTime();
msDelay(1);
	}
	


void lcdDisplayTime()
{
	if((minute > 0 && second == 0)||(hours > 0 && minute==0 && second == 0 ))
{
			LCD_SendCommand(0x01);
		}
		
    LCD_SendCommand(0xC0);     
    lcdDisplayNum(hours);
    LCD_SendData(':');
    lcdDisplayNum(minute);
    LCD_SendData(':');
    lcdDisplayNum(second);

    LCD_SendCommand(0xCD);     
    if (hours >= 12) {
        LCD_SendString("PM");
    } else {
        LCD_SendString("AM");
    }

}
void lcdDisplayDate()
{
	LCD_SendCommand(0x80);     
 lcdDisplayNum(day);   
	LCD_SendData('/');
    lcdDisplayNum(month);
    LCD_SendData('/');
    lcdDisplayNum(year);	
	LCD_SendCommand(0x8C);     
	 LCD_SendString(days[(day % 7)-1]);
}