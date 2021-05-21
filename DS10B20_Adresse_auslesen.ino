
// mit diesem Programm werden die Adressen der DS18B20 Sensoren 
// im seriellen Monitor auf dem PC ausgegeben
// Der Sensor wird an Pin 3 angeschlossen

#include <OneWire.h>

OneWire  ds(3);  // Anschluss an PIN 3

void setup(void) {
  Serial.begin(9600);
  discoverOneWireDevices();
}

void discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  Serial.print("Nach 1 Leitung Sensor suchen\n\r");
  while(ds.search(addr)) {
    Serial.print("\n\rGefunden \'1-Wire\' fuehler mit der Adresse:\n\r");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }
  }
  Serial.print("\n\r\n\rDas war es... mehr kommmt nicht:)\r\n");
  ds.reset_search();
  return;
}

void loop(void) {
  // nothing to see here
}
  
