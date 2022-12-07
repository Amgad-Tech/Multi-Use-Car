#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Servo x,y,z; 
int i;
#define speedL 24
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define speedR 25
#define sensorL 26
#define sensorR 27
#define trig 8
#define echo 9
char Reading;
int d1=0;
int d2=0;
Servo servo;
long duration,distance;
int button=16;
int mode=0;
int counter=0;
char b=17;
char a=18;
char f=19;
char g=20;
char e=21;
char d=22;
char c=23;
int pot=A0;
int sl=0;
int sr=0;
void setup() 
{
lcd.init();
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
Serial.begin (9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(echo, INPUT);
pinMode(trig,OUTPUT);
pinMode(speedL,OUTPUT);
pinMode(speedR,OUTPUT);
servo.attach(11);
servo.write(90);
x.attach(12);
y.attach(13);
z.attach(14);
x.write(45);
y.write(0);
z.write(0);
pinMode(a, OUTPUT );
pinMode(b, OUTPUT );
pinMode(c, OUTPUT);
pinMode(d, OUTPUT );
pinMode(e, OUTPUT );
pinMode(f, OUTPUT);
pinMode(g, OUTPUT);
pinMode(sensorR, INPUT);
pinMode(sensorL, INPUT);
pinMode(button,INPUT);
}

void Ultrasonic(){
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance = (duration/2) * 0.0343;
}
void forword()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void backword(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void left(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void right()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
void stopp(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
void zero()
{
                digitalWrite(a, 1);

                digitalWrite(b, 1);

                digitalWrite(c, 1);

                digitalWrite(d, 1);

                digitalWrite(e, 1);

                digitalWrite(f, 1);

                digitalWrite(g, 0);}
void one()
{
                digitalWrite(a, 0);

                digitalWrite(b, 1);

                digitalWrite(c, 1);

                digitalWrite(d, 0);

                digitalWrite(e, 0);

                digitalWrite(f, 0);

                digitalWrite(g, 0);}
void two()
{
                digitalWrite(a, 1);

                digitalWrite(b, 1);

                digitalWrite(c, 0);

                digitalWrite(d, 1);

                digitalWrite(e, 1);

                digitalWrite(f, 0);

                digitalWrite(g, 1);}
void three() 
{
                digitalWrite(a, 1);

                digitalWrite(b, 1);

                digitalWrite(c, 1);

                digitalWrite(d, 1);

                digitalWrite(e, 0);

                digitalWrite(f, 0);

                digitalWrite(g, 1);}


void loop(){counter++;
  if(digitalRead(button)==HIGH)
         {
         zero();
         mode=0;
          lcd.print("Line.Follower car ");
         delay(250);
         }
  while(mode==0)
  {
    sl=digitalRead(sensorL);
sr=digitalRead(sensorR);
if (sl==0&&sr==0)
forword();
else if (sl==0 &&sr==1)
right();
else if (sl==1 &&sr==0)
left();
else if (sl==1 &&sr==1)
stopp();
i=analogRead(A0);
for(i=0;i<=80;i++){
  analogWrite(speedL,i);
  analogWrite(speedR,i);
}
for(i=80;i>=0;i--){
  analogWrite(speedL,i);
  analogWrite(speedR,i);
}
}
  if(digitalRead(button)==HIGH)
         { 
  one();
  mode=1;
   lcd.print("Ultrasonic Car");
  delay(250);
  }

  
while(mode==1)
{
Ultrasonic();
if(distance<20){
stopp();
servo.write(0);
d1=digitalRead(distance);//save the value
servo.write(180);
d2=digitalRead(distance);//save the vlaue
    if (d1 >= d2){
      right();
      stopp();
    }
    else if(d2 >= d1){
      left();
      stopp();
    }
  }
  else{
    forword(); 
  
}
} 
if(digitalRead(button)==HIGH)
  {
  two();
  mode=2;
   lcd.print("Bluetooth Car");
  delay(250);
  }
while(mode=2)
{
if(Serial.available()>0){
Reading=Serial.read();
switch(Reading)
{
case'F' : forword();break;
case'B' : backword();break;
case'X' : right();break;
case'Y' : left();break;
case'S' : stopp();break; 
}
}
}
if(digitalRead(button)==HIGH)
  {
    three();
  mode=3;
   lcd.print("Robot Arm");
  delay(250);
  }
while(mode=3){
if(Serial.available()>0) {
}
Reading=Serial.read();
switch(Reading){
case 'U':for(i=45;i<180;i++){
  x.write(i); 
}
break;
case 'D': for(i=180;i>0;i--){
  x.write(i);
}
break;
case 'R':for(i=0;i<180;i++){
  y.write(i); 
}
break;
case 'L': for(i=180;i>0;i--){
  y.write(i);
}
break;
case 'A':for(i=0;i<90;i++){
  z.write(i); 
}
break;
case 'B': for(i=90;i>0;i--){
  z.write(i);
}
break;
}
} 
  if(digitalRead(button)==HIGH)
         {
         three();
         mode=0;
          lcd.print("Line.Follower car ");
         delay(250);
         }
}
