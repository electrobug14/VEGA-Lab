#include "pcf85263a.h"

static uint8_t dec2bcd(uint8_t val) { return ((val / 10 * 16) + (val % 10)); }
static uint8_t bcd2dec(uint8_t val) { return ((val / 16 * 10) + (val % 16)); }

int PCF85263A_WriteReg(uint8_t reg, uint8_t value) {
    uint8_t buf[2] = { reg, value };
    return I2C_Write(PCF85263A_I2C_ADDR, buf, 2);
}

int PCF85263A_ReadRegs(uint8_t start_reg, uint8_t *data, uint8_t len) {
    return I2C_Read(PCF85263A_I2C_ADDR, start_reg, data, len);
}

int PCF85263A_SetTime(const RTC_Time *time) {
    uint8_t data[8];
    data[0] = REG_SECONDS;
    data[1] = dec2bcd(time->seconds);
    data[2] = dec2bcd(time->minutes);
    data[3] = dec2bcd(time->hours);
    data[4] = dec2bcd(time->day);
    data[5] = dec2bcd(time->weekday);
    data[6] = dec2bcd(time->month);
    data[7] = dec2bcd(time->year % 100);
    return I2C_Write(PCF85263A_I2C_ADDR, data, 8);
}

int PCF85263A_GetTime(RTC_Time *time) {
    uint8_t buf[7];
    if (PCF85263A_ReadRegs(REG_SECONDS, buf, 7) != 0) return -1;
    time->seconds = bcd2dec(buf[0] & 0x7F);
    time->minutes = bcd2dec(buf[1] & 0x7F);
    time->hours   = bcd2dec(buf[2] & 0x3F);
    time->day     = bcd2dec(buf[3] & 0x3F);
    time->weekday = bcd2dec(buf[4] & 0x07);
    time->month   = bcd2dec(buf[5] & 0x1F);
    time->year    = bcd2dec(buf[6]) + 2000;
    return 0;
}
