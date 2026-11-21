// every library we need
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// GLOBAL VARIABLES --------------------------------------------------------------------------------------------------------------

// define the pins for the RFID reader
#define RFID_SS 5
#define RFID_RST 17

// define LED pins
#define LED_RED 
#define LED_GREEN 
#define LED_BLUE 

// The time variable is used to store the time when the last RFID card was read
unsigned long indicatorStart = 0; // the time the program started
unsigned long indicatorTime = 0; // how long i want it to wait/ stay at that state
bool indicatorOn = false; // states if the program is running

// helps the program remember the last card that was read, so it doesn't keep reading the same card over and over again and changing states (occupied/free)
String lastUID = ""; // the last UID that was read
unsigned long lastScanTime = 0; // the time when the last UID was read  

// the authorized UIDS, that will have permission to the room at that time
String authorizedUIDS[] = {"", "", ""}; // the authorized UIDs, that will have permission to the room at that time ------- gotta complete
int numAuthorized = 0; //number of autorized devices ------- gotta complete

bool roomOccupied = false; // the state of the room if it is occupied or not

// creating the object from the library to act as the reader
MFRC522 rfid(RFID_SS, RFID_RST); // remember rfid is the object name we're calling back

// FUNCTIONS -----------------------------------------------------------------------------------------------------------------------------
String getUID() {
  String uid = ""; // create a string to store the UID
  for (byte i = 0; i < rfid.uid.size; i++) { // loop through the UID bytes
    if(rfid.uid.uidByte[i] < 0x10) {

    }
}



bool isAuthorized(String uid) {
  for (int i = 0; i < numAuthorized)

}

void startIndicatorTimer(unsigned long duration) {
  indicatorStart = millis(); // store the current time/ calling back the global variable with the proper functions
  indicatorTime = duration; // store the duration
  indicatorOn = true; // set the indicator to on
}






void setup() {
  Serial.begin(115200); // start the serial communication
  SPI.begin(); // start the SPI bus
  rfid.PCD_Init(); // initialize the RFID reader

  Serial.println("tap a card...");

}

void loop() {
  // put your main code here, to run repeatedly:
}
