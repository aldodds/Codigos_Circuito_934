# Tener en cuenta
* Módulo: LCD I2C con PCF8574T
* Instalar la biblioteca `LiquidCrystal_I2C` esde el Administrador de Bibliotecas de Arduino.
* Dirección I2C: **0x27**
* La retroilumincación se enciende por medio de un puente *jumper*
* Se puede cambiar la dirección I2C del módulo configurando los terminales A0, A1 y A2 mediante puentes. Hay 8 combinaciones posibles, de 0x20 a 0x27. Por defecto, la dirección es 0x27, ya que no hay puentes y los terminales están en estado lógico alto.

# Principales métodos disponibles

* `lcd.clear()`: Limpia la pantalla.
* `lcd.setCursor(col, row)`: Posiciona el cursor en columna (col) y fila (row).
* `lcd.print("texto")`: Muestra texto en la posición actual.
* `lcd.backlight() / lcd.noBacklight()`: Controla la retroiluminación
* `lcd.blink() / lcd.noBlink()`: Activa/desactiva el parpadeo del cursor.
* `lcd.cursor() / lcd.noCursor()`: Activa/desactiva el cursor subrayado.



# Código básico

```c
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuración del LCD: Dirección I2C, Columnas, Filas
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();          // Inicializa el LCD
  lcd.backlight();     // Enciende la retroiluminación
  lcd.setCursor(0, 0); // Coloca el cursor en la posición inicial
  lcd.print("Hola Mundo!"); // Muestra un mensaje
}

void loop() {
  // Código adicional aquí
}
```
