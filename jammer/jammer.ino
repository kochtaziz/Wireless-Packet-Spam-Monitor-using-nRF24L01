#include <SPI.h>
#include <RF24.h>

// CE and CSN pins for NRF24L01
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[5] = {'J','U','N','K','1'};  // Arbitrary target address
char payload[] = "XXXXXXXXXXXXXXXXXXXX";        // Garbage payload

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(100);              // Channel 100 = 2.5 GHz (can change 0–125)
  radio.setPALevel(RF24_PA_MAX);      // Max power
  radio.setDataRate(RF24_2MBPS);      // Fastest data rate
  radio.openWritingPipe(address);     // Set fake target address
  radio.stopListening();              // Set as transmitter
  Serial.println("Flooding started...");
}

void loop() {
  for (int i = 0; i < 100; i++) {
    radio.write(&payload, sizeof(payload));  // Spam packets
  }
}
