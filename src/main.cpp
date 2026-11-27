// Libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>    // Temp Sensor Library
#include <Adafruit_BMP280.h>    // Temp Sensor Library
#include <Adafruit_GFX.h>       // OLED Library
#include <Adafruit_SSD1306.h>   // OLED Library
#include <Wire.h>               // I2C Library
#include <SPI.h>                // SPI Library

// Pins
Adafruit_BMP280 bmp;            // Temperature Pins

// Global Variables
    // TEMPERATURE
const int NUM_READINGS = 10;
float temp[NUM_READINGS];       // Initialize Temperature Array

    // OLED DISPLAY
unsigned long lastOLEDTime = 0; // Time of Last OLED Update
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MOSI 23                 // Global MOSI
#define CLK 18                  // Global Clock
#define DC 16
#define OLED_CS 15              // Chip Select of OLED
#define RST 4
Adafruit_SSD1306 display(       // OLED Object
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	MOSI,
	CLK,
	DC,
	RST,
	OLED_CS
);

    // POTENTIOMETER
#define POT_PIN 34
    // HELP BUTTON
volatile const int HELP_BUTTON = 25;

// Functions
    // TEMPERATURE
float getAverage() {
    // Store Last 10 Temperature Readings
    for (int t = 0; t < NUM_READINGS; t++)
    {
        temp[t] = bmp.readTemperature();
        delay(50);
    }
    // Get Average Temperautre of Last 10 Temperature Readings
    long sum = 0;
    for (int t = 0; t < NUM_READINGS; t++) 
    {
        sum = sum + temp[t];
    }
    return (float)sum / NUM_READINGS;
}

    // POTENTIOMETER THRESHOLD
float getTempThresh()
{
    int potVal = analogRead(POT_PIN);               // Reads Potentiometer Resistance
    int tempThresh = map(potVal, 0, 4095, 20, 50);  // Fan Will Only Turn On if Temperature > 20
    return tempThresh;
}

    // FAN CONTROL
void fanSpeed () {
    
}

    // HELP BUTTON
ISR_RAM



void setup() {
// Initialize Components
    Serial.begin(115200);   // Initialize Serial Monitor

    // TEMPERATURE
    Wire.begin();           // Initialize I2C
    bmp.begin(0x76);        // Initialize BMP280 Sensor

    // OLED DISPLAY
    display.begin(SSD1306_SWITCHCAPVCC);    // Initialize OLED
    display.clearDisplay();                 // Clear Display
    display.setTextSize(1);                 // Set Text Size
    display.setTextColor(SSD1306_WHITE);    // Set Text Color
    display.setCursor(0, 0);                // Set Cursor Position
    display.display();                      // Update Display

    // POTENTIOMETER ADC
    analogReadResolution(12);               // Set Analog 12 Bit Resolution
    analogSetAttenuation(ADC_11db);         // Measure 0-3.3V Range
    pinMode(POT_PIN, INPUT);

}

void loop() {
// OLED DISPLAY
if (millis() - lastOLEDTime >= 2000)    // Update OLED Display Every 2 Seconds
    {
    lastOLEDTime = millis();

    // TEMPERATURE
    float averageTemp = getAverage();       // Get Average of Last 10 Temperature Readings

    // Display Average Temperature & Room State on OLED Display
    display.clearDisplay();                 // Clear Display
    display.setCursor(0, 0);                // Set Cursor Position
    display.print("Temp: ");                // Display Text
    display.print(averageTemp);             // Display Average Temperature
    display.println(" C");                  // Display Text
    // display.println(Room State);
    display.display();                      // Update Display
    }

// FAN CONTROL

}

















// TESTS
 // Check for BMP Setup
    //if(!bmp.begin(0x76))
    //{ 
    //Serial.println("BMP280 Not Found"); 
    //while(true); 
    //}
    //Serial.println("BMP280 Found");
 // Check for temperature readings Loop
    //Serial.println(bmp.readTemperature());