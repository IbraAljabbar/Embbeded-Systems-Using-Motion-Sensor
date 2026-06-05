#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi Credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// Sensor and Actuator Pin Mapping
const int pirPin = D5;
const int ledPin = D6;
const int buzzerPin = D7;

int ldrValue;
int motion;

// Adjust this variable if ambient light readings change
const int darkThreshold = 550;

BlynkTimer timer;

// ================= BLYNK VIRTUAL PINS =================
// V0 = Ambient Light Value (LDR)
// V1 = Motion State (PIR: 0 or 1)
// V2 = System Alarm Security Status String

void checkEnvironmentAndAlert() {
  // Read sensor inputs
  ldrValue = analogRead(A0);
  motion = digitalRead(pirPin);

  // Print telemetry data to Serial Monitor
  Serial.print("LDR = ");
  Serial.print(ldrValue);
  Serial.print(" | PIR = ");
  Serial.println(motion);

  // Push raw numeric telemetry to Blynk App Virtual Pins
  Blynk.virtualWrite(V0, ldrValue);
  Blynk.virtualWrite(V1, motion);

  // Evaluate if the ambient environment is dark
  bool isDark = (ldrValue > darkThreshold);

  // Automated nighttime light control
  if (isDark) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Active intrusion alarm triggers when dark and motion is detected
  if (isDark && motion == HIGH) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("WARNING: Motion Detected!");
    
    // Push emergency notification status string to Blynk Dashboard
    Blynk.virtualWrite(V2, "CRITICAL: Intrusion Detected!");
  } else {
    digitalWrite(buzzerPin, LOW);
    
    // Reset status message on the cloud dashboard
    if (isDark) {
      Blynk.virtualWrite(V2, "Secured (Night Mode)");
    } else {
      Blynk.virtualWrite(V2, "Secured (Day Mode)");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.println("Connecting to Blynk Cloud...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Read sensors and transmit packets every 1 second (1000ms) safely
  timer.setInterval(1000L, checkEnvironmentAndAlert);

  Serial.println("IoT Smart Home Security System Ready.");
}

void loop() {
  Blynk.run();
  timer.run();
}
