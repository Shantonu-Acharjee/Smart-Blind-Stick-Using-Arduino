#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);

void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("Ready");
}

void loop()
{
  if (ss.available() > 0)
    if (gps.encode(ss.read())) {
      Serial.print(F("Location "));
      if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.write(',');
        Serial.println(gps.location.lng(), 6);
      } else {
        Serial.println(F(" is not valid."));
      }
    }
}