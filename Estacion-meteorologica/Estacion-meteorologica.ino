//Este codigo es para la estacion meteorologica WS3 de DFRobot 
// V2.0

char databuffer[35];
unsigned long lastUpdate = 0;
const unsigned long interval = 3000; // Intervalo configurable en milisegundos

void getBuffer() {
  int index = 0;
  while (index < 35) {
    if (Serial.available()) {
      char c = Serial.read();
      if (index == 0 && c != 'c') continue; // Asegurar inicio correcto
      databuffer[index++] = c;
    }
  }
}

int parseInt(char *buffer, int start, int stop) {
  int result = 0;
  for (int i = start; i <= stop; i++) {
    result = result * 10 + (buffer[i] - '0');
  }
  return result;
}

float parseTemp(char *buffer) {
  int value = (buffer[13] == '-') 
              ? -((buffer[14] - '0') * 10 + (buffer[15] - '0')) 
              : ((buffer[13] - '0') * 100 + (buffer[14] - '0') * 10 + (buffer[15] - '0'));
  return (value - 32) * 5.0 / 9.0;
}

void printData() {
  Serial.print("Wind Direction: "); Serial.println(parseInt(databuffer, 1, 3));
  Serial.print("Average Wind Speed (1 min): "); Serial.print(parseInt(databuffer, 5, 7) * 0.44704); Serial.println(" m/s");
  Serial.print("Max Wind Speed (5 min): "); Serial.print(parseInt(databuffer, 9, 11) * 0.44704); Serial.println(" m/s");
  Serial.print("Rainfall (1 hour): "); Serial.print(parseInt(databuffer, 17, 19) * 0.254); Serial.println(" mm");
  Serial.print("Rainfall (24 hours): "); Serial.print(parseInt(databuffer, 21, 23) * 0.254); Serial.println(" mm");
  Serial.print("Temperature: "); Serial.print(parseTemp(databuffer)); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(parseInt(databuffer, 25, 26)); Serial.println(" %");
  Serial.print("Barometric Pressure: "); Serial.print(parseInt(databuffer, 28, 32) / 10.0); Serial.println(" hPa");
  Serial.println();
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= interval) {
    lastUpdate = currentTime;
    getBuffer();
    printData();
  }
}
