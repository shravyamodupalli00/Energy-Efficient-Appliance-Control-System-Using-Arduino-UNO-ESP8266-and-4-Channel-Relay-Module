// ===================================================
//  Final Arduino UNO Relay Controller
//  Works with corrected LLC wiring (D5→LV2, D6→LV1)
// ===================================================

#include <SoftwareSerial.h>

// SoftwareSerial: D11 = RX, D10 = TX  (matches corrected wiring)
SoftwareSerial espSerial(11, 10); 

// Relay pins - active LOW (LOW = relay ON)
const int RELAY1 = 2;
const int RELAY2 = 3;
const int RELAY3 = 4;
const int RELAY4 = 5;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  // IMPORTANT: Set HIGH before pinMode to prevent relay activation at boot
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  Serial.println("\n=== Arduino Relay Controller READY ===");
  Serial.println("All relays initialized to OFF");
  Serial.println("Waiting for commands from NodeMCU...\n");
  
  delay(800);
}

void loop() {
  if (espSerial.available()) {
    String cmd = espSerial.readStringUntil('\n');
    cmd.trim();

    Serial.print("Received: [");
    Serial.print(cmd);
    Serial.println("]");

    if (cmd == "R1ON") {
      digitalWrite(RELAY1, LOW);
      Serial.println("→ Relay 1 TURNED ON");
    }
    else if (cmd == "R1OFF") {
      digitalWrite(RELAY1, HIGH);
      Serial.println("→ Relay 1 TURNED OFF");
    }
    else if (cmd == "R2ON") {
      digitalWrite(RELAY2, LOW);
      Serial.println("→ Relay 2 TURNED ON");
    }
    else if (cmd == "R2OFF") {
      digitalWrite(RELAY2, HIGH);
      Serial.println("→ Relay 2 TURNED OFF");
    }
    else if (cmd == "R3ON") {
      digitalWrite(RELAY3, LOW);
      Serial.println("→ Relay 3 TURNED ON");
    }
    else if (cmd == "R3OFF") {
      digitalWrite(RELAY3, HIGH);
      Serial.println("→ Relay 3 TURNED OFF");
    }
    else if (cmd == "R4ON") {
      digitalWrite(RELAY4, LOW);
      Serial.println("→ Relay 4 TURNED ON");
    }
    else if (cmd == "R4OFF") {
      digitalWrite(RELAY4, HIGH);
      Serial.println("→ Relay 4 TURNED OFF");
    }
    else if (cmd == "ALL_ON") {
      digitalWrite(RELAY1, LOW);
      digitalWrite(RELAY2, LOW);
      digitalWrite(RELAY3, LOW);
      digitalWrite(RELAY4, LOW);
      Serial.println("→ ALL Relays TURNED ON");
    }
    else if (cmd == "ALL_OFF") {
      digitalWrite(RELAY1, HIGH);
      digitalWrite(RELAY2, HIGH);
      digitalWrite(RELAY3, HIGH);
      digitalWrite(RELAY4, HIGH);
      Serial.println("→ ALL Relays TURNED OFF");
    }
    else {
      Serial.print("Unknown command: ");
      Serial.println(cmd);
    }
  }
}