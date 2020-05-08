#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4
int TIME_UNTIL_WARMUP = 900;
unsigned long time;

int analogPin = 0;
int val = 0;


void setup()   {                

}


void loop() {  
  
  delay(100);

  val = readAlcohol();
  printTitle();
  printWarming();

  time = millis()/1000;
  
  if(time<=TIME_UNTIL_WARMUP)
  {
    time = map(time, 0, TIME_UNTIL_WARMUP, 0, 100);
    display.drawRect(10, 50, 110, 10, WHITE); //Empty Bar
    display.fillRect(10, 50, time,10,WHITE);
  }else
  {
     printTitle();
     printAlcohol(val);
     printAlcoholLevel(val);  
  }
  display.display();

}

 
 int readAlcohol()
 {
  int val = 0;
  int val1;
  int val2;
  int val3; 


  display.clearDisplay();
  val1 = analogRead(analogPin); 
  delay(10);
  val2 = analogRead(analogPin); 
  delay(10);
  val3 = analogRead(analogPin);
  
  val = (val1+val2+val3)/3;
  return val;
 }
