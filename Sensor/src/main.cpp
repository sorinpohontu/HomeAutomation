// ESP8266 FileSystem
#include <FS.h>

// ESP8266
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// ESP8266 WiFiManager: https://github.com/tzapu/WiFiManager
#include <WiFiManager.h>

// DHT Temperature Sensor: https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>

// ArduinoJSON: https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>

// PrintEx: https://github.com/Chris--A/PrintEx
#include <PrintEx.h>

// Initialize DHT sensor
#define DHTPIN	D4			// DHT PIN
#define DHTTYPE DHT21   	// DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

// Deep sleep seconds
const int sleepTime = 30;

void setup()
{
	// Serial.setDebugOutput(true);
	Serial.begin(74880);

	PrintEx serialLog = Serial; // Wrap the Serial object in a PrintEx interface
	serialLog.println("Starting Setup");

	dht.begin();
	delay(2000);

	// Reading temperature or humidity takes about 250 milliseconds!
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		serialLog.println("Failed to read from DHT sensor!");
	} else {

		// Compute heat index in Celsius (isFahreheit = false)
		float hic = dht.computeHeatIndex(t, h, false);

		serialLog.printf("Temperature: %.2f *C, Humidity: %.2f %%, Heat index: %.2f *C\n", t, h, hic);
	}

	// Enter deepSleep
	ESP.deepSleep(sleepTime * 1000000);
}

void loop()
{

}
