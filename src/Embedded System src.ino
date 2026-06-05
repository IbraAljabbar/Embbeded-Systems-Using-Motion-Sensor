// ========================
// SMART HOME SECURITY SYSTEM
// ESP8266 + PIR + LDR + LED + BUZZER
// ========================

const int pirPin = D5;
const int ledPin = D6;
const int buzzerPin = D7;

int ldrValue;
int motion;

// Adjust this variable if ambient light readings change
const int darkThreshold = 550;

void setup() {
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.println("Smart Home Security System Active");
}

void loop() {
  // Read sensor inputs
  ldrValue = analogRead(A0);
  motion = digitalRead(pirPin);

  // Print telemetry data to Serial Monitor
  Serial.print("LDR = ");
  Serial.print(ldrValue);
  Serial.print(" | PIR = ");
  Serial.println(motion);

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
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);
}
