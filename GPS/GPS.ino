#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <BluetoothSerial.h>// Assuming you need it for Bluetooth later

SoftwareSerial Dta(2, 3); // Pins 2 (RX) and 3 (TX) for GPS communication
TinyGPSPlus gps;          // Create a TinyGPS++ object

void setup(){
  Serial.begin(9600);     // Initialize serial monitor
  Dta.begin(9600);        // Initialize SoftwareSerial for GPS
}

void loop(){
  while (Dta.available() > 0) {
    byte gpsData = Dta.read();
    if (gps.encode(gpsData)) {    // Parse GPS data
      if (gps.location.isValid()) {   // If valid GPS data
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);   // Print latitude
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);   // Print longitude
      }
    }
  }
}
