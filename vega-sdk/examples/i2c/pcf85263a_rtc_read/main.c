#include "pcf85263a.h"

#include "i2c.h"
#include "i2c_api.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0
// Example: I2C3 running at 100kHz with 40MHz system clock
#define I2C_BUS I2C_3

int I2C_Write(uint8_t dev_addr, uint8_t *data, uint8_t len) {
    // Initialize bus if not already done
    i2c_init(I2C_BUS);

    // Start communication with device
    i2c_beginTransmission(dev_addr);

    // Write data buffer
    i2c_multiWrite(data, len);

    // End transmission (TRUE = send STOP condition)
    i2c_endTransmission(TRUE);

    return 0; // return 0 for success
}

int I2C_Read(uint8_t dev_addr, uint8_t reg, uint8_t *data, uint8_t len) {
    uint8_t i;

    i2c_init(I2C_BUS);

    // Send the register address to read from
    i2c_beginTransmission(dev_addr);
    i2c_write(reg);
    i2c_endTransmission(TRUE);

    // Request 'len' bytes from device
    i2c_requestFrom(dev_addr, len, TRUE);

    // Read 'len' bytes
    for (i = 0; i < len; i++) {
        data[i] = i2c_read();
    }

    return 0;
}

int main(void) {
    RTC_Time rtc_time;
   // RTC_Time set_time = {30, 9, 17, 7, 4, 11, 2025};

   /* if (PCF85263A_SetTime(&set_time) == 0)
        printf("RTC time set successfully!\n");
    else
        printf("Failed to set RTC time!\n");*/
        
    while(1){

    if (PCF85263A_GetTime(&rtc_time) == 0) {
        printf("\rRTC Time: %02d:%02d:%02d %02d/%02d/%04d",
               rtc_time.hours, rtc_time.minutes, rtc_time.seconds,
               rtc_time.day, rtc_time.month, rtc_time.year);
    } else {
        printf("Failed to read RTC time!\n");
    }
    usleep(10000000);
    }

    while (1) {}
    return 0;
}
