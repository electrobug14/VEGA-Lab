#ifndef PCF85263A_H
#define PCF85263A_H

#include <stdint.h>

#define PCF85263A_I2C_ADDR  0x51

#define REG_SECONDS   0x01
#define REG_MINUTES   0x02
#define REG_HOURS     0x03
#define REG_DAYS      0x04
#define REG_WEEKDAYS  0x05
#define REG_MONTHS    0x06
#define REG_YEARS     0x07

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t weekday;
    uint8_t month;
    uint16_t year;
} RTC_Time;

int PCF85263A_WriteReg(uint8_t reg, uint8_t value);
int PCF85263A_ReadRegs(uint8_t start_reg, uint8_t *data, uint8_t len);
int PCF85263A_SetTime(const RTC_Time *time);
int PCF85263A_GetTime(RTC_Time *time);

int I2C_Write(uint8_t dev_addr, uint8_t *data, uint8_t len);
int I2C_Read(uint8_t dev_addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif
