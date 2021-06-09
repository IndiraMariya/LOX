#include <Adafruit_CircuitPlayground.h>

uint32_t colors[] = {
  0xFF0000,   
  0xFF5500,
  0xFFFF00,
  0x00FF00,
  0x0000FF,
  0xFF00FF,
  0x000000,
  0x000000,
  0x000000,
  0x000000
};
 
int colorIndex = 0;
int startIndex = 0;
int const ROTATION_RATE = 100;
bool leftButtonPressed;
bool rightButtonPressed;
int z = 0;
int count = 0;
int timer = 0;

void colorwheel(){
  CircuitPlayground.clearPixels();
  colorIndex = startIndex;
  for (int pixel=0; pixel<10; pixel++) {
    CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
  }
  startIndex++;
  if (startIndex > 9) startIndex = 0;
}

void timeup(){
  Serial.println("Time's Up!");
  CircuitPlayground.clearPixels();
  while (z <= 10) {
    leftButtonPressed = CircuitPlayground.leftButton();
    rightButtonPressed = CircuitPlayground.rightButton();
    if (leftButtonPressed) {
      CircuitPlayground.clearPixels();
      Serial.println("Enter A Time!(Seconds)");
      break;
    } 
    if (rightButtonPressed) {
      CircuitPlayground.clearPixels();
      Serial.println("Enter A Time!(Seconds)");
      break;
    } 
    CircuitPlayground.setPixelColor(z, 0,   255,   0);
    delay(100);
    ++z;
    if (z==11){
      CircuitPlayground.clearPixels();
      z = 0;
    }
  }
}


int counter(int t){
  if (t > 0){
    Serial.println(t);
    t = t - 1;
  }
  return(t);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void setup(void) {
  
  while (!Serial);
  Serial.begin(115200);

  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(50);
  startIndex = 0;
  Serial.println("Enter A Time!(Seconds)");
}
void loop() { 
    if (Serial.available() > 0){
      String x = Serial.readString();
      timer = x.toInt();
      Serial.print("I received: ");
      Serial.println(timer, DEC);   
    } else if(timer > 0){
      colorwheel();
      ++count;
      if (count == 10) {
        timer = counter (timer);
        count= 0;
      }
      if (timer == 0){
        timeup();
      }
    }
     delay (100);

}