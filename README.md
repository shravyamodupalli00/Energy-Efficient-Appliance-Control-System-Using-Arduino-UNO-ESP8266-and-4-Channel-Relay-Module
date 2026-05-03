# Energy-Efficient-Appliance-Control-System-Using-Arduino-UNO-ESP8266-and-4-Channel-Relay-Module
IoT-Based Energy-Efficient Appliance Control System A Wi-Fi enabled home appliance control system built with Arduino UNO, NodeMCU ESP8266, and a 4-channel relay module. Control up to four AC appliances remotely from a mobile app or web browser over your local network — no cloud required.
# How it works
The ESP8266 hosts a lightweight HTTP server on your local Wi-Fi network. When you tap a button in the app, it sends an HTTP GET request to an endpoint like /R1ON or /ALL_OFF. The ESP8266 forwards the command to the Arduino UNO via UART serial communication through a Logic Level Converter (LLC), which handles the 3.3V ↔ 5V voltage translation. The Arduino then drives the relay module to switch appliances on or off.

# Hardware
Arduino UNO (relay driver, pins D2–D5)
NodeMCU ESP8266 (Wi-Fi HTTP gateway, pins D5/D6)
4-Channel Relay Module (active LOW, 5V coil)
Bi-directional Logic Level Converter (3.3V ↔ 5V)
