//Author: Lieu Thanh Truong
//LCD 16x2 communicate with Pic16f887

#define LCD_RW     RD1_bit
#define LCD_RS     RD0_bit
#define LCD_EN     RD2_bit
#define LCD_D4     RD4_bit
#define LCD_D5     RD5_bit
#define LCD_D6     RD6_bit
#define LCD_D7     RD7_bit

#define LCD_Clear 0x01
#define CMD 0
#define DAT 1

void LCD_Send(bool CmdData , unsigned char data1);
void LCD_SetCursor(unsigned char row, unsigned char col);
void LCD_Init();
void LCD_String(char *str);

void LCD_Send(bool CmdData , unsigned char data1)
{
    //4 bit cao
    LCD_D4 = (data1 >> 4) & 1;
    LCD_D5 = (data1 >> 5) & 1;
    LCD_D6 = (data1 >> 6) & 1;
    LCD_D7 = (data1 >> 7) & 1;
    LCD_RS = CmdData;
    LCD_EN = 1;
    Delay_us(1);
    LCD_EN = 0;

    // 4 bit thap
    LCD_D4 = (data1 >> 0) & 1;
    LCD_D5 = (data1 >> 1) & 1;
    LCD_D6 = (data1 >> 2) & 1;
    LCD_D7 = (data1 >> 3) & 1;
    LCD_EN = 1;
    Delay_us(1);
    LCD_EN = 0;

    Delay_ms(2);
}


void LCD_Init()
{
    // G?i l?nh kh?i t?o
    LCD_Send(CMD,0x02); // Giao tiep 4 day
    LCD_Send(CMD,0x28); // 4-bit mode, 2 lines, 5x7 font
    LCD_Send(CMD,0x0C); // Display ON, cursor OFF
    LCD_Send(CMD,0x06); // Auto increment cursor
    LCD_Send(CMD,0x01); // Clear display
    Delay_ms(2);   // Delay 2ms
}

// Hàm g?i chu?i ký t? t?i màn hình LCD
void LCD_String(char *str)
{
    while(*str)
    {
        LCD_Send(DAT,*str++);
    }
}

void LCD_SetCursor(unsigned char row, unsigned char col)
{
    unsigned char pos;
    if(row == 1)
        pos = 0x80 + col - 1; // Ð?a ch? b?t d?u c?a dòng 1
    else if(row == 2)
        pos = 0xC0 + col - 1; // Ð?a ch? b?t d?u c?a dòng 2
    LCD_Send(CMD,pos);
}