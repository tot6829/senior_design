#define BLYNK_TEMPLATE_ID "TMPL2S67kycsb"
#define BLYNK_TEMPLATE_NAME "LED Controller"
#define BLYNK_AUTH_TOKEN "z75PDW_lM-EKdAfV7V8COMuc4rYpdB9u"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char auth[] = "z75PDW_lM-EKdAfV7V8COMuc4rYpdB9u";
char ssid[] = "Devin iphone";
char pass[] = "oau0jc48psdao";

// Pins for LEDs
#define LED_PIN_1 12
#define LED_PIN_2 14
#define LED_PIN_3 27
#define LED_PIN_4 26

// Variables to store LED states and brightness
bool ledState1 = false;
bool ledState2 = false;
bool ledState3 = false;
bool ledState4 = false;
int brightness1 = 0;
int brightness2 = 0;
int brightness3 = 0;
int brightness4 = 0;
int brightness = 50;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  Blynk.begin(auth, ssid, pass);

  // Set the LED pins as outputs
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
}

void loop() {
  Blynk.run();
}

// Function to update LED state and brightness
void updateLed(int ledPin, bool ledState, int brightness) {
  if (ledState) {
    analogWrite(ledPin, brightness);
    Serial.println("Goodbye!");
  } else {
    Serial.println("Hello!");
    analogWrite(ledPin, 0); // Turn LED off
  }
}

// Blynk virtual pins configuration
BLYNK_WRITE(V1) {  // Virtual pin for LED 1 button
  ledState1 = param.asInt(); // Update LED state
  if (ledState1)
    brightness1 = brightness;
  Serial.println(ledState1);
  updateLed(LED_PIN_1, ledState1, brightness1);
}


BLYNK_WRITE(V2) {  // Virtual pin for LED 2 button
  ledState2 = param.asInt(); // Update LED state
  brightness2 = ledState2 ? param.asInt() : 0; // Adjust brightness if LED is turned on
  updateLed(LED_PIN_2, ledState2, brightness2);
}

BLYNK_WRITE(V3) {  // Virtual pin for LED 3 button
  ledState3 = param.asInt(); // Update LED state
  brightness3 = ledState3 ? param.asInt() : 0; // Adjust brightness if LED is turned on
  updateLed(LED_PIN_3, ledState3, brightness3);
}

BLYNK_WRITE(V4) {  // Virtual pin for LED 4 button
  ledState4 = param.asInt(); // Update LED state
  brightness4 = ledState4 ? param.asInt() : 0; // Adjust brightness if LED is turned on
  updateLed(LED_PIN_4, ledState4, brightness4);
}

BLYNK_WRITE(V5) {  // Virtual pin for brightness slider
  brightness = param.asInt(); // Get value from Blynk app
  // Update brightness for all LEDs
  brightness1 = brightness * ledState1;
  brightness2 = brightness * ledState2;
  brightness3 = brightness * ledState3;
  brightness4 = brightness * ledState4;
  analogWrite(LED_PIN_1, brightness1);
  analogWrite(LED_PIN_2, brightness2);
  analogWrite(LED_PIN_3, brightness3);
  analogWrite(LED_PIN_4, brightness4);
}
