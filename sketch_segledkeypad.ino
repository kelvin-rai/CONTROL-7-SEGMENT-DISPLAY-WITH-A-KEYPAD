#include <Keypad.h>

// Define segment pins (A, B, C, D, E, F, G, DP)
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};  // A, B, C, D, E, F, G, DP

// Define digit select pins
const int digitPins[] = {10, 11, 12, 13};  // Digit 1, Digit 2, Digit 3, Digit 4

// Define LED pins
const int ledPins[] = {14, 15, 16, 17};  // LED 1, LED 2, LED 3, LED 4

// Binary patterns for numbers 0-9 on a 7-segment display (Common Anode)
const byte numberPatterns[] = {
  0b11111100,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000   // 9
};

// Define the keypad layout
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {19, 20, 21, 30}; // Row pinouts of the keypad
byte colPins[COLS] = {22,24 , 26, 28}; // Column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Set segment pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Set digit select pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }

  // Set LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Turn off all segments, digits, and LEDs initially
  clearDisplay();
}

void loop() {
  char key = keypad.getKey(); // Get the pressed key
  
  if (key) {
    int digit = key - '0'; // Convert char to int
    if (digit >= 1 && digit <= 4) { // Check for valid keys
      displayNumber(digit, digit - 1); // Display number
      controlLED(digit - 1); // Control corresponding LED
      delay(1000); // Keep it on for 1 second
    }
  }
}

void displayNumber(int number, int digit) {
  // Turn off all digits
  clearDisplay();
  
  // Select the current digit (set HIGH for common anode)
  digitalWrite(digitPins[digit], HIGH);

  // Display the corresponding number (set segments HIGH to turn them on)
  for (int i = 0; i < 8; i++) {
    bool segmentState = numberPatterns[number] & (1 << i);
    digitalWrite(segmentPins[i], segmentState ? HIGH : LOW);  // HIGH turns ON the segment
  }

  // Small delay for multiplexing
  delay(5);
}

// Function to control the corresponding LED for the digit
void controlLED(int index) {
  // Turn off all LEDs
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);  // LOW turns OFF the LED
  }
  // Turn on the selected LED
  digitalWrite(ledPins[index], HIGH);  // HIGH turns ON the selected LED
}

// Function to clear all digits and LEDs (turn off)
void clearDisplay() {
  // Turn off all segments (LOW = off for common anode)
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], LOW);  // LOW turns OFF the segment
  }

  // Turn off all digit select pins (LOW = off for common anode)
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);  // LOW turns OFF the digit
  }

  // Turn off all LEDs
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);  // LOW turns OFF the LED
  }
}
