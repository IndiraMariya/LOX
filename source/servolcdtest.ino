#include <LiquidCrystal.h>
#include<Servo.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo Myservo1;
Servo Myservo2;

int pos = 10;

int VRx = A0;
int VRy = A1;
int SW = 7;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

void servomove(){
  for(pos=10;pos<=170;pos += 10){
    Myservo1.write(pos);
    Myservo2.write(pos);
    delay(1000);
    //Serial.println(pos);
  }
  delay(10);
  
  for(pos=170;pos>=10;pos -= 10){
    Myservo1.write(pos);
    Myservo2.write(pos);
    delay(1000);
    //Serial.println(pos);
  }
  delay(10);
}

void joystickread(){
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  delay(100);
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  Myservo1.attach(9);
  Myservo2.attach(8);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  //joystickread();
  //servomove();
  //Myservo1.write(170);
  Myservo1.write(30);
  delay(500);
  Myservo2.write(150);
  delay(100);
}