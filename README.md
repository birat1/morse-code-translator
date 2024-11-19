## Morse Code Decoder
A Morse code decoder implemented on a Raspberry Pi Pico using the Pico C SDK.

It reads button presses to interpret Morse code and displays the resulting letter on a seven-segment display.

## Features
- Recognises dot (.) and dash (-) inputs based on the duration of the button presses.
- Displays error messages for unrecognised/invalid inputs.
- Decodes morse code and resets after a specified duration.

## Hardware Requirements
- Raspberry Pi Pico
- Button connected to GPIO pin 16
- Seven-segment display

## Usage
1. Connect Raspberry Pi Pico
2. Flash the compiled binary to the Pico
3. Press the button to input Morse code:
   - Short press (< 250ms) for dot (.)
   - Long press (> 250ms) for dash (-)
   - Very long press (> 700ms) will result in an error.
