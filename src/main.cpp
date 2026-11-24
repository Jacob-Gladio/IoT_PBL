// Libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>    // Temp Sensor Libraries
#include <Adafruit_BMP280.h>    // Temp Sensor Libraries
#include <Adafruit_GFX.h>       // OLED Library
#include <Adafruit_SSD1306.h>   // OLED Library
#include <Wire.h>               // I2C Library
#include <SPI.h>                // SPI Library

// Pins


// Global Variables
Adafruit_BMP280 bmp;            // Temp variable
float temperature;


// Initialize Temp Array
float Temp[10] = {0};


// 

void setup(){
    //Initialize Components
    Serial.begin(115200);       // Initialize Serial Monitor
    Wire.begin();               // Initialize I2C
    Serial.println("I2C Started");

    if(!bmp.begin(0x76))        // Check for BMP
    { 
    Serial.println("BME280 Not Found"); 
    while(true); 
    }
    Serial.println("BME280 Found"); 

}

void loop(){
    // Last 10 Temperature Readings
    //for (int t = 0; t < 10; t++)
    //{
        //digitalRead();
    //}

    // Temp Test
    temperature = bmp;
    Serial.print("Temperature: "); 
    Serial.print(temperature); 
    Serial.println(" C"); 
    delay(1000); 
}