#define relayState 11
#define rellay 7

#define btnUp 10
#define btnDwn 9
#define btnReturn 8

#define term A0

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 20 chars and 4 line display
  int btnUpState = 0;
  int relay = 0;
  int btnDwnState = 0;
  int tempSense = 0;
  
void setup() {
  pinMode(relayState, OUTPUT);
  pinMode(rellay, OUTPUT);
  pinMode(btnUp, INPUT);
  pinMode(btnDwn, INPUT);
  pinMode(btnReturn, INPUT);
  pinMode(term, INPUT);
  
   
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Temp ");
    lcd.setCursor(0,1);
    lcd.print("Relay ");

    digitalWrite(rellay, LOW);
 


}

void loop() {
  // put your main code here, to run repeatedly:
btnUpState = digitalRead(btnUp);
btnDwnState = digitalRead(btnDwn);
  if (btnUpState == LOW) {
    if (relay) {
      relay = 0;
      lcd.setCursor(6,1);
      lcd.print("off");
      digitalWrite(rellay, HIGH);
       digitalWrite(relayState, LOW);

    }
  }
    if (btnDwnState == LOW) {
      relay = 1;
      lcd.setCursor(6,1);
      lcd.print("on ");
      digitalWrite(rellay, LOW);
       digitalWrite(relayState, HIGH);


    btnUpState = 0;
    delay(500);
  }
tempSense = analogRead(term);
 lcd.setCursor(6,0);
  lcd.print(tempSense);
  delay(50);
}
