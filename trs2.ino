#include <SPI.h>
#include <LoRa.h>

#define NSS 46
#define RST 44
#define DIO0 42

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("LoRa Receiver Test...");

    LoRa.setPins(NSS, RST, DIO0);
    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa init failed!");
        while (1);
    }
    Serial.println("LoRa initialized successfully!");
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String message = "";
        while (LoRa.available()) {
            message += (char)LoRa.read();
        }

        int rssi = LoRa.packetRssi();
        Serial.print("Received: "); Serial.print(message);
        Serial.print(" | RSSI: "); Serial.println(rssi);
    } else {
        Serial.println("No packets received...");
        delay(50000);
    }
}