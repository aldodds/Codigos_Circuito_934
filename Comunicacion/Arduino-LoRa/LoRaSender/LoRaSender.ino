#include <SPI.h>      //Libreria para LoRa
#include <LoRa.h>     //Libreria para LoRa

const int LED_PIN = 3;  // Pin del LED

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println("LoRa receptor");
  
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Asegurarse que el LED comience apagado
  
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // Encender el LED cuando se recibe un paquete
    digitalWrite(LED_PIN, HIGH);
    
    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    
    // print RSSI of packet
    Serial.print(" ");
    Serial.println(LoRa.packetRssi());
    
    // Esperar un momento con el LED encendido
    delay(500);
    
    // Apagar el LED
    digitalWrite(LED_PIN, LOW);
  }
}