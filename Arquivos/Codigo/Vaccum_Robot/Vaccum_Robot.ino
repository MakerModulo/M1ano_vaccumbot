#include <Ultrasonic.h>

#define sensorPin A0
int sensor = 0;
int velocidade = 0;

#define pino_echo 7
#define pino_trigger 8

int Motor_D1 = 5;   //IN1
int Motor_D2 = 6;   //IN2
int Motor2_D1 = 9;  //IN3
int Motor2_D2 = 10;  //IN4

Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup(){
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  pinMode(Motor_D1, OUTPUT);
  pinMode(Motor_D2, OUTPUT);
  pinMode(Motor2_D1, OUTPUT);
  pinMode(Motor2_D2, OUTPUT);
}

void loop(){
  sensor = analogRead(sensorPin);
  velocidade = map(sensor,0,1023,0,255);
  Serial.print("velocidade: ");
  Serial.println(velocidade);
  
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  Serial.print("Distancia sensor 1 em cm: ");
  Serial.print(cmMsec);

  if (cmMsec > 30) {
    analogWrite(Motor_D1, 0);
    analogWrite(Motor_D2, velocidade);
    analogWrite(Motor2_D1, velocidade);
    analogWrite(Motor2_D2, 0);
    Serial.println("Ambos ligados para frente");
    delay(250);
  } else {
    analogWrite(Motor_D1, velocidade);
    analogWrite(Motor_D2, 0);
    analogWrite(Motor2_D1, 0);
    analogWrite(Motor2_D2, velocidade);
    Serial.println("Ambos ligados para tras");
    delay(500);
    analogWrite(Motor_D1, velocidade);
    analogWrite(Motor_D2, 0);
    analogWrite(Motor2_D1, velocidade);
    analogWrite(Motor2_D2, 0);
    Serial.println("Ambos ligados para esquerda");
    delay(500);
  }
}
