// Push Button Counter
// This project counts button presses and displays the count on an LCD.
// It includes debouncing to prevent false counts from mechanical switch bounce.
//
// Wiring:
// Push Button:
// - One side to pin 2
// - Other side to GND
// - 10kΩ pull-up resistor from pin 2 to 5V
//
// LCD (16x2 with parallel interface):
// - VSS to GND
// - VDD to 5V
// - V0 to potentiometer (contrast adjustment)
// - RS to pin 8
// - Enable to pin 9
// - D4 to pin 4
// - D5 to pin 5
// - D6 to pin 6
// - D7 to pin 7

#include <LiquidCrystal.h>

// Initialize the LCD library with interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int buttonPin = 2;     // Push button pin
const int debounceDelay = 50; // Debounce time in milliseconds

// Variables for button state and counting
int buttonState = 0;
int lastButtonState = 0;
int buttonCount = 0;
unsigned long lastDebounceTime = 0;

void setup() {
  // Initialize button pin with internal pull-up
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Set up the LCD
  lcd.begin(16, 2);
  lcd.print("Button Counter");
  lcd.setCursor(0, 1);
  lcd.print("Count: 0");
  
  Serial.begin(9600);
  Serial.println("Push Button Counter Ready");
  Serial.println("Count: 0");
}

void loop() {
  // Read the button state
  int reading = digitalRead(buttonPin);
  
  // Check if button state changed (due to noise or pressing)
  if (reading != lastButtonState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }
  
  // Check if enough time has passed to consider this a stable reading
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed
    if (reading != buttonState) {
      buttonState = reading;
      
      // Only count if the button is pressed (LOW due to pull-up)
      if (buttonState == LOW) {
        buttonCount++;
        
        // Update LCD display
        lcd.setCursor(0, 1);
        lcd.print("Count: ");
        lcd.print(buttonCount);
        
        // Clear any extra digits
        if (buttonCount < 10) {
          lcd.print("   ");
        } else if (buttonCount < 100) {
          lcd.print("  ");
        } else if (buttonCount < 1000) {
          lcd.print(" ");
        }
        
        // Print to serial monitor
        Serial.print("Button pressed! Count: ");
        Serial.println(buttonCount);
        
        // Optional: Reset counter at 9999 to prevent overflow display issues
        if (buttonCount >= 9999) {
          buttonCount = 0;
          lcd.setCursor(0, 1);
          lcd.print("Count: 0    ");
          Serial.println("Counter reset to 0");
        }
      }
    }
  }
  
  // Save the current reading for next iteration
  lastButtonState = reading;
}
