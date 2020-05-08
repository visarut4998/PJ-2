#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SDA D2
#define BME_SCL D1

Adafruit_BME280 bme;

/*void setup() {
  Serial.begin(9600);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");
  
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  Serial.println();
  delay(1000);
}*/

float temperature, humidity, pressure, altitude;
void setup() {
  Serial.begin(9600);

  bme.begin(0x76);  
  
}
void loop() {
  
 temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
 Serial.print(temperature);
 Serial.print(" *C ");
 Serial.print(humidity);
 Serial.print(" % ");
 Serial.print(pressure);
 Serial.print(" P");
 Serial.print("\n");
 delay(1000);
}
