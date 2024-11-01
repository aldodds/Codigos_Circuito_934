/*
V.1.1
Este código envía un mensaje de texto "Porvenir" a un número de teléfono (+573...). Verifica la red y la intensidad de la señal, y envía el mensaje cada 30 segundos. El LED se enciende solo durante el envío exitoso.
*/

// Definir el modelo del módem ANTES de incluir TinyGSM
#define TINY_GSM_MODEM_SIM800      // Módem es SIM800
#define TINY_GSM_RX_BUFFER   1024  // Buffer RX a 1Kb

#include <TinyGsmClient.h>

// Configuración del número de teléfono
#define SMS_TARGET  "+573042102865"

// Configuración de pines TTGO T-Call
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define LED_PIN              13    // LED interno de la ESP32 GPIO13

// Configuración de Serial
#define SerialMon Serial
#define SerialAT  Serial1

// Variables de temporización
unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 30000; // 30 segundos

// Configuración del módulo SIM800
TinyGsm modem(SerialAT);

void setup() {
  // Inicializar Serial Monitor
  SerialMon.begin(115200);
  SerialMon.println("Iniciando configuración...");

  // Configurar pines del módem
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  pinMode(LED_PIN, OUTPUT);     // Configuración del LED interno
  digitalWrite(LED_PIN, LOW);   // Asegurar que el LED comience apagado

  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  SerialMon.println("Configurando módulo GSM...");
  
  // Configurar módulo GSM
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Inicializar módem
  SerialMon.println("Inicializando modem...");
  modem.restart();
  delay(10000); // Esperar 10 segundos para que el módulo se estabilice

  // Configurar APN de Claro Colombia
  modem.gprsConnect("internet.comcel.com.co", "comcel", "comcel");
  
  // Verificar si el módem responde
  SerialMon.println("Verificando módem...");
  if(!modem.testAT()) {
    SerialMon.println("Error: No hay respuesta del módem");
    return;
  }
  SerialMon.println("Módem respondiendo OK");

  // Verificar registro en la red
  SerialMon.println("Verificando registro en la red...");
  if(!modem.waitForNetwork()) {
    SerialMon.println("Error: No hay registro en la red");
    return;
  }
  SerialMon.println("Registro en red OK");

  // Verificar intensidad de señal
  int signalQuality = modem.getSignalQuality();
  SerialMon.println("Intensidad de señal: " + String(signalQuality));
}

void loop() {
  unsigned long currentTime = millis();

  // Enviar SMS cada 30 segundos
  if (currentTime - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = currentTime; // Actualizar tiempo del último envío

    // Apagar el LED al inicio del intento de envío
    digitalWrite(LED_PIN, LOW);
    
    // Intentar enviar SMS
    SerialMon.println("Intentando enviar SMS...");
    bool smsSent = modem.sendSMS(SMS_TARGET, "Porvenir");
    
    if(smsSent) {
      SerialMon.println("SMS enviado exitosamente");
      digitalWrite(LED_PIN, HIGH);  // Encender LED solo si se envió el SMS exitosamente
      delay(1000);                  // Mantener el LED encendido 1 segundo
      digitalWrite(LED_PIN, LOW);   // Apagar el LED después del envío exitoso
    } else {
      SerialMon.println("Error al enviar SMS");
    }
  }
}