#include<reg51.h>


#define lcd P1

sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;

char i=0;
char num_arr[10];

void LCD_Init();
void LCD_SendCommand(unsigned char);
void LCD_SendData(unsigned char);
void msDelay(unsigned char);
void LCD_SendString(unsigned char *);
void LCD_Clear();

//lcd initialization

void LCD_Init()
{
	LCD_SendCommand(0x80);
	LCD_SendCommand(0x38);
	LCD_SendCommand(0x01);
	LCD_SendCommand(0x0c);
	LCD_SendCommand(0x06);
}

// send commands

void LCD_SendCommand(unsigned char ch)
{
	lcd = ch;
	rs = 0;
	rw = 0;
	en = 1;
	msDelay(20);
	en = 0;
	
}

// send data

void LCD_SendData(unsigned char ch)
{
	lcd = ch;
	rs = 1;
	rw = 0;
	en = 1;
	msDelay(20);
	en = 0;
}

// delay

void msDelay(unsigned char t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	for(j = 0; j < 500; j++);
}

// send a string of data

void LCD_SendString(unsigned char *p)
{
	while(*p != '\0')
	{
		LCD_SendData(*p);
		p++;
	}
}


void LCD_Clear()
{
	msDelay(100);
	msDelay(100);
	msDelay(100);
	msDelay(100);
	LCD_SendCommand(0x01);
	msDelay(100);
}


void num_package(long int num)
{
    i=0;
    while(num)
    {
        num_arr[i]=(num%10)+'0';
        num=num/10;
        i++;
    }
}

void lcdDisplayNum(long int num)
{
    if(num==0)
    {
        LCD_SendData('0');
    }
    else
    {
        if((num>>31)&1)
        {
            LCD_SendData('-');
            num=num*-1;
            num_package(num);

            while(i>0)
            {
                LCD_SendData(num_arr[--i]);
            }

        }
        else
        {
            num_package(num);
            while(i>0)
            {
                LCD_SendData(num_arr[--i]);
            }
        }
    }
}


