#include <SPI.h>
#include <LoRa.h>

const int LED_PIN = 3;  // Pin del LED
const int BLINK_DELAY = 200;  // Tiempo de parpadeo en milisegundos

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("LoRa receptor");
  
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa!");
    while (1);
  }
}

void blinkTwice() {
  // Primer parpadeo
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_DELAY);
  
  // Segundo parpadeo
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_DELAY);

  // Tercer parpadeo
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_DELAY);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    
    // print RSSI of packet
    Serial.print(" ");
    Serial.println(LoRa.packetRssi());
    
    // Hacer parpadear el LED dos veces
    blinkTwice();
  }
}