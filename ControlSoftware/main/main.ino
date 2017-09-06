#define RELAY_STATE_LED 11
#define RELAY 7

#define BTN_UP 10
#define BTN_DOWN 9
#define BTN_RETURN 8

#define TEMP_SENSOR A0

#define TARGET_TEMP_RAW 979
#define BTN_DELAY 60

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

int btnUpState = 0;
int btnDwnState = 0;
int relayState = 0;
int tempSensor = 0;

void setup() {
  pinMode(RELAY_STATE_LED, OUTPUT);
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
  
  if (btnUpState == LOW) {
    relayState = 0;
    lcd.setCursor(6,1);
    lcd.print("off");
    digitalWrite(RELAY, HIGH);
    digitalWrite(RELAY_STATE_LED, LOW);
  }
  
  if (btnDwnState == LOW) {
    relayState = 1;
    lcd.setCursor(6,1);
    lcd.print("on ");
    digitalWrite(RELAY, LOW);
    digitalWrite(RELAY_STATE_LED, HIGH);
  }
  
  tempSensor = analogRead(TEMP_SENSOR);
  lcd.setCursor(6,0);
  lcd.print(tempSensor);
  delay(BTN_DELAY);
}
