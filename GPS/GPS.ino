#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial ss(4, 3);

float latitude;
float longitude;
String googleMapLink;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("Ready");
}

void loop() {
  if (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();  // Store latitude
        longitude = gps.location.lng();  // Store longitude

        // Create the Google Maps link with latitude and longitude
        googleMapLink = "https://www.google.com/maps/search/?api=1&query=";
        googleMapLink += String(latitude, 6);  // Convert latitude to String with 6 decimal places
        googleMapLink += ",";
        googleMapLink += String(longitude, 6);  // Convert longitude to String with 6 decimal places

        // Print latitude, longitude, and Google Maps link
        Serial.print(F("Latitude: "));
        Serial.println(latitude, 6);
        Serial.print(F("Longitude: "));
        Serial.println(longitude, 6);
        Serial.print(F("Google Maps Link: "));
        Serial.println(googleMapLink);
      } else {
        googleMapLink = "https://www.google.com/maps/search/?api=1&query=22.929950,90.851372";

        Serial.println(googleMapLink + "Do Fun");
      }
    }
  }
}
