// ===================================================
//  IoT Appliance Control — NodeMCU ESP8266 (Optimized)
// ===================================================

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

// ── WiFi credentials ──────────────
const char* ssid     = "mmd";
const char* password = "damumadi";

// ── SoftwareSerial to Arduino ─────
SoftwareSerial arduinoSerial(D6, D5);   // RX, TX

ESP8266WebServer server(80);
const int STATUS_LED = 2;

// ── Optimized sendCmd (less String usage) ─────
ICACHE_FLASH_ATTR void sendCmd(const String& cmd, const String& desc) {
  arduinoSerial.println(cmd);
  Serial.print("→ Arduino: "); Serial.println(cmd);

  digitalWrite(STATUS_LED, LOW);
  delay(60);
  digitalWrite(STATUS_LED, HIGH);

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK: " + desc);
}

ICACHE_FLASH_ATTR void handleRoot() {
  server.send(200, "text/plain",
    "ESP8266 Relay Gateway running.\n"
    "Endpoints: /R1ON /R1OFF ... /ALL_OFF");
}

void setup() {
  Serial.begin(115200);
  delay(1000);                    // Important: give Serial time to init
  arduinoSerial.begin(9600);

  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH); // LED OFF

  Serial.println("\n\n=== ESP8266 WiFi Gateway Starting ===");

  // === Critical fixes for stability ===
  WiFi.persistent(false);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to: "); Serial.println(ssid);
  WiFi.begin(ssid, password);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
    tries++;
    if (tries > 60) {               // Increased timeout
      Serial.println("\n[!] WiFi connection failed! Restarting...");
      ESP.restart();
    }
  }

  // Now it should reliably reach here
  digitalWrite(STATUS_LED, LOW);   // Solid ON = connected
  Serial.println("\n[✓] WiFi Connected!");
  Serial.print("[✓] IP Address: http://");
  Serial.println(WiFi.localIP());
  Serial.println(">>> Copy this IP for your app <<<");

  // Register endpoints
  server.on("/",         handleRoot);
  server.on("/R1ON",     []() { sendCmd("R1ON",   "Relay1 ON");  });
  server.on("/R1OFF",    []() { sendCmd("R1OFF",  "Relay1 OFF"); });
  server.on("/R2ON",     []() { sendCmd("R2ON",   "Relay2 ON");  });
  server.on("/R2OFF",    []() { sendCmd("R2OFF",  "Relay2 OFF"); });
  server.on("/R3ON",     []() { sendCmd("R3ON",   "Relay3 ON");  });
  server.on("/R3OFF",    []() { sendCmd("R3OFF",  "Relay3 OFF"); });
  server.on("/R4ON",     []() { sendCmd("R4ON",   "Relay4 ON");  });
  server.on("/R4OFF",    []() { sendCmd("R4OFF",  "Relay4 OFF"); });
  server.on("/ALL_ON",   []() { sendCmd("ALL_ON", "All relays ON"); });
  server.on("/ALL_OFF",  []() { sendCmd("ALL_OFF","All relays OFF"); });

  server.onNotFound([]() {
    server.send(404, "text/plain", "404 - Unknown endpoint");
  });

  server.begin();
  Serial.println("[✓] HTTP server started on port 80");
  Serial.println("Ready! You can now test from browser.");
}

void loop() {
  server.handleClient();
  // yield();   // uncomment if you notice instability later
}
