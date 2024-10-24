#include <SPI.h> //Libreria para LoRa
#include <LoRa.h> //Libreria para LoRa

#include <Wire.h> //Libreria para la pantalla LCD I2C
#include <LiquidCrystal_I2C.h> //Libreria para la pantalla LCD I2C

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C (0x27 puede variar según el módulo)

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa transmisor");

  if (!LoRa.begin(433E6)) { //Frecuencia para Colombia
    Serial.println("Error al iniciar LoRa!");
    while (1);
  }

  lcd.init();                      // Inicializa la pantalla LCD
  lcd.backlight();                  // Enciende la luz de fondo
  lcd.setCursor(0, 0);              // Establece el cursor en la primera fila, primera columna
  lcd.print("Iniciando...");           // Muestra el texto "Iniciando"
  delay(5000);                      // Espera  segundos
  lcd.clear();                      // Limpia la pantalla
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

  //Mensaje LCD
  lcd.setCursor(0, 0); 
  lcd.print("Enviando paquete");

  lcd.setCursor(0, 1); 
  lcd.print(counter);
           
  delay(3000);
}
