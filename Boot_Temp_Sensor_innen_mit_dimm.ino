#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// set the I2C address to 0x3f
// for 4 line display with 20 char per line
// connect I2C Adapter as follows: A4 - SDA, A5 - SCL
// connect DS18B20 to pin D3
// connect Buzzer to pin D4
// Pin 7 von U1 auf dem I2C-Board entlöten
// den Basisanschluss von Q1 über einen 220Ohm Widerstand mit Pin D9 (int LCDPin = 9;) verbinden
// Der Widerstand für den Helligkeitssensor beträgt 1kOhm
// Der Eingangspin für den Helligkeitssensor ist A0: "(analogRead(0)"
// Die Programme werden mit dem USBasp Programmer geladen
// Die Einstellungen für das Board: ATMega 168, Internal, 8Mhz, ohne Bootloader, Variant 168PA

LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
constexpr uint8_t BuzzerPin = 4;
int LCDPin = 9; // PWM-Ausgangs-Pin für das Display

#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// aktuelle Adressen der Sensoren
// Seewasser: 28FF88056E1801A9
// Auspuff:   28FFE6196E180130
// Motorraum: 28FF516B6D180165
// Drucklager:28FF0BF6681803B8

float Temperatur[4];
float TempAlarm = 70; // hier die maximale Temperatur für "Auspuff" eingeben

// Sensoren 0-3 feste Vorgabe der Adressen der Temperatursensoren
DeviceAddress Sensor0 = {0x28, 0xFF, 0x88, 0x05, 0x6E, 0x18, 0x01, 0xA9}; // Seewasser
DeviceAddress Sensor1 = {0x28, 0xFF, 0xE6, 0x19, 0x6E, 0x18, 0x01, 0x30}; // Auspuff
DeviceAddress Sensor2 = {0x28, 0xFF, 0x51, 0x6B, 0x6D, 0x18, 0x01, 0x65}; // Motorraum
DeviceAddress Sensor3 = {0x28, 0xFF, 0x0B, 0xF6, 0x68, 0x18, 0x03, 0xB8}; // Drucklager

void setup() {
  lcd.begin(20, 4);
  lcd.clear();
  lcd.backlight();
  sensors.begin();
  pinMode(BuzzerPin, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();
  Temperatur[0] = sensors.getTempC(Sensor0);
  Temperatur[1] = sensors.getTempC(Sensor1);
  Temperatur[2] = sensors.getTempC(Sensor2);
  Temperatur[3] = sensors.getTempC(Sensor3);

  lcd.setCursor(1, 0);
  lcd.print("Seewasser: ");
  lcd.print(Temperatur[0]);
  lcd.setCursor(17, 0);
  lcd.write(223);             // ergibt das "Grad" Zeichen
  lcd.print("C  ");

  lcd.setCursor(1, 1);
  lcd.print("Auspuff  : ");
  lcd.print(Temperatur[1]);
  lcd.setCursor(17, 1);
  lcd.write(223);
  lcd.print("C  ");

  lcd.setCursor(1, 2);
  lcd.print("Motorraum: ");
  lcd.print(Temperatur[2]);
  lcd.setCursor(17, 2);
  lcd.write(223);
  lcd.print("C  ");

  lcd.setCursor(1, 3);
  lcd.print("Dr-Lager : ");  
  lcd.print(Temperatur[3]);
  lcd.setCursor(17, 3);
  lcd.write(223);
  lcd.print("C  ");

  if (Temperatur[1] > TempAlarm) {            // Temp Wert "Auspuff" mit "TempAlarm" vergleichen
    digitalWrite(BuzzerPin, HIGH);
    delay(1000);
    digitalWrite(BuzzerPin, LOW);
  }
  delay(5000);
  
if(analogRead(0)>= 190)
  analogWrite(LCDPin, 255);
else
  analogWrite(LCDPin, 10);  
}
