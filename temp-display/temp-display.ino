// Temperature Display with LCD
// This project reads a temperature sensor and displays the temperature on an LCD screen.
// It shows both Celsius and Fahrenheit readings with real-time updates.
//
// Wiring:
// Temperature Sensor:
// - VCC to 5V
// - GND to GND  
// - Signal to A0
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

const int tempPin = A0; // Temperature sensor pin

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Print initial message
  lcd.print("Temp Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  
  Serial.begin(9600);
  Serial.println("Temperature Display Ready");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read temperature sensor
  int sensorValue = analogRead(tempPin);
  
  // Convert analog reading to voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Convert voltage to temperature for TMP36
  // TMP36: 10mV/°C with 500mV offset
  float temperatureC = (voltage - 0.5) * 100.0;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  
  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC, 1);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("      ");
  lcd.print(temperatureF, 1);
  lcd.print("F");
  
  // Clear any extra characters
  for(int i = lcd.getCursor(); i < 16; i++) {
    lcd.print(" ");
  }
  
  // Also print to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print("°C / ");
  Serial.print(temperatureF, 1);
  Serial.println("°F");
  
  delay(1000); // Update every second
}
