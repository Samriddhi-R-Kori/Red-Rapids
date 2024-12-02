
// ADC 0   RA0  //
// ADC 1   RA1  //  i/p As Analog
// ADC 2   RA2  //
// ADC 3   RA3  //

#include <stdio.h>
#include <stdlib.h>
#include "pic16f1783.h"
#include <xc.h>                                    //PIC hardware mapping



#define RFID RA4    //  High to Low
#define PIR RA5    // Low to High

#define G1 RC0
#define R1 RC1
#define Y1 RC4

#define G2 RC5
#define R2 RC6
#define Y2 RC7



#define _XTAL_FREQ 8000000                 //Used by the XC8 delay_ms(x) macro

#define Timer_Value 0x4E                   //timer value for 10 ms

#pragma config FOSC = HS, WDTE=OFF, PWRTE=OFF, CP=OFF, CPD=OFF, BOREN=OFF
#pragma config WRT=OFF, LVP=OFF


unsigned int x=0x0000;

void delay(void)
{
    unsigned char i;
    for(i=0;i<250;i++);

}

void del_1ms()
 {
    unsigned char i;
    for(i=0;i<=125;i++);
 }


void del_2ms()
 {
    unsigned int i;
    for(i=0;i<=500;i++);
 }

void del_1sec()
{
  unsigned int i;
  for(i=0;i<=2250;i++);
}
void del_10ms()
 {
    unsigned char i;
    for(i=0;i<5;i++)
    {
     del_2ms();
    }
 }



void del_100ms()
 {
    unsigned char i;
    for(i=0;i<10;i++)
    {
     del_10ms();
    }

 }


void del_500ms()
{
    unsigned char i;
    for(i=0;i<12;i++)
    {
     del_100ms();
    }

}






/***********************************************************************************/
/* Initializes ADC*/
/* channel 1*/
/***********************************************************************************/
void ADC_INIT()
{
  ADCON0=0x00;
  ADCON1 = 0xb0;       //80                //only chanel 0 RA0 is analog, remaining digital
  ADCON2=0x0F;
}

int ADC_PROCESS(unsigned char chanel)
{
    unsigned int read_adc=0x0000;
    //chanel = chanel&0x03;
   
    if(chanel==0x00)
    {
     ADCON0=01;
    }
     if(chanel==0x01)
    {
     ADCON0=05;
    }
    
    delay();        
    delay();        
     GO = 1;
        while (GO) continue;                        
        read_adc=ADRESH;
        ADRESH=0x00;
        // Controler(0x80);
        //Data_Display(Adc_Val);
        //Adc_Val=ADRESL;
        // Controler(0xC0);
        //Data_Display(Adc_Val);
        read_adc=(read_adc<<8);
        read_adc=(read_adc | ADRESL);
        ADRESL=0x00;
        ADCON0=0x00;
        return read_adc;
}





void main()
{
       
     unsigned int adc_value=0,adc_value1=0,x=0,y=0,Color=0,Sound=0;;
     unsigned char lock1=0,lock2=0,gaurd=0,grd_cnt=0,cnt=0,pir1=0;
     unsigned int result;
     unsigned int temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,temp7=0;
     unsigned int temp8=0,temp9=0,temp10=0,temp11=0,temp12=0,temp13=0,temp14=0,temp15=0;
     float f=0.0;

    TRISA=0xff;
    TRISB=0x01;      // RB0 as i/p  >> KEY
    TRISC=0x00;
    
    ANSELA=0x0F;
    ANSB0=0;
  
    
    PORTB=0x00;
    
  
    
    
   
    G1=0;R1=0;Y1=0;
    G2=0;R2=0;Y2=0;
    
       
    ADC_INIT();

    delay();delay();delay();delay();
    del_100ms();del_100ms();
   
    delay();
   
    delay();
  
    delay();delay();

    
    delay();delay();delay();delay();
   
    delay();delay();
    
    
       
                
   
    delay();
    delay();
    delay();
    delay();   
    
 
    
   
 
    
     for(x=0;x<5;x++)   
        {
          //G1=1;R1=1;Y1=1;G2=1;R2=1;Y2=1;
            PORTC=0x90;
           del_500ms();del_500ms(); 
          //G1=0;R1=0;Y1=0;G2=0;R2=0;Y2=0;
            PORTC=0x00;
           del_500ms();del_500ms(); 
        
        }   
    
    
    while(1)
    {
        PORTC=0x41;
        for(x=0;x<7500;x++)
        {
         del_10ms();
         if(RFID==0)
          break;   
         del_10ms(); 
         Color = ADC_PROCESS(0x00);
         Sound = ADC_PROCESS(0x01);
         if(Color<0x70 || Sound <=0x800)
             break;
        }   
        pir1=0;
        PORTC=0x50;
        for(x=0;x<25;x++)
        {
         if(pir1)
         { PORTB=0x20;  
           del_100ms();
           PORTB=0x00;
           del_100ms(); 
         }
         else
         {
           if(PIR)
           {pir1=1;}       
          del_100ms(); 
           if(PIR)
           {pir1=1;} 
          del_100ms(); 
         }
        } 
        pir1=0;
       PORTC=0x22;
        for(x=0;x<7500;x++)
        {
         del_10ms();
         if(RFID==0)
          break;  
         del_10ms(); 
         Color = ADC_PROCESS(0x00);
         Sound = ADC_PROCESS(0x01);
         if(Color<0x70 || Sound <=0x800)
             break;
        }   
        PORTC=0x82;
         for(x=0;x<25;x++)
        {
         if(pir1)
         { PORTB=0x20;  
           del_100ms();
           PORTB=0x00;
           del_100ms(); 
         }
         else
         {
           if(PIR)
           {pir1=1;}       
          del_100ms(); 
           if(PIR)
           {pir1=1;} 
          del_100ms(); 
         }
        } 
        pir1=0;
    
    }   
        
    
    
} // main


