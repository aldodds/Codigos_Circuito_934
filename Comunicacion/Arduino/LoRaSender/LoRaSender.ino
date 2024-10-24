#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa transmisor");

  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa!");
    while (1);
  }
}

void loop() {
  Serial.print("Enviando paquete: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("Recibido: ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(3000);
}
