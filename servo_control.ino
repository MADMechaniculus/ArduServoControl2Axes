#include <Wire.h>

#define SERVO_H_MAX   150
#define SERVO_H_MIN   30

#define SERVO_V_MAX   90
#define SERVO_V_MIN   40

#define ENABLE 1

#define SENSOR_US    0
#define SENSOR_IR    1
#define SENSOR_LS    2

#include <Servo.h>

Servo servo_H;
Servo servo_V;

int trigger = 8;
int echo    = 9;

int sensorType_0 = 7;
int sensorType_1 = 8;

long duration = 0, mm = 0;
int sensor   = SENSOR_US;

boolean first_start = true;

void setup() {
  Serial.begin(9600);
  
  servo_H.attach(5);
  servo_V.attach(3);
  
  pinMode(trigger,  OUTPUT);
  pinMode(echo,     INPUT);
  
  pinMode(sensorType_0, INPUT);
  pinMode(sensorType_1, INPUT);
}

void loop(){
  
  if (first_start)
  {
  //Определение типа датчика
  if (digitalRead(sensorType_0) == LOW && digitalRead(sensorType_1) == LOW)
    sensor = SENSOR_US;
  if (digitalRead(sensorType_0) == LOW && digitalRead(sensorType_1) == HIGH)
    sensor = SENSOR_IR;
  if (digitalRead(sensorType_0) == HIGH && digitalRead(sensorType_1) == HIGH)
    sensor = SENSOR_LS;
   
    first_start = false;
  }
  
  //Основное тело рабочего цикла
  if (ENABLE == 1){
    for (int i = SERVO_V_MAX; i > SERVO_V_MIN; i--)
    {
      servo_V.write(i);
      for (int j = SERVO_H_MIN; j < SERVO_H_MAX; j++)
      {
        servo_H.write(j);
        
        digitalWrite(trigger, LOW);
        delayMicroseconds(2); 
        digitalWrite(trigger, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(trigger, LOW);
        
        duration = pulseIn(echo, HIGH, 58000);
        
        mm = duration*10 / 58;
        
        Serial.write(mm);
        
        mm = 0;
        duration = 0;
      }
      servo_H.write(SERVO_H_MIN);
    }
  }
}
