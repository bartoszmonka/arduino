#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"
#include <OneWire.h>                         //dodaj biblitekę OneWire.h
#include <DallasTemperature.h>               //dodaj biblitekę DallasTemperature.h
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
 tmElements_t tm;
#define DHTPIN 13  
#define DHTTYPE DHT22   // DHT 22 
LiquidCrystal lcd(3,4,5,6,7,8);
RTC_DS1307 rtc;

DHT dht(DHTPIN, DHTTYPE);
int przekaznik1 = 10;                        //przekaznik1 pin 10
int przekaznik2 = 11;                        //przekaznik2 pin 11
int przekaznik3 = 12; 
int przekaznik4 = 9;
int one_wire = 2;                            //Transmisja 1-Wire pini 8 

OneWire oneWire(one_wire);                   //transmisja 1-Wire na pinie 8
DallasTemperature sensors(&oneWire);         //1-Wire

void setup() {

  Serial.begin(9600);
  Wire.begin();

  rtc.begin();

  if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
  }
 
  
 sensors.begin(); 
 pinMode(przekaznik3, OUTPUT);               //przekaznik3 jako wyjście
 pinMode(przekaznik1, OUTPUT);               //przekaznik1 jako wyjście
 pinMode(przekaznik2, OUTPUT);               //przekaznik2 jako wyjście
 digitalWrite(przekaznik3, HIGH);            //stan początkowy przekaznika1 wysoki
 digitalWrite(przekaznik1, HIGH);            //stan początkowy przekaznika2 wysoki
 digitalWrite(przekaznik2, HIGH);            //stan początkowy przekaznika2 wysoki

}

void loop() {

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.println();
    delay(1000);

    sensors.requestTemperatures();     //odczyt temperatury z czujnika
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float w = sensors.getTempCByIndex(0);

 //Sterowanie modułem przekaźników        

   if(sensors.getTempCByIndex(0) >= 42)      
  {
     digitalWrite(przekaznik3, LOW);           //włącz przekaźnik1 - LED
     digitalWrite(przekaznik1, HIGH);          //wyłącz przekaźnik2 - LAMPKA GRZEWCZA
  }
 
  else if (sensors.getTempCByIndex(0) < 33)    
  { 
     
     digitalWrite(przekaznik3, HIGH);          //wyłącz przekaźnik1- LED
     digitalWrite(przekaznik1, LOW);           //włącz przekaźnik2 - LAMPKA GRZEWCZA
     
  }

 

    if (now.hour() == 10 & now.minute() == 30 & now.second() == 0)
    {
      digitalWrite(przekaznik2, LOW);
    }

    else if (now.hour() == 18 & now.minute() == 00 & now.second() == 0)
    {
      digitalWrite(przekaznik2, HIGH);
    }


}
