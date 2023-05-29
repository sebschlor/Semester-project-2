/*
used red 5mm LED diode and 390 ohm resistor ;)
*/

#include <avr/sleep.h> //inculde sleep.h library built in in Arduino IDE to enalble sleep modes
  
#define pinLED 14 //define pin for LED as digita pin 14, or analog pin 0

void setup() {
  // put your setup code here, to run once:
   set_sleep_mode(SLEEP_MODE_PWR_SAVE); //setting sleep mode to 'power save' sleep mode, for test2 (because this is the sleep mode we're using)
   //set_sleep_mode(SLEEP_MODE_PWR_DOWN); //setting sleep mode to 'power down' sleep mode (uses the least voltage and current), for test1, 
   digitalWrite(pinLED, OUTPUT); //setting pin 14 as output pin
   digitalWrite(pinLED, LOW); //setting pin 14 to low, led is off when the program starts 
   
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinLED, HIGH); //led turns on
  delay(8000); //led stays on for around 8 seconds
  going_sleep(); //calling going_sleep function
  digitalWrite(pinLED, HIGH); //just another attempt to turn led on in case sleep mode doesn't work
}

//going_sleep function
void going_sleep(){

  digitalWrite(pinLED, LOW); //setting pin 14 to low, turning led off
  sleep_enable(); //enabling sleep mode
  sleep_mode(); //exectuting sleep mode, after exectuing this line arduino is asleep
  delay(1000); //little delay of 1 second
  digitalWrite(pinLED, HIGH); 
  //if the sleep mode doesn't work led turns on (by setting pin 14 to high) 1 second after executing "sleep_mode();"
}
