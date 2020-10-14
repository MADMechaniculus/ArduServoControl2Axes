#define SERVO_H_MAX   150
#define SERVO_H_MIN   30

#define SERVO_V_MAX   90
#define SERVO_V_MIN   40

#define ENABLE 1

#include <Servo.h>

Servo servo_H;
Servo servo_V;

int trigger = 8;
int echo    = 9;

int microsec = 0;

void setup() {
  Serial.begin(9600);
  
  servo_H.attach(5);
  servo_V.attach(3);
  
  pinMode(trigger,  OUTPUT);
  pinMode(echo,     INPUT);
}

void loop(){
  if (ENABLE == 1){
    for (int i = SERVO_V_MAX; i > SERVO_V_MIN; i--)
    {
      servo_V.write(i);
      for (int j = SERVO_H_MIN; j < SERVO_H_MAX; j++)
      {
        servo_H.write(j);
        
        digitalWrite(trigger, HIGH);
        delay(7);
        digitalWrite(trigger, LOW);
        
        while(digitalRead(echo) != HIGH);
        
        while(digitalRead(echo) == HIGH)
        {
          delayMicroseconds(1);
          microsec++;
        }
        
        Serial.write(microsec);
        microsec = 0;
        
        delay(5);
      }
      servo_H.write(SERVO_H_MIN);
    }
  }
}
