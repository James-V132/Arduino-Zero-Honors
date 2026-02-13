#include<LiquidCrystal.h>
#include<SPI.h>
#include<MFRC522.h>

LiquidCrystal lcd(9, 10, 5, 4, 3, 2);

#define RST_PIN 8
#define SS_PIN 7
MFRC522 myFRID(SS_PIN, RST_PIN);

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  SPI.begin();
  myFRID.PCD_Init();

  Serial.println("Please scan your RFID card...");
  Serial.println();
}

void loop() {

  myFRID.PCD_Init();

  if(!myFRID.PICC_IsNewCardPresent() || !myFRID.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("USER ID tag :"); 
  String content = "";

  for(byte i = 0; i < myFRID.uid.size; i++) 
  {
    Serial.print(myFRID.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(myFRID.uid.uidByte[i], HEX);

    content.concat(String(myFRID.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(myFRID.uid.uidByte[i], HEX));
  }
  Serial.println();
  myFRID.PICC_HaltA();

  lcd.setCursor(0, 0);
  content.toUpperCase();
  lcd.print(content);

}
