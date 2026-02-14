#include<LiquidCrystal.h>

LiquidCrystal lcd(9, 10, 5, 4, 3, 2);
/*
  VSS = GND (GND for logic)
  VDD = VCC (VCC for logic)
  V0 = Pot
  RS = Pin 9
  RW = GND (0 = Write)
  E = Pin 10
  D4 = Pin 5
  D5 = Pin 4
  D6 = Pin 3
  D7 = Pin 2
  A = 220Ohm Resistor (VCC for LED)
  K = GND (GND for LED)
*/

void setup() {
    lcd.begin(16,2);

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("My Chudling");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Evan :D");
  delay(2000);
}
