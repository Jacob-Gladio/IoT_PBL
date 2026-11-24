// every library we need
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>

// GLOBAL VARIABLES --------------------------------------------------------------------------------------------------------------

// define the pins for the RFID reader
#define RFID_SS 5
#define RFID_RST 17

// define LED pins
#define LED_RED 35
#define LED_GREEN 32

//define the pin for the SD card reader
#define SDchipSelect 2
File dataFile; // create a file object to hold the data

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
  for (byte i = 0; i < rfid.uid.size; i++) { // loop through the UID bytes (normally 4 according to Lab 9)
    if(rfid.uid.uidByte[i] < 0x10) {
      uid += "0"; // add a leading zero for single-digit hex values --> 1 = 01, 2 = 02, etc
    }
    uid = uid + String(rfid.uid.uiByte[i], HEX); // Turns the byte into hex text
    if (i < rfid.uid.size - 1) { // Add a space after each byte except the last
      uid = uid + " "; 
    }
  }
  uid.toUpperCase(); // convert the string to uppercase
  return uid; // return the UID string
}

bool isAuthorized(String uid) { // receives the card text, and returns with true or false if it respects the parameters
  for (int i = 0; i < numAuthorized; i++) {
    if (uid == authorizedUIDs[i]) {
      return true; // UID is authorized 
    }
  }
  return false; // UID is not authorized
}

void startIndicatorTimer(unsigned long duration) {
  indicatorStart = millis(); // store the current time/ calling back the global variable with the proper functions
  indicatorTime = duration; // store the duration
  indicatorOn = true; // set the indicator to on
}

void redOFF() {
  digitalWrite(LED_RED, LOW);
}

void onAccessGranted(){
  Serial.println("Access granted");
  indicatorOn = false;
  redOFF();

  roomOccupied = !roomOccupied; // toggle the state of the room

  if(roomOccupied == true && buttonPressed == false){ // if the room is occupied and the button is not pressed, it will check in the user
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("Room: OCCUPIED");
    dataFile = SD.open("/checkins.csv", FILE_APPEND); // makes that the data is added one after the other line by line
    dataFile.print(millis() / 1000); // tells the time in seconds since the program started
    dataFile.print(","); //tells the code to go to the next column
    dataFile.println("Check-in");
    dataFile.close(); // saves
  } else if(roomOccupied == true && buttonPressed == true){ // if the room is occupied and the button is pressed, it will check out the user
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("Room: FREE, HELP NEEDED");
    dataFile = SD.open("/checkins.csv", FILE_APPEND);
    dataFile.print(millis() / 1000);
    dataFile.print(",");
    dataFile.println("Check-in");
    dataFile.close(); // saves 
  }else{
    digitalWrite(LED_GREEN, LOW);
    Serial.println("Room: FREE");
    dataFile = SD.open("/checkins.csv", FILE_APPEND);
    dataFile.print(millis() / 1000);
    dataFile.print(",");
    dataFile.println("Check-out");
    dataFile.close(); // saves
  }
}

void onAccessDenied(){
  Serial.println("Access denied");
  startIndicatorTimer(1000); // start the timer for 1 second
}

void onTimerExpired(){
  redOFF();
  indicatorOn = false;
  Serial.println( "READY");
}

void onCardScanned(String uid){




  if(uid == lastUID && millis() - lastScanTime < 2000) { // if the same card is scanned within 2 seconds, ignore it
    Serial.println("Card already scanned, please wait...");
    return;
  }
  lastUID = uid; // update the last scanned UID
  lastScanTime = millis(); // update the last scan time

  Serial.print("Card UID: ");
  Serial.println(uid);

  if(isAuthorized(uid) == true){
    onAccessGranted();
  }
  else{
    onAccessDenied();
  }
}


void setup() {
  pinMode(LED_RED, OUTPUT); // set the LED pins as output
  pinMode(LED_GREEN, OUTPUT);
  
  digitalWrite(LED_RED, LOW); // turn off the LEDs starting state
  digitalWrite(LED_GREEN, LOW);

  Serial.begin(115200); // start the serial communication
  SPI.begin(); // start the SPI bus
  rfid.PCD_Init(); // initialize the RFID reader

  Serial.println("Initializing SD card...");
  if (SD.begin(chipSelect)){
    Serial.println("SD card Found");
  } else {
    Serial.println("SD card not found");
  }

  dataFile = SD.open("/checkins.csv", FILE_WRITE); // This creates the file in esp32's format
  dataFile.println("Time,Room,Request"); // write the header to the file
  dataFile.close(); // close the file to save the changes
  

  Serial.println("tap a card...");
  Serial.println(" Room: FREE");


}

void loop() {
  if (rfid.PICC_IsNewCardPresent() == true && rfid.PICC_ReadCardSerial() == true) { //asking the reader if there is a new card present --> returns either true or false
    String uid = getUID(); // get the UID of the card
    Serial.print("Card UID: ");
    Serial.println(uid);
    rfid.PICC_HaltA(); //puts the reader into sleep mode so it isn't constantly reading
    rfid.PCD_StopCrypto1();  
  }

   // Timer
  if (indicatorOn == true){
    unsigned long elapsed = millis() - indicatorStart;

    if (elapsed >= indicatorTime){
      onTimerExpired();
    }
    else if ((elapsed / 200) % 2 == 0){
      digitalWrite(LED_RED, HIGH);
    }
    else{
      digitalWrite(LED_RED, LOW);
    }
  }
}
