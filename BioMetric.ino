
/*
  Biometric Attendance system Draft
  Date 08-04-2023
  Processor : Arduino UNO
*/

// define io

#define BUZZER 6
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define TOUCH 8

#include <EEPROM.h>
#include "i2c.h"

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address

#include <Wire.h>

#include "RTClib.h"
RTC_DS1307 RTC;

int Keypress1 = 0;                  // KeyPress Values from A0
int Keypress2 = 0;                  // KeyPress Values from A1
int Keypress3 = 0;                  // KeyPress Values from A2
int Keypress4 = 0;                  // KeyPress Values from A3


void setup ()
{

  // configure Arduino port bits 
  pinMode(BUZZER, OUTPUT);                 // Output for Buzzer
  pinMode(S1, INPUT_PULLUP);               // Key S1
  pinMode(S2, INPUT_PULLUP);               // Key S2
  pinMode(S3, INPUT_PULLUP);               // Key S3
  pinMode(S4, INPUT_PULLUP);               // Key S4
  pinMode(TOUCH, INPUT);                   // FP Touch Active Low
  
  // set initial Output states
  digitalWrite(BUZZER, LOW); 

    Serial.begin(9600);
    Wire.begin();
    RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
//    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  // initialize the LCD, 
   lcd.init();
   
   // Turn on the blacklight and print a message.
   lcd.backlight();
   lcd.clear();

   analogWrite(BUZZER, 128);   // Sound buzzer PowerOn
   delay(500);
   analogWrite(BUZZER, LOW);

   lcd.setCursor (0,0);                 //set cursor to Col,Row
   lcd.print("   BIOMETRIC    "); 
   lcd.setCursor (0,1);                 //set cursor to Col,Row
   lcd.print("ATENDANCE SYSTEM"); 
   delay(2000);                           // to change later

}

void loop()
{
myTerminal();
DisplayTime();
//delay(2000);                           // to change later

if(digitalRead(S1)==0){
   
    Serial.println(digitalRead(S1));

    lcd.clear();
 

   lcd.setCursor (0,0);                 //set cursor to Col,Row
   lcd.print(digitalRead(S1));
    delay(2000);

  }
}


void myTerminal()                           // send data to terrminal
{
    DateTime now = RTC.now(); 
    Serial.println(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); 

    Serial.println("");                    // Print empty line
 }

 void DisplayTime()
{
       lcd.setCursor (0,0);                 //set cursor to Col,Row
       DateTime now = RTC.now(); 
       lcd.clear();
       lcd.setCursor (0,0);                 //set cursor to Col,Row
       if (now.day() < 10)
        {
          lcd.print('0');
        }
       lcd.print(now.day(), DEC);
       lcd.print('/');
       if (now.month() < 10)
        {
          lcd.print('0');
        }
       lcd.print(now.month(), DEC);
       lcd.print('/');
       lcd.print(now.year(), DEC);
       lcd.print(" ");                   
       if (now.hour() < 10)
        {
          lcd.print('0');
        }
       lcd.print(now.hour(), DEC);
       lcd.print(':');
       if (now.minute() < 10)
        {
          lcd.print('0');
        }
       lcd.print(now.minute(), DEC);
}
