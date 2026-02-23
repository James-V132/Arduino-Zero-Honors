#include<SPI.h>
#include<MFRC522.h>

/*
  SDA/SS = Pin 7
  SCK = Pin 13
  MOSI = Pin 11
  MISO = Pin 12
  IRQ = *Unconnected*
  GND = GND
  RST = Pin 8
  3.3V = 3.3V
*/


#define RST_PIN 8
#define SS_PIN 7
MFRC522 myFRID(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {  
  Serial.begin(9600); // Initiate a serial communication
  SPI.begin(); // Initiate SPI bus
  myFRID.PCD_Init(); // Initiate MFRC522

  Serial.println("Please scan your RFID card...");
  Serial.println();

}

void loop() {

  // Wait for RFID cards to be scanned
  myFRID.PCD_Init();
  if(!myFRID.PICC_IsNewCardPresent() || !myFRID.PICC_ReadCardSerial())
  {
    return;
  }
  // Show UID on serial monitor
  Serial.print("USER ID tag :"); // Print card's unique ID
  String content = "";

  for(byte i = 0; i < myFRID.uid.size; i++) // Loops through cards unique ID and displays through serial monitor
  {
    Serial.print(myFRID.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(myFRID.uid.uidByte[i], HEX);

    content.concat(String(myFRID.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(myFRID.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if(content.substring(1) == "7B C0 AD 21") 
  {
    Serial.println("Access Granted!");
    Serial.println();
    delay(2000);
  }
  else
  {
    Serial.println("Access Denied!");
    delay(2000);
  }

  myFRID.PICC_HaltA();

}
