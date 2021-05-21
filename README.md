# Temperatur-Monitor-Inside
A Monitor to display the various temperatur sensors inside a boat

Required hardware: Arduino mini (a ATMega 168 is sufficient) , LCD Display 4 x 20 with I2C-adapter FC113, DS1820B, 12 to 5V DC-DC adapter, LDR, active beeper

The address of the DS1820B has to be identified and inserted into the code prior programming. The display can be dimmed in darkness. The threshold of the dimming can be adapted by changing the value "if(analogRead(3)>= 190) //threshold" The min brightness is defined by the value " analogWrite(LCDPin, 10); // dimmed brightness"
An alarm will be triggered, if the the temp of the "Auspuff" (exhaust) goes above the value in "float TempAlarm = 70; // hier die maximale Temperatur für "Auspuff" eingeben". In this case the value is set to 70 degrees C.
