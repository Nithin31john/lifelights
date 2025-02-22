#include <SPI.h>
#include <LoRa.h>

#define NSS 46
#define RST 44
#define DIO0 42

// Traffic Light Module Pins
#define RED1 3
#define YELLOW1 4
#define GREEN1 5
#define RED2 6
#define YELLOW2 7
#define GREEN2 8

int rssi_threshold = -160;  // Adjust this if needed
bool emergencyMode = false;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("LoRa Receiver Initializing...");

    LoRa.setPins(NSS, RST, DIO0);

    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa init failed!");
        while (1);
    }
    Serial.println("LoRa initialized successfully!");

    pinMode(RED1, OUTPUT);
    pinMode(YELLOW1, OUTPUT);
    pinMode(GREEN1, OUTPUT);
    pinMode(RED2, OUTPUT);
    pinMode(YELLOW2, OUTPUT);
    pinMode(GREEN2, OUTPUT);

    normalTrafficCycle();
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

        // Debug: Print RSSI threshold check
        Serial.print("Comparing RSSI: "); Serial.print(rssi);
        Serial.print(" with Threshold: "); Serial.println(rssi_threshold);

        if (rssi <= rssi_threshold) {  
            Serial.println("🚨 Emergency Mode Activated!");
            emergencyMode = true;
            emergencyTrafficCycle();
        } else {  
            Serial.println("✅ Normal Traffic Mode");
            if (emergencyMode) {
                emergencyMode = false;
                normalTrafficCycle();
            }
        }
    } else {
        // Print RSSI even when no packet is received
        int rssi = LoRa.packetRssi();
        Serial.print("RSSI: "); Serial.println(rssi);
        delay(500);
    }
}

// 🚦 Normal Traffic Light Cycle
void normalTrafficCycle() {
    Serial.println("Running Normal Traffic Cycle...");

    while (!emergencyMode) {
        Serial.println("RSSI Monitoring in Normal Mode...");
        Serial.print("Current RSSI: "); Serial.println(LoRa.packetRssi());

        // Signal 1: Green | Signal 2: Red
        digitalWrite(GREEN1, HIGH);
        digitalWrite(RED2, HIGH);
        delay(5000);

        // Signal 1: Yellow | Signal 2: Red
        digitalWrite(GREEN1, LOW);
        digitalWrite(YELLOW1, HIGH);
        delay(2000);
        digitalWrite(YELLOW1, LOW);

        // Signal 1: Red | Signal 2: Green
        digitalWrite(RED1, HIGH);
        digitalWrite(RED2, LOW);
        digitalWrite(GREEN2, HIGH);
        delay(5000);

        // Signal 1: Red | Signal 2: Yellow
        digitalWrite(GREEN2, LOW);
        digitalWrite(YELLOW2, HIGH);
        delay(2000);
        digitalWrite(YELLOW2, LOW);
        digitalWrite(RED2, HIGH);
        digitalWrite(RED1, LOW);
    }
}

// 🚨 Emergency Traffic Light Cycle
void emergencyTrafficCycle() {
    Serial.println("Running Emergency Traffic Mode...");
    Serial.print("Current RSSI: "); Serial.println(LoRa.packetRssi());

    // Signal 1: Amber | Signal 2: Red for 5 seconds
    digitalWrite(YELLOW1, HIGH);
    digitalWrite(RED1, LOW);
    digitalWrite(GREEN1, LOW);
    digitalWrite(RED2, HIGH);
    digitalWrite(GREEN2, LOW);
    digitalWrite(YELLOW2, LOW);
    delay(5000);

    // Signal 1: Red | Signal 2: Green for 10 seconds
    digitalWrite(YELLOW1, LOW);
    digitalWrite(RED1, HIGH);
    digitalWrite(GREEN1, LOW);
    digitalWrite(RED2, LOW);
    digitalWrite(GREEN2, HIGH);
    digitalWrite(YELLOW2, LOW);
    delay(10000);

    emergencyMode = false;
    normalTrafficCycle();
}