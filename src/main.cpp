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
    // TEMPERATURE
const int NUM_READINGS = 10;
float temp[NUM_READINGS];       // Initialize Temperature Array
unsigned long lastTempTime = 0; // Time of Last Temperature Reading

    //OLED DISPLAY
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
    Serial.begin(115200);   // Initialize Serial Monitor
    Wire.begin();           // Initialize I2C
    // OLED DISPLAY
    display.begin(SSD1306_SWITCHCAPVCC);    // Initialize OLED
    display.clearDisplay();                 // Clear Display
    display.setTextSize(1);                 // Set Text Size
    display.setTextColor(SSD1306_WHITE);    // Set Text Color
    display.setCursor(0, 0);                // Set Cursor Position
    display.display();                      // Update Display

}

void loop() {
// TEMPERATURE
if (millis() - lastTempTime >= 2000)    // Read Temperature Every 2 Seconds
    {
    lastTempTime = millis();
    // Store Last 10 Temperature Readings
    for (int t = 0; t < NUM_READINGS; t++)
    {
        temp[t] = bmp.readTemperature();
    }
    // Get Average of Last 10 Temperature Readings
    float averageTemp = getAverage();
    // Display Average Temperature on OLED Display
    display.clearDisplay();                 // Clear Display
    display.setCursor(0, 0);                // Set Cursor Position
    display.print("Average Temp: ");        // Display Text
    display.print(averageTemp);             // Display Average Temperature
    display.print(" C");                    // Display Text
    // display.println(Room State);)
    display.display();                      // Update Display
    }
}

















// TESTS
 // Check for BMP
    //if(!bmp.begin(0x76))
    //{ 
    //Serial.println("BMP280 Not Found"); 
    //while(true); 
    //}
    //Serial.println("BMP280 Found"); 