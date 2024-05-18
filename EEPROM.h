// Author: Lieu Thanh Truong
//Read and write EEPROM in pic18f14k22

void EEPROM_write(unsigned char address, unsigned char data1);
unsigned char EEPROM_read(unsigned char address);


void EEPROM_write(unsigned char address, unsigned char data1)
{
    EEADR = address;
    EEDATA = data1;
    GIE_bit = 0;
    WREN_bit = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR_bit = 1;
    while(WR_bit);
    WREN_bit = 0;
    GIE_bit = 1;
}

unsigned char EEPROM_read(unsigned char address)
{
    EEADR = address;
    RD_bit = 1;
    while(RD_bit);
    return EEDATA;
}
