#include <SPI.h> //Libreria para LoRa 
#include <LoRa.h> //Libreria para LoRa 
 
#include <Wire.h> //Libreria para la pantalla LCD I2C 
#include <LiquidCrystal_I2C.h> //Libreria para la pantalla LCD I2C 
 
// Definir el pin del LED
#define LED_PIN 3
 
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C (0x27 puede variar según el módulo) 
 
int counter = 0; 
 
void setup() { 
  Serial.begin(9600); 
  while (!Serial); 
 
  // Configurar el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Asegurarse que el LED comience apagado
 
  Serial.println("LoRa transmisor"); 
 
  if (!LoRa.begin(433E6)) { //Frecuencia para Colombia 
    Serial.println("Error al iniciar LoRa!"); 
    while (1); 
  } 
 
  lcd.init();                      // Inicializa la pantalla LCD 
  lcd.backlight();                  // Enciende la luz de fondo 
  lcd.setCursor(0, 0);              // Establece el cursor en la primera fila, primera columna 
  lcd.print("Iniciando...");           // Muestra el texto "Iniciando" 
  delay(2000);                      // Espera  segundos 
  lcd.clear();                      // Limpia la pantalla 
} 
 
void loop() { 
  Serial.print("Enviando paquete: "); 
  Serial.println(counter); 
 
  // Encender el LED antes de enviar el paquete
  digitalWrite(LED_PIN, HIGH);
 
  // send packet 
  LoRa.beginPacket(); 
  LoRa.print("Recibido: "); 
  LoRa.print(counter); 
  LoRa.endPacket(); 
 
  counter++; 
 
  //Mensaje LCD 
  lcd.setCursor(0, 0);  
  lcd.print("Enviando paquete"); 
 
  lcd.setCursor(0, 1);  
  lcd.print(counter); 
  
  // Mantener el LED encendido por un momento y luego apagarlo
  delay(100);  // El LED permanece encendido 100ms
  digitalWrite(LED_PIN, LOW);
            
  delay(2900);  // Completar el delay total de 3000ms (3 segundos)
}