/*
 * growlight.ino
 * Arduino code for running a led grow light
 * DavidMaitland.me 2014
 *
 */

#include <Time.h>
#include <TimeAlarms.h>

// pins
const byte lamp = 11,
           clockstatus = 13;

// settings
const int lampMax = 180,
          timeOnH = 20,
          timeOnM = 40,
          timeOffH = 7,
          timeOffM = 0,
          tick = 60;

// dynamic, do not change!
int level = 0;

void setup() {
  
  pinMode(lamp, OUTPUT);
  pinMode(clockstatus, OUTPUT);

  // Set time to start the clock here
  setTime(19,48,0,7,5,14);
  
  Alarm.alarmRepeat(timeOnH, timeOnM, 0, lampOn);
  Alarm.alarmRepeat(timeOffH, timeOffM, 0, lampOff);
  
  Alarm.timerRepeat(tick, tickLamp);

}

void lampOn() {

  // Fades led on
  for(int fadeValue = 0; fadeValue <= lampMax; fadeValue +=1) {
    analogWrite(lamp, fadeValue);
    level = fadeValue;
    Alarm.delay(1000);                            
  }

}

void lampOff() {

  // Fades led off
  for(int fadeValue = lampMax; fadeValue >= 0; fadeValue -=1) {
    analogWrite(lamp, fadeValue);
    level = fadeValue;
    Alarm.delay(1000);
  }
  
}

void tickLamp() {

  // Fade lamp up to max then back down. Just used to show the timer / led is working

  for(int fadeValue = level; fadeValue <= 255; fadeValue +=5) {
    analogWrite(lamp, fadeValue);
    Alarm.delay(20);                            
  }

  for(int fadeValue = 255; fadeValue >= level; fadeValue -=5) {
    analogWrite(lamp, fadeValue);
    Alarm.delay(20);
  }

  // Set lamp to inital state
  analogWrite(lamp, level);
  
}

void loop() {

  // Run the alarms
  Alarm.delay(100);

}
