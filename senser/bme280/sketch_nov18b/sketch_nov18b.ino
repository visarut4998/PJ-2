
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
 
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
 
//#define BME_SDA D1
//#define BME_SDL D2
 
#define SEALEVELPRESSURE_HPA (1013.25)
 
Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
 
unsigned long delayTime;
 
void setup() {
    Serial.begin(115200);
    Serial.println("BME280 test");
 
    bool status;
   
    // default settings
    status = bme.begin();
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
   
    Serial.println("-- Default Test --");
    delayTime = 1000;
 
    Serial.println();
 
    delay(100); // let sensor boot up
}
 
 
 
 
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    /*float fTemp = bme.readTemperature();
    Serial.print(fTemp);
    Serial.println(" *C");*/
   
 
    Serial.print("Pressure = ");
 
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    /*float bPress = bme.readPressure() / 100.0F / 33.8638866667;
    Serial.print(bPress);
    Serial.println(" inHg");*/
 
    //Serial.print("Approx. Altitude = ");
    //Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    //Serial.println(" m");
 
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    /*float rH = bme.readHumidity();
    Serial.print(rH);
    Serial.println(" %");*/
   
 
   /* Serial.print("Dew Point = ");
    float dPoint = fTemp - ((100-rH)/5);
    Serial.print(dPoint);
    Serial.println(" *F");
 
 
    Serial.print("Heat Index = ");
    float hIndex = 0.5 * (fTemp + 61.0 + ((fTemp-68.0)*1.2) + (rH*0.094));
    Serial.print(hIndex);
    Serial.println(" *F");*/
   
    Serial.println();

    delay(1000);
}
