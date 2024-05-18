#include <stdio.h>
#include <stdbool.h>
#include "LCD.h"
#include "EEPROM.h"
#include "RC522.h"

#define DELAYTIME 500
#define OUTPUT 0
#define INPUT 1


char i;
char UID[6];
unsigned char TagType;
char size;

void SPI_init()
{
     SSPCON = 0x21;     //SSPEN = 1    CKP = 0
     SSPSTAT = 0x00;    //CKE = 0
}

void Init()
{
    TRISD = 0x00;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    Delay_ms(20);
    EEPGD_bit = 0;
}

void main() 
{
    Init();
    LCD_Init();
    LCD_Send(CMD,LCD_Clear);
    LCD_String("LCD initialized");
    delay_ms(DELAYTIME);
    LCD_Send(CMD,LCD_Clear);
    LCD_SetCursor(1,1);
    
    SPI_init();
    MFRC522_Init ();
    
    LCD_String("RC522 initialized");
    delay_ms(1000);
    
    LCD_Send(CMD,LCD_Clear);

    while(1)
    {
       /*Test EEPROM
       if(EEPROM_read(0x00)==-1)
       {
          EEPROM_write(0x00,0);
       }
       else
       {
          i = EEPROM_read(0x00);
          i++;
          i=(i==10)?0:i;
          EEPROM_write(0x00,i);
          LCD_Send(DAT,i+'0');
          delay_ms(DELAYTIME+DELAYTIME);
          LCD_Send(CMD,LCD_Clear);
          LCD_SetCursor(1,1);
       }
       */

       /*test spi
       for(i=0;i<10;i++)
       {
          SPI_ReadWrite(i);
          delay_ms(DELAYTIME);
       }
       */
       
       if(MFRC522_isCard (&TagType)) //Check any card
       {
           if(MFRC522_ReadCardSerial (&UID))
         {
            LCD_Send(DAT,"UID: ");
            LCD_SetCursor(2,1);
            for(i = 0; i < 5; i++)
            {
                  LCD_Send(DAT,UID[i]+'0');
            }
         }
         //Ngu dong
         MFRC522_Halt();
       }
    }
}