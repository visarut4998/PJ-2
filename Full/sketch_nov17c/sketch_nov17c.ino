#include <ESP8266WiFi.h>
#include <MicroGear.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

const char* ssid     = "iPhone Visarut";
const char* password = "1234567890";

#define APPID   "CraftBeer"
#define KEY     "wkPwHAri2JGZEXu"
#define SECRET  "mteucFErHDt2UtXqBKLiBrrgr" 

#define ALIAS   "Beer01"
#define FEEDID  "CraftBeer"
#define APIKEY  "Yaf6vpSzVepHU8T7CPoSRt1EALSthGsc"

WiFiClient client;


Adafruit_BME280 bme;
int timer = 0;
char alh[32] , tmp1[32] ,pre[32] ,hum[32] , cel[32] , fha[32];

float Celsius = 0;
float Fahrenheit = 0;
const int analogInPin = A0;
int ALH = 0;
float TEMP1 = 0 , PRE = 0 , HUM = 0 ;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message -->");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup(){

    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);
    
    bool status;
    
    Serial.begin(115200);
    Serial.println("Starting...");
    status = bme.begin();
    
    if (WiFi.begin(ssid, password)) {
   while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
}

void loop(){
    if (microgear.connected()) {
        //Serial.println("connected");
        microgear.loop();

        if (timer >= 1000) {

            ALH = analogRead(analogInPin)/10;
            Serial.print("sensor = ");
            Serial.println(ALH);
            sprintf(alh,"%d",ALH); //Alcohol

            TEMP1 = bme.readTemperature();
            Serial.print("Temperature = ");
            Serial.print(TEMP1);
            //Serial.print(bme.readTemperature());
            Serial.println(" *C"); 
            sprintf(tmp1,"%.2f",TEMP1); //temp

            PRE = bme.readPressure()/1000.0F;
            Serial.print("Pressure = ");
            Serial.print(PRE);
            //Serial.print(bme.readPressure() / 100.0F);
            Serial.println(" KPa"); 
            sprintf(pre,"%.2f",PRE); //แรงดัน

            HUM = bme.readHumidity();
            Serial.print("Humidity = ");
            Serial.print(HUM);
            //Serial.print(bme.readHumidity());
            Serial.println(" %");
            sprintf(hum,"%.2f",HUM); //ความชื้น
            
            sensors.requestTemperatures();
            Celsius = sensors.getTempCByIndex(0);
            Fahrenheit = sensors.toFahrenheit(Celsius);
            Serial.print(Celsius);
            Serial.print(" C  ");
            Serial.print(Fahrenheit);
            Serial.println(" F"); 
            sprintf(cel,"%.2f",Celsius); //temp water
            sprintf(fha,"%.2f",Fahrenheit); //temp water
            
            String datafeed = "{\"Alcohol\":" + (String)ALH + 
                              ",\"TEMP1\":" + (String)TEMP1 + 
                              ",\"Pressure\":" + (String)PRE +
                              ",\"Humidity\":" + (String)HUM + 
                              ",\"TEMP2\":" + (String)Celsius +
                              ",\"TEMP3\":" + (String)Fahrenheit + "}";

            microgear.writeFeed(FEEDID,datafeed);
            
            microgear.publish("/alh",alh);
            microgear.publish("/tmp1",tmp1);
            microgear.publish("/pre",pre);
            microgear.publish("/hum",hum);
            microgear.publish("/cel",cel);
            microgear.publish("/fha",fha);

            timer = 0;
        } 
else timer += 100;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
