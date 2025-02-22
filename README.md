
---

# *🚦 Traffic Light Automation for Emergency Vehicles Using LoRa 🚑*  

## *Overview*  
This project automates traffic signals to prioritize emergency vehicles using *LoRa (Long Range)* communication. When an ambulance approaches a traffic signal within a specific *RSSI threshold (-25 dBm)*, the system automatically changes the lights to allow it to pass safely.  

## *How It Works*  
- The *ambulance* is equipped with a *LoRa transmitter (Arduino Uno)* that continuously sends signals.  
- A *LoRa receiver (Arduino Mega)* at the *traffic light module* detects the signal strength (*RSSI*).  
- Based on the distance (RSSI value), the traffic lights change accordingly:  
  1. *If RSSI is stronger than -25 dBm* (ambulance is near):  
     - Signal *1* → *Amber (5s), then Red (10s)*  
     - Signal *2* → *Red (5s), then Green (10s)*  
  2. *If RSSI is weaker than -25 dBm* (ambulance is far):  
     - Normal traffic cycle resumes.  

---

## *🛠 Components Used*  
- *Arduino Mega 2560* (LoRa Receiver & Traffic Light Controller)  
- *Arduino Uno* (LoRa Transmitter in Ambulance)  
- *SX1278 LoRa Module* (One for transmitter, one for receiver)  
- *Traffic Light LEDs (2 Sets, Each with Red, Yellow, Green)*  
- *Voltage Level Shifter (4-channel)* (For SPI communication with LoRa)  
- *Resistors (1kΩ, 2kΩ)* (For MOSI voltage divider)  

---

## *🔌 Circuit Connections*  

### *🔹 LoRa Transmitter (Arduino Uno)*
| *LoRa SX1278 Pin* | *Arduino Uno Pin* |
|---------------------|---------------------|
| *VCC* | 3.3V |
| *GND* | GND |
| *SCK* | 13 |
| *MISO* | 12 |
| *MOSI* | 11 (*via Voltage Divider*) |
| *NSS (CS)* | 10 |
| *RST* | 9 |
| *DIO0* | 2 |

---

### *🔹 LoRa Receiver (Arduino Mega)*
| *LoRa SX1278 Pin* | *Arduino Mega Pin* |
|---------------------|---------------------|
| *VCC* | 3.3V |
| *GND* | GND |
| *SCK* | 52 |
| *MISO* | 50 |
| *MOSI* | 51 (*via Level Converter*) |
| *NSS (CS)* | 53 |
| *RST* | 48 |
| *DIO0* | 2 |

---

### *🔹 Traffic Light Module (Arduino Mega)*
| *Traffic Light* | *LED Color* | *Arduino Mega Pin* |
|------------------|-------------|---------------------|
| *Signal 1* | *Red* | 3 |
| *Signal 1* | *Yellow* | 4 |
| *Signal 1* | *Green* | 5 |
| *Signal 2* | *Red* | 6 |
| *Signal 2* | *Yellow* | 7 |
| *Signal 2* | *Green* | 8 |

---

## *📜 Code Overview*  
There are *two separate codes* for the *transmitter (Arduino Uno)* and *receiver (Arduino Mega)*.

1. *Transmitter (Arduino Uno)* → Sends a LoRa signal with RSSI.
2. *Receiver (Arduino Mega)* → Reads RSSI and controls the traffic lights based on signal strength.  

---

## *🚀 How to Run the Project*
1. *Upload the Transmitter Code* (transmitter.ino) to *Arduino Uno*.
2. *Upload the Receiver Code* (receiver.ino) to *Arduino Mega*.
3. *Place the transmitter in the ambulance* and *power on both Arduinos*.
4. *Monitor the RSSI value* in the receiver's serial monitor.
5. *Watch the traffic lights change based on the RSSI threshold (-25 dBm).*  

---

## *🔍 Troubleshooting*
- *LoRa init failed?*  
  - Check wiring and power (LoRa requires 3.3V, NOT 5V).  
  - Ensure MOSI uses a *voltage divider (1kΩ + 2kΩ)*.  

- *RSSI always shows -164 dBm?*  
  - LoRa module may not be receiving data → Check antennas and frequency (433MHz).  
  - Move transmitter and receiver closer to verify communication.  

- *Traffic lights not responding?*  
  - Ensure traffic lights are correctly connected to *pins 3, 4, 5, 6, 7, 8* on *Arduino Mega*.  

---

## *📌 Future Improvements*
- *GPS-based tracking for real-world implementation.*  
- *Integration with a siren detection system.*  
- *Cloud monitoring for emergency vehicle tracking.*  

---

## *🔚 Conclusion*  
This project demonstrates a practical solution to improve emergency vehicle response times using *LoRa-based traffic light automation. By prioritizing ambulances at intersections, this system can help **reduce delays, prevent accidents, and save lives. Future enhancements like **GPS integration, siren detection, and cloud-based monitoring* could make this system more efficient and applicable to real-world smart city infrastructure. 🚦🚑  

---
