#ifndef _AT25512_H
#define _AT25512_H

#define HIGH 1
#define LOW 0

/* opcodes */
#define READ_EEPROM 0x03     // Read Array
#define WRITE_EEPROM 0x02    // Byte/Page Program

#define READ_STATUS_1 0x05   // Read Status Register - Byte 1
#define READ_STATUS_2 0x35   // Read Status Register - Byte 2
#define WRITE_ENABLE 0x06    // Write Enable
#define DUMMY_DATA 0x00
#define EEPROM_BUSY 0x01
#define PAGE_SIZE 128



#define READ_DEV_ID 0x9F     // Read Manufacturer and Device ID



void at25512Begin(unsigned char spi_no);
void at25512Read(char *readBuff, int length, char opcode);
void at25512Write(char *writeBuf, int length);
void at25512ReadEeprom(char *readBuf, int length, unsigned int eepromAddress);
void at25512WriteEeprom(char *writeBuf, int length, unsigned int eepromAddress);
void at25512BusyWait(void);
void at25512_main();
#endif /* _ADS25SF161_H */
