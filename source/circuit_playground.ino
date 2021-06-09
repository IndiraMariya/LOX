#include <Adafruit_CircuitPlayground.h>\
#define ROTATION_RATE   100

bool leftButtonPressed;
bool rightButtonPressed;
int z = 0;
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

void setup(void) {
  
  while (!Serial);
  Serial.begin(115200);

  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(50);
  startIndex = 0;
}
  void loop() {
    Serial.println("Enter A Time!(Seconds)"); 
    if (Serial.available() > 0){
      String x = Serial.readString();
      int t = x.toInt();
      Serial.print("I received: ");
      Serial.println(t, DEC);   
      
      while (t > 0){
        #define ROTATION_RATE   100
        Serial.println(t);
        t = t - 1;
        delay(1000);
        CircuitPlayground.clearPixels();

        colorIndex = startIndex;
        for (int pixel=0; pixel<10; pixel++) {
            CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
            colorIndex++;
            if (colorIndex > 9) colorIndex = 0;
          }
        startIndex++;
        if (startIndex > 9) startIndex = 0;
          delay(ROTATION_RATE);
         }
  Serial.println("Time's Up!");
  CircuitPlayground.clearPixels();
  
  
  while (z <= 10) {
    leftButtonPressed = CircuitPlayground.leftButton();
    rightButtonPressed = CircuitPlayground.rightButton();
    if (leftButtonPressed) {
      CircuitPlayground.clearPixels();
      break;
    } 
    if (rightButtonPressed) {
      CircuitPlayground.clearPixels();
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
}