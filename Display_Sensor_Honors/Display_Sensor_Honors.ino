#include<LiquidCrystal.h>
#include<SPI.h>
#include<MFRC522.h>
#include <ArduinoHttpClient.h>
#include <WiFiS3.h> // Or the library for your specific board

// Your network credentials
const char* ssid = "EK iPhone 16";
const char* pass = "Password";

LiquidCrystal lcd(9, 10, 5, 4, 3, 2);

#define RST_PIN 8
#define SS_PIN 7
MFRC522 myFRID(SS_PIN, RST_PIN);

// Server details
const char* serverAddress = "IP";
int port = 80;

WiFiClient client;
HttpClient http_client = HttpClient(client, serverAddress, port);

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print("Please Scan...");
  
  SPI.begin();
  myFRID.PCD_Init();

  Serial.begin(9600);
  Serial.println();
  Serial.println("Please scan your RFID card...");
  Serial.println();
}

void loop() {
  //PICC_IsNewCardPresent() = Look for new nearby card(s) and returns true if one is found
  //PICC_ReadCardSerial() = Select one of the cards if multiple cards are present
  if(!myFRID.PICC_IsNewCardPresent() || !myFRID.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("USER ID tag :"); 
  String content = "";

  //If successfully scanned the card's ID is stored in myFRID.uid
  //myFRID.uid.size = how many bytes
  //myFRID.uid.uidByte[] = array holding numerical values of ID
  for(byte i = 0; i < myFRID.uid.size; i++) 
  {
    Serial.print(myFRID.uid.uidByte[i] < 0x10 ? " 0" : " "); //If number < 16 ensurses leading 0 before printing byte
    Serial.print(myFRID.uid.uidByte[i], HEX); //Converts byte into hexidecimal

    content.concat(String(myFRID.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(myFRID.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.println();
  
  http_client.post("/db/queries/postEntry.sql");
  myFRID.PICC_DumpToSerial(&(myFRID.uid)); // Dumps all info available from card and displays it

  lcd.setCursor(0, 0);
  lcd.clear();

  content.toUpperCase();
  lcd.print(content);

  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Please Scan...");

}
