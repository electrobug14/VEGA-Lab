
#ifndef LED_H_
#define LED_H_

/**
 @file led.h
 @brief header file for LED functions 
 @detail 
 */

/*  Include section
*
***************************************************/


/*  Defines section
*


***************************************************/
#define OFF_LED			0
#define ON_LED			1


/*  Function declarations
*
***************************************************/
void on_LED(US pin_no);
void off_LED(US pin_no);
US read_switch(US pin_no);

#endif /* LED_H_ */
