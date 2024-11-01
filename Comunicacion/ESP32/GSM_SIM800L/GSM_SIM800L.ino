/*
V.1.0
Este codigo envia un mensaje de texto AT a un numero de teléfono (+573...). Comprueba el registro en la red y muestra la intensidad de la señal
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

// Configuración de Serial
#define SerialMon Serial
#define SerialAT  Serial1

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

  // Intentar enviar SMS
  SerialMon.println("Intentando enviar SMS...");
  if(modem.sendSMS(SMS_TARGET, "Porvenir")){
    SerialMon.println("SMS enviado exitosamente");
  } else {
    SerialMon.println("Error al enviar SMS");
  }
}

void loop() {
  delay(1000);
}