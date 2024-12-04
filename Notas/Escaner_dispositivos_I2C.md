# Arduino IDE

Escanear y detectar todos los dispositivos conectados al bus I2C en un rango de direcciones.

Utiliza la librería `Wire.h` estándar para comunicación I2C en Arduino

## Inicialización

1. `Wire.begin()`: Inicializa la comunicación I2C
2. `Serial.begin(9600)`: Configura comunicación serial para mostrar resultados

### Algoritmo de escaneo

* Recorre direcciones de 1 a 126
* Intenta establecer transmisión en cada dirección
* Si la transmisión es exitosa (error = 0), imprime la dirección

## Métodos clave

* `Wire.beginTransmission(address)`: Inicia transmisión en una dirección
* `Wire.endTransmission()`: Finaliza transmisión y devuelve código de error

    * 0: Dispositivo encontrado
    * Otro valor: No hay dispositivo

## Consideraciones

* Solo detecta dispositivos respondiendo
* No proporciona información del dispositivo
* Útil para depuración y verificación de conexiones