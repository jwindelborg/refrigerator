#define RELAY 7

#define BTN_UP 10
#define BTN_DOWN 9
#define BTN_RETURN 8

#define TEMP_SENSOR A0

#define TARGET_TEMP_RAW 981
#define TEMP_MARGIN 12
#define LCD_DELAY 60

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

int btnUpState = 0;
int btnDwnState = 0;
int relayState = 0;
int tempSensor = 0;

int automaticMode = 1;

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);
  pinMode(BTN_RETURN, INPUT);
  pinMode(TEMP_SENSOR, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp ");
  lcd.setCursor(0,1);
  lcd.print("Relay off");

  digitalWrite(RELAY, HIGH);
}

void loop() {
  btnUpState = digitalRead(BTN_UP);
  btnDwnState = digitalRead(BTN_DOWN);
  
  if(btnUpState == LOW) {
    automaticMode = 0;
    relayState = 0;
    lcd.setCursor(6,1);
    lcd.print("off");
    digitalWrite(RELAY, HIGH);
  }
  
  if(btnDwnState == LOW) {
    automaticMode = 0;
    relayState = 1;
    lcd.setCursor(6,1);
    lcd.print("on ");
    digitalWrite(RELAY, LOW);
  }

  if(automaticMode) {
    // pump on, if pump is not on, and temperature is too low
    if(!relayState && tempSensor <= TARGET_TEMP_RAW - TEMP_MARGIN) {
      relayState = 1;
      digitalWrite(RELAY, LOW);
      lcd.setCursor(6,1);
      lcd.print("on ");
    }
    // pump off, if pump is on, and temperature is too high / high enough
    if(relayState && tempSensor >= TARGET_TEMP_RAW + TEMP_MARGIN) {
      relayState = 0;
      digitalWrite(RELAY, HIGH);
      lcd.setCursor(6,1);
      lcd.print("off");
    }
  }
  
  tempSensor = analogRead(TEMP_SENSOR);
  lcd.setCursor(6,0);
  lcd.print(tempSensor);
  delay(LCD_DELAY);
}
