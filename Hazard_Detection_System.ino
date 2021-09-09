/*  Hazard Detection System Prototype sketch

 * This sketch integrates the HC-SR04 Ultrasonic Distance Sensor,
 * LCD, 12C Adapter and Arduino Uno into an IoT system that detects
 * danger and prevents accidents.
 *                                   
 *                                   -originally written by Chika Dueke-Eze.   

 * 

 * Components

 * ----------

 *  - Arduino Uno

 *  - 12C Adaptor (or equivalant)
 *  
 *  - Breadboards
 *  
 *  - LEDs
 *  
 *  - HC-SR04 Ultrasonic Distance Sensor
 *  
 *  - Jumper cables

 *  Libraries

 *  ---------

 *  - Liquid Crystal Library


 * Connections
 

 * -----------

 *  HC-SR04 UDS   |    Arduino Uno            

 *  -----------------------------

 *      Echo      |      12

 *      GND       |      GND

 *      Trig      |      13

 *       VCC      |      5V


 
  12C Adaptor     |    Arduino Uno

 *  -----------------------------

 *     SDA        |      A4

 *      GND       |      GND

 *      SCL       |      A5

 *       VCC      |      5V


* Piezo buzzers and LEDs follow the normal simple configuration to GND and Digital pin.

 * Other information

 * -----------------


 *  HC-SR04 Ultrasonic Distance Sensor datasheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
 *  Piezo Buzzer datasheet: https://www.sparkfun.com/datasheets/Sensors/Flex/p37e.pdf
 *  16 x 2 LCD datasheet: https://www.sparkfun.com/datasheets/LCD/ADM1602K-NSW-FBS-3.3v.pdf
 *  LEDs datasheet: https://cdn-shop.adafruit.com/datasheets/IR333_A_datasheet.pdf
 *  
 *  Adafruit product page: https://www.adafruit.com/product/1782

 *  For more information on the Liquid Crystal Library: https://github.com/arduino-libraries/LiquidCrystal

 *  

 *  Created on September 10,2019 by Chika Dueke-Eze 

 * 

*/

const int buzzer = 8; 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define trigPin 13
#define echoPin 12 

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  
  pinMode (echoPin, INPUT);
  
  pinMode(buzzer, OUTPUT);
  
  pinMode(5, OUTPUT);
  
  pinMode(6, OUTPUT);
  
  pinMode(7, OUTPUT);
  
  }

void loop() {
  // put your main code here, to run repeatedly:
    long duration, distance;
  digitalWrite(trigPin, LOW);
  
  delay(2);
  
  digitalWrite(trigPin, HIGH);
  
  delay(10);
  
  digitalWrite(trigPin, LOW);
  
  duration= pulseIn(echoPin, HIGH);
  
  distance=(duration/2)/29.1;  /*This equation is used to accurately determine
                                 distance by using the time taken for waves to 
                                 bounce from the transducer to the responder
                               */
   if(distance<=150){
   lcd.setCursor (0,0);
   
   lcd.print("DANGER AHEAD!");      /*This is used to transmit a signal to the LCD
                                     to print a text once it detects that someone has
                                     encroached upon the specified 'Danger Zone'
    
                                    */
   lcd.setCursor (0,1);             
   
   lcd.print("PLEASE STAY BACK");  // 
   
   tone(buzzer, 3000);
   
   digitalWrite(7, HIGH);
   
   delay(250);
   
   digitalWrite(7, LOW);
   
   digitalWrite(6, HIGH);
   
   delay(250);
   
   digitalWrite(6, LOW);
   
   digitalWrite(5, HIGH);
   
   delay(250) ;
  
   digitalWrite(5, LOW);
   
  lcd.clear();
  return;
  delay(1000);
   
   }
   
   else{
   lcd.setCursor (0,0);
   lcd.print("SAFE ZONE"); /*Default state when the Ultrasonic Distance Sensor
                             fails to detect anyone within the danger zone.
    
                           */
   noTone(8);
    delay(1000);
   }
   delay(1000);
   lcd.clear()
   ;
  
}
