/**
 * The given template is a guideline for your coursework only.
 * You are free to edit/create any functions and variables.
 * You can add extra C files if required.
*/


#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"

#define BUTTON_PIN			16	// Pin 21 (GPIO 16)

// declare global variables e.g., the time when the button is pressed 
int pressDuration = 0;

int BUTTON_BOUNDARY = 250;
int INTER_SIGNAL_GAP = 400;

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character

int main() {
	stdio_init_all();

	// Initialise the seven segment display.
	seven_segment_init();

	sleep_ms(1000);
	// Turn the seven segment display off when the program starts.
	seven_segment_off();

	// Initialize the button's GPIO pin.
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).

	while (true) {

		while (gpio_get(BUTTON_PIN)){			
            // record how long the button is pressed
			pressDuration += 50;
			sleep_ms(50);
		}

        // check if the button press is a dot or a dash
		checkButton();

		pressDuration = 0;
	}
}

void decoder(){
    // a function to be implemented
}

void checkButton(){
    if (pressDuration < BUTTON_BOUNDARY && pressDuration != 0) {
		printf(".");
	} else if (pressDuration > BUTTON_BOUNDARY && pressDuration != 0) {
		printf("-");
	}
}

