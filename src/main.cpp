// Libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>    // Temp Sensor Libraries
#include <Adafruit_BMP280.h>    // Temp Sensor Libraries
#include <Adafruit_GFX.h>       // OLED Library
#include <Adafruit_SSD1306.h>   // OLED Library
#include <Wire.h>               // I2C Library
#include <SPI.h>                // SPI Library

// Pins
Adafruit_BMP280 bmp;            // Temperature Pins

// Global Variables
const int NUM_READINGS = 10;
float temp[NUM_READINGS];                 // Initialize Temperature Array


// Functions
// TEMPERATURE
float getAverage() {
    long sum = 0;
    for (int t = 0; t < NUM_READINGS; t++) 
    {
        sum = sum + temp[t];
    }
    return (float)sum / NUM_READINGS;
}


void setup() {
// Initialize Components
    Serial.begin(115200);                   // Initialize Serial Monitor
    Wire.begin();                           // Initialize I2C
    // Check for BMP
    //if(!bmp.begin(0x76))
    //{ 
    //Serial.println("BMP280 Not Found"); 
    //while(true); 
    //}
    //Serial.println("BMP280 Found"); 

}

void loop() {
// TEMPERATURE
    // Store Last 10 Temperature Readings
    for (int t = 0; t < NUM_READINGS; t++)
    {
        temp[t] = bmp.readTemperature();
    }
    // Get Average of Last 10 Temperature Readings
    float averageTemp = getAverage();

// OLED
}