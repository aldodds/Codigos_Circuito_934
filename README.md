# Conexiones del Arduino al módulo SX1278 Ra-01

*D* corresponde a un pin digital del Arduino UNO.

| Arduino UNO| SX1278   |
|:-----------|:--------:|
| 3.3 V      | 3.3 V    |
| GND        | GND      |
| D2         | G0/DIO0  |
| D9         | RST      |
| D10        | EN/NSS   |
| D11        | MOSI     |
| D12        | MISO     |
| D13        | SCK      |

# APN Claro Colombia

La información de la [APN de la SIM Card de Claro colombia](https://selectra.com.co/empresas/claro/celulares/apn) se establece en el código de la siguiente forma:

```C++
  // Configurar APN de Claro Colombia
  modem.gprsConnect("internet.comcel.com.co", "comcel", "comcel");
```
