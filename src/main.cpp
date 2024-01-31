#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <esp_sleep.h>

// Define the pins that we will use
#define DHTPIN 33 // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11 // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t previousMillis = 0;
const long interval = 5000;  // Interval de 5 secondes en millisecondes

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  // Mise en veille profonde (deep sleep) pendant 5 secondes
  Serial.println("Démarrage de la mise en veille...");
  Serial.println();
  esp_sleep_enable_timer_wakeup(interval * 1000); // Conversion en microsecondes
  delay(10);
  Serial.flush();
  
  esp_deep_sleep_start();
}

void loop() {
  // La fonction loop est vide car nous utilisons la mise en veille profonde
}






// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor


// #define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.



