#include <LiquidCrystal.h>//lcd library
#include<Servo.h>//servo library
#define SETIME 10
//LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Declare Servos
Servo Myservo1;
Servo Myservo2;

int pos = 10;//delcare servo position
int z = 0;
//joystick pins
int VRx = A0;
int VRy = A1;
int SW = 7;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
int joytime = 0;
String direct = "";

//timer variables
int ms1000 = 0;
int timer = 0;

//contorls the servos
void servomove(){
  for(pos=10;pos<=170;pos += 10){
    Myservo1.write(pos);
    Myservo2.write(pos);
    delay(10);
    //Serial.println(pos);
  }
  delay(10);
  
  for(pos=170;pos>=10;pos -= 10){
    Myservo1.write(pos);
    Myservo2.write(pos);
    delay(10);
    //Serial.println(pos);
  }
  delay(10);
}

void dirprint(){
  lcd.clear();
  lcd.print(joytime);
  lcd.setCursor(0, 1);
  lcd.print(direct);
  lcd.setCursor(0, 0);
}
//Reads and prints joystick position
void joystickread(){
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  if (mapX / 100 >= 5){
    direct = "seconds";
    joytime += 10;
    dirprint();
  }
  if (mapX / 100 <= -1){
    direct = "seconds";
    joytime -=10;
      if (joytime < 0){
        joytime = 0;
      }
    dirprint();
  }

  //Serial.println(mapX / 100);
}


//when time is up...
void timeup(){
  joytime = 0;
  Myservo1.write(150);
  Myservo2.write(30);
  delay(100);
  lcd.print("0");
  lcd.clear();
  lcd.print("Time's Up!");
  lcd.setCursor(0,1);
  lcd.print("Open the Door");
  delay(10000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Choose A Time!");
  lcd.setCursor(0,0);
  lcd.print("Welcome!");
}

void eventtime()
{  
  ++ms1000;
  if (ms1000 == 10) {
    timer = counter(timer);
    ms1000= 0;
  }
  if (timer == 0){
    timeup();
  }
}

int counter(int t){
  if (t >= 0){
    lcd.clear();
    lcd.print(t);
    lcd.setCursor(0,1);
    lcd.print("Door is closed!");
    lcd.setCursor(0,0);
    t = t - 1;
  }
  return(t);
}

void setup(void) {
  //Serial Setup
  while (!Serial);
  Serial.begin(115200);

  //LCD setup
  lcd.begin(16, 2);
  lcd.print("Welcome!");
  lcd.setCursor(0,1);
  lcd.print("Choose A Time!");
  lcd.setCursor(0,0);
  //Servo setup
  Myservo1.attach(9);
  Myservo2.attach(8);
  Myservo1.write(150);
  Myservo2.write(30);

  //Joystick Setup
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}
void loop() { 
    joystickread();
    if (SW_state==0) {
      if (joytime > 0){
          delay(1000);
          Myservo1.write(30);//closing door
          Myservo2.write(150);
          timer = joytime;
          Serial.println(timer);
      }
    }
     if (timer >0){
      eventtime();
     }
    delay (100);
}