#define EN1 6
#define IN1 8
#define IN2 7

#define EN2 5
#define IN3 4
#define IN4 3

#define LEFT_SENSOR_PIN A0
#define RIGHT_SENSOR_PIN A1 

//создаются читаемые определения
//для вызова функции чтения датчиков линии
#define LEFT 1
#define RIGHT 0

//определяется граница между черным и белым
#define BLACK 100

//константами задаются два варианта скоростей
#define FRW 140
#define BCK 0

void setup() {
  // put your setup code here, to run once:
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.println(analogRead(A0));
  
  //возможные сочетания цветов поля под датчиками
  //описано серией условий с использованием lineSensor(),
  //которая возвращает логическое значение, соответствующее черному или белому
  if(lineSensor(LEFT) && lineSensor(RIGHT))
  //в зависимости от сочетания цветов под датчиками
  //задается сочетание скоростей левого и правого колес
    drive(FRW,FRW);
  else if(lineSensor(LEFT) && !lineSensor(RIGHT))
    drive(FRW,BCK);
  else if(!lineSensor(LEFT) && lineSensor(RIGHT))
    drive(BCK,FRW);
  else   
    drive(0,0);
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

boolean lineSensor(int sensor)
{
  //в зависимости от того, какой датчик был запрошен
  //проверяется либо левый, либо правый датчик
  if(sensor == LEFT)
  {
     //в зависимости от того, превосходит ли значение,
     //полученное на датчике, пороговое значение
     //возвращается истина или ложь, т.е. "белое" или "черное"
     if(analogRead(LEFT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
  else if(sensor == RIGHT)
  {
     if(analogRead(RIGHT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
}
