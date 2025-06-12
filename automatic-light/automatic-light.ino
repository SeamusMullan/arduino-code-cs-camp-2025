// This file uses a light sensor to automatically turn on an LED when it gets dark.
// It uses the Arduino's built-in analog pin to read the light level.

const int lightSensorPin = A0; // Analog pin for light sensor
const int ledPin = 8;          // Digital pin for LED

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int lightLevel = analogRead(lightSensorPin);
    Serial.println(lightLevel);
    if (lightLevel < 512) // if its dark enough
    {
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }
    delay(100);
}