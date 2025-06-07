// This program shows a random long message on an LCD screen using Arduino.
// The message is too long to fit, so it scrolls across the screen!
//
// How it works:
// 1. When the Arduino turns on, it picks one of five long messages at random.
// 2. The message is shown on the LCD, but since it's too long, it scrolls from left to right.
// 3. The LCD is 16 characters wide, so only part of the message is visible at a time.
// 4. The message scrolls smoothly so you can read the whole thing!


#include <Wire.h> // Lets Arduino talk to devices using I2C (like the LCD)
#include <hd44780.h> // Main LCD library
#include <hd44780ioClass/hd44780_I2Cexp.h> // Special class for I2C LCDs

// This creates an LCD object that knows how to talk to your screen using I2C.
hd44780_I2Cexp lcd; // auto-detects I2C address



#include <Arduino.h> // Standard Arduino stuff
#include <stdlib.h>  // For random numbers

// Here are 5 long messages. Each time the Arduino starts, one will be picked randomly.
// These are all longer than 16 characters, so they need to scroll!
const char* messages[5] = {
  "This is a long message that will scroll across the LCD screen!",
  "Arduino projects are fun and educational for everyone involved.",
  "The quick brown fox jumps over the lazy dog multiple times.",
  "Exploring I2C LCD displays with scrolling text is pretty cool!",
  "Here is another long string to demonstrate scrolling on LCD."
};

// This function scrolls a message across the LCD screen.
//
// msg: the message to show (must be a string)
// row: which row of the LCD to use (0 = top row, 1 = bottom row)
// delayMs: how long to wait before moving the text (in milliseconds)
//
// If the message is short, it just shows it. If it's long, it scrolls it!
void scrollText(const char* msg, int row = 0, int delayMs = 300) {
  int len = strlen(msg); // How long is the message?
  int width = 16; // LCD width (16 characters)
  if (len <= width) {
    // If the message fits, just print it
    lcd.setCursor(0, row);
    lcd.print(msg);
    return;
  }
  // If the message is too long, scroll it!
  // This loop moves the message from left to right, one letter at a time
  for (int i = 0; i <= len - width; i++) {
    lcd.setCursor(0, row); // Start at the beginning of the row
    for (int j = 0; j < width; j++) {
      lcd.print(msg[i + j]); // Print part of the message
    }
    delay(delayMs); // Wait a bit so you can read it
  }
  // After the message, scroll in some blank spaces so it looks smooth
  for (int i = 0; i < width; i++) {
    lcd.setCursor(0, row);
    for (int j = 0; j < width; j++) {
      int idx = len - width + 1 + i + j;
      if (idx < len)
        lcd.print(msg[idx]); // Still part of the message
      else
        lcd.print(" "); // Now just blank spaces
    }
    delay(delayMs);
  }
}

// This function runs once when the Arduino turns on.
// It sets up the LCD, picks a random message, and scrolls it!
void setup() {
  lcd.begin(16, 2); // Tell the LCD how big it is (16 columns, 2 rows)
  lcd.backlight();  // Turn on the LCD backlight so you can see it
  randomSeed(analogRead(A0)); // Make sure the random number is different every time
  int idx = random(0, 5); // Pick a random number from 0 to 4
  lcd.clear(); // Clear anything that was on the screen
  scrollText(messages[idx], 0, 150); // Show and scroll the message on the top row
}

// This function runs over and over forever.
// We'll use it to keep scrolling the message forever!
int currentMsgIdx = -1; // Store which message is being shown

void loop() {
  // If this is the first time, pick a random message
  if (currentMsgIdx == -1) {
    currentMsgIdx = random(0, 5);
  }
  // Keep scrolling the same message forever
  scrollText(messages[currentMsgIdx], 0, 150);
}