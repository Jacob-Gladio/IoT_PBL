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
float temp[NUM_READINGS];                 // Initialize Temperature Array
const int NUM_READINGS = 10;
float averageTemp;              // Variable Containing Average Temperature from temp[10]

// Functions
float getAverage() {            //Temperature Average
    long sum = 0;
    for (int t = 0; t < NUM_READINGS; t++) 
    {
        sum = sum + t;
    }
    return (float)sum / NUM_READINGS;
}

void setup() {
// Initialize Components
    Serial.begin(115200);                   // Initialize Serial Monitor
    Wire.begin();                           // Initialize I2C
    Serial.println("I2C Started");

    if(!bmp.begin(0x76))                    // Check for BMP
    { 
    Serial.println("BME280 Not Found"); 
    while(true); 
    }
    Serial.println("BME280 Found"); 

}

void loop() {
// TEMPERATURE
    for (int t = 0; t < 10; t++)
    {
        temp[t] = bmp.readTemperature();    // Store Last 10 Temperature Readings
    }

}