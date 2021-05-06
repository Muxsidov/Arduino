#include <Servo.h>          //standard library for the servo
#include <NewPing.h>        //for the Ultrasonic sensor function library.

//L298N motor control pins
#define EN1 6
#define IN1 8
#define IN2 7

#define EN2 5
#define IN3 4
#define IN4 3

//sensor pins
#define ECHO_PIN A2
#define TRIG_PIN A3

//speed of car
#define FRW 200
#define BCK -200

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

const int fh = 500;

NewPing sonar(TRIG_PIN, ECHO_PIN, maximum_distance); //sensor function
Servo servo_motor; 

void setup(){

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  servo_motor.attach(9); //our servo pin

  servo_motor.write(25);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  int distanceForward = 0;
  delay(50);

  if (distance <= 20)
  {
    drive(0, 0);
    delay(300);
    drive(BCK, BCK);
    delay(400);
    drive(0, 0);
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft)
    {
      drive(0, FRW);
      delay(fh);
      drive(FRW, FRW);
      drive(0, 0);
    }
    else
    {
      drive(FRW, 0);
      delay(fh);
      drive(FRW, FRW);
      drive(0, 0);
    }
  }
  else
  {
    drive(FRW, FRW); 
  }
  distance = readPing();
}

int lookRight()
{  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(50);
  return distance;
}

int lookLeft()
{
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(80);
  return distance;
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void drive(int left, int right)
{
  //значение скорости может быть вычислено автоматически
  //поэтому следует убедиться, что оно лежит в допустимом диапазоне
  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);
  
  //проверяется знак первого параметра
  //и в зависимости от него задается направление левого мотора
  if(left >= 0)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }  
  
  //аналогично для правого мотора
  if(right >= 0)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  //для задания скоростей используются те же параметры,
  //но с помощью abs() берется их абсолютное значение
  analogWrite(EN2, abs(left));
  analogWrite(EN1, abs(right));

}
