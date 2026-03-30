/*****************************************************************************

 Project Name		: Aries v3 Board - UART LED GPIO Example
 Project Code		: 
 Created		    : 27-Aug-2025
 Filename		    : uart_led_gpio.c
 Purpose		    : Sample program to control RGB LED using UART input
 Description		: Sample program to control the on-board RGB LED
                      using UART input. The program listens for user input
                      via UART and controls the LED colors accordingly.
                      The user can input numbers from 1 to 8 to set different
                      color combinations or turn off the LED.
 Author(s)		    : Nishit Bayen
 Email			    : nishitbayen2021@gmail.com
    
 See LICENSE for license details.
******************************************************************************/


/**
 @file rgb_led_control.c
 @brief Controls the on-board RGB LED using UART input.
 */

#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include "uart.h"
#include "string.h"

// Define the GPIO pins for the on-board RGB LED
#define RED1_PIN    22
#define RED2_PIN   25
#define GREEN1_PIN  23
#define GREEN2_PIN 26
#define BLUE1_PIN   24
#define BLUE2_PIN  27

// Forward declaration of the receive_string function
void receive_string(char *str);

/**
 * @brief Sets the state of a specific GPIO pin (ON/OFF)
 * and automatically sets its direction as output.
 * @param gpioPin The pin number.
 * @param state The state to set (1 for ON, 0 for OFF).
 */
void setLedState(unsigned char gpioPin, unsigned char state) {
    GPIO_write_pin(gpioPin, state);
}

/**
 * @brief Receives a string from the UART and null-terminates it.
 * @param str Pointer to the buffer to store the received string.
 */
void receive_string(char *str) {
    char error;
    char data;
    int i = 0;
    while(1) {
        data = uart_getchar(UART_0, &error);
        if (data == '\r' || data == '\n' || i >= 99) {
            break;
        }
        str[i] = data;
        i++;
    }
    str[i] = '\0';
}

/**
 * @fn main
 * @brief Main function to control the RGB LED based on UART input.
 */
int main() {
    char str_input[100];
    int selection;

    printf("\n--- Aries Board RGB LED Control ---\n");
    printf("Enter a number from 1 to 8 to control the LED.\n");
    printf("1: Red, 2: Green, 3: Blue, 4: Red+Green, 5: Red+Blue, 6: Green+Blue, 7: All ON, 8: All OFF\n");

    // The GPIO_write_pin function implicitly sets the pin direction to output,
    // so there's no need for a separate setWireOutput function.

    while(1) {
        printf("\nEnter selection (1-8): ");
        receive_string(str_input);
        selection = atoi(str_input);

        // Turn off all LEDs before applying the new state
        setLedState(RED1_PIN, 1);
        setLedState(GREEN1_PIN, 1);
        setLedState(BLUE1_PIN, 1);

        setLedState(RED2_PIN, 1);
        setLedState(GREEN2_PIN, 1);
        setLedState(BLUE2_PIN, 1);

        // Control LEDs based on the user's input
        switch(selection) {
            case 1: // Red
                setLedState(RED1_PIN, 0);
                setLedState(RED2_PIN, 0);
                break;
            case 2: // Green
                setLedState(GREEN1_PIN, 0);
                setLedState(GREEN2_PIN, 0);
                break;
            case 3: // Blue
                setLedState(BLUE1_PIN, 0);
                setLedState(BLUE2_PIN, 0);
                break;
            case 4: // Red + Green
                setLedState(RED1_PIN, 0);
                setLedState(RED2_PIN, 0);
                setLedState(GREEN1_PIN, 0);
                setLedState(GREEN2_PIN, 0);
                break;
            case 5: // Red + Blue
                setLedState(RED1_PIN, 0);
                setLedState(RED2_PIN, 0);
                setLedState(BLUE1_PIN, 0);
                setLedState(BLUE2_PIN, 0);
                break;
            case 6: // Green + Blue
                setLedState(GREEN1_PIN, 0);
                setLedState(GREEN2_PIN, 0);
                setLedState(BLUE1_PIN, 0);
                setLedState(BLUE2_PIN, 0);
                break;
            case 7: // All ON
                setLedState(RED1_PIN, 0);
                setLedState(RED2_PIN, 0);
                setLedState(GREEN1_PIN, 0);
                setLedState(GREEN2_PIN, 0);
                setLedState(BLUE1_PIN, 0);
                setLedState(BLUE2_PIN, 0);
                break;
            case 8: // All OFF (handled by the initial state reset)
                break;
            default:
                printf("Invalid input. Please enter a number from 1 to 8.\n");
                break;
        }
    }
    return 0;
}