#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"

#define BUTTON_PIN 16 // Pin 21 (GPIO 16)

int pressDuration = 0;
int unpressedDuration = 0;
bool newLinePrinted = false;

int BUTTON_BOUNDARY = 250;
int INTER_SIGNAL_GAP = 400;

char code[4] = {' ', ' ', ' ', ' '};
int codeIndexTracker = 0;

void decoder();
void checkButton();
void checkGap();

int main(){
    stdio_init_all();
    seven_segment_init();
    sleep_ms(1000);
    seven_segment_off();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);

    printf("\n");

    while (true)
    {

        while (!gpio_get(BUTTON_PIN))
        {
            unpressedDuration += 50;
            // printf("Unpressed duration: %d \n", unpressedDuration);
            sleep_ms(50);
            checkGap();
        }

        while (gpio_get(BUTTON_PIN))
        {
            seven_segment_show(0);
            pressDuration += 50;
            unpressedDuration = 0;
            // printf("Pressed duration: %d \n", pressDuration);
            sleep_ms(50);
        }
        checkButton();
    }
}

void decoder()
{
    //Initialises two constant char arrays in to use as a key for decoding the inputs from the button
    const char *morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    const char *alphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    //New char array initialised and original input array is looped and added into this new variable
    //In order to compare it to the key above
    char input[5];

    for (int i = 0; i < codeIndexTracker; i++)
    {
        input[i] = code[i];
    }
    //A null character added at the end of the array in order to signal the end of the string
    input[codeIndexTracker] = '\0';

    //for loop to iterate through the morse array and compare the string with the input array
    //When a match is found the letter is printed from the alphabet array and it is displayed on the seven segment display
    for (int i = 0; i <= 26; i++)
    {
        if (strcmp(input, morse[i]) == 0)
        {
            printf("%s", alphabet[i]);
            seven_segment_show(i + 1);
            memset(code, ' ', 4);
            codeIndexTracker = 0;
            break;
        }
    }

    //If more than 4 inputs are created error message displated and 8 displayed in the seven segement display
    if (codeIndexTracker > 4) {
        printf("%s", "Not part of the alphabet (Too many signals!)");
        seven_segment_show(27);
    }
}

void checkButton()
{

    //Recognises dot input (Below  250ms and not 0ms) and adds a '.' character in the code array
    if (pressDuration < BUTTON_BOUNDARY && pressDuration != 0) {
        code[codeIndexTracker] = '.';
        codeIndexTracker++;
        newLinePrinted = true;
    }
    //Recognises that the button has been pressed for longer than 700ms, shows error message and display 8 on seven segement display
    if (pressDuration > 700) {
        printf("%s", "Pressed button for too long (Over 700ms!)");
        seven_segment_show(27);
    }
    //Recognises dash input (Above  250ms) and adds a '-' character in the code array
    else if (pressDuration > BUTTON_BOUNDARY) {
        code[codeIndexTracker] = '-';
        codeIndexTracker++;
        newLinePrinted = true;
    }


    //Prints inputs and codeIndexTracker (Used for testing purposes)
    /*for (int i = 0; i < codeIndexTracker; i++)
    {
        printf("%c", code[i]);
    }
    printf("%d", codeIndexTracker); */


    //Resets variable that records the amount of time that the button has been pressed
    pressDuration = 0; 
}

//Procedure to only print a new line when the button has not been pressed longer than 400ms and a previous output has been printed
//Also calls decoder procedure and resets the code array and codeIndexTracker
void checkGap()
{
    if (unpressedDuration > INTER_SIGNAL_GAP && newLinePrinted)
    {
        printf("\n");
        decoder();
        memset(code, ' ', 4);
        codeIndexTracker = 0;

        unpressedDuration = 0;
        newLinePrinted = false;
    }
}
