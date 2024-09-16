#include <WiFi.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// WiFi credentials
const char* ssid = "Abbigeri 4g";
const char* password = "9480410589";

// GPS
TinyGPSPlus gps;
HardwareSerial neo6mSerial(1); // Using Serial1 for the Neo-6M GPS module

// Function to connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
}

void setup() {
  Serial.begin(115200);
  neo6mSerial.begin(9600, SERIAL_8N1, 16, 17); // RX = GPIO16, TX = GPIO17 (adjust based on wiring)

  connectToWiFi();
}

void loop() {
  while (neo6mSerial.available()) {
    char c = neo6mSerial.read();
    // Serial.print(c);

    if(gps.encode(c)){

    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();

      Serial.print("Latitude: ");
      Serial.println(latitude);
      Serial.print("Longitude: ");
      Serial.println(longitude);
    }
  }
}
}
