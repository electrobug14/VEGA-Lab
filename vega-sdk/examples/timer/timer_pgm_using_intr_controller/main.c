/***************************************************
* Module name: main.c
*
* Copyright 2020 Company CDAC(T)
* All Rights Reserved.
*
*  The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
*
* Module Description:
* SPI test pgm
*
***************************************************/

/*  Include section
*
*
***************************************************/

#include "stdlib.h"
#include "config.h"
#include "timer.h"
#include "interrupt.h"




/** @fn timer0_intr_handler
  @brief  timer 0 intr handler.
  @details The function will execute the steps as described in routine
  @warning 
  @param[in] unsigned char, unsigned int
  @param[Out] No output parameter.
*/
void timer0_intr_handler(void) {
	UI wEOI;
	wEOI = Timer(0).EOI;			// Reads the Timer 0 EOI register to clear the intr.
	printf("\n\r TIMER 0 intr occurred");
	// User can add their code for TImer 0 interrupt.
	return;   
}


/** @fn timer1_intr_handler
  @brief  timer 1 intr handler.
  @details The function will execute the steps as described in routine
  @warning 
  @param[in] unsigned char, unsigned int
  @param[Out] No output parameter.
*/
void timer1_intr_handler(void) {
	UI wEOI;
	wEOI = Timer(1).EOI;			// Reads the Timer 1 EOI register to clear the intr.
	printf("\n\r TIMER 1 intr occurred");
	// User can add their code for TImer 1 interrupt.
	return;   
}


/** @fn timer2_intr_handler
  @brief  timer 2 intr handler.
  @details The function will execute the steps as described in routine
  @warning 
  @param[in] unsigned char, unsigned int
  @param[Out] No output parameter.
*/
void timer2_intr_handler(void) {
	UI wEOI;
	wEOI = Timer(2).EOI;			// Reads the Timer 2 EOI register to clear the intr.
	printf("\n\r TIMER 2 intr occurred");
	// User can add their code for TImer 2 interrupt.
	return;   
}




/** @fn main
 * @brief Generate a delay in polling mode.
 * @details In this program the timers0,timers1 & timers2 are loaded with values and enabled.
 *          When a timer overflows, interrupt from that particular timer occurs and the program goes to the isr of that timer 
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{

	printf("\n\r TIMER TEST CASE - INTR Method");

	timer_register_isr(TIMER_0, timer0_intr_handler);  // Register timer0 Intr.
	timer_register_isr(TIMER_1, timer1_intr_handler);  // Register timer1 Intr.
	timer_register_isr(TIMER_2, timer2_intr_handler);  // Register timer2 Intr.

	timer_run_in_intr_mode(TIMER_0,0x2000000);	    // Load timer0 (with Number of clocks = 0x2000000) and enable interrupt.
	timer_run_in_intr_mode(TIMER_1,0x5000000);	    // Load timer1 (with Number of clocks = 0x5000000) and enable interrupt.
	timer_run_in_intr_mode(TIMER_2,0xA000000);      // Load timer2 (with Number of clocks = 0xA000000) and enable interrupt.

	while(1);
 }




