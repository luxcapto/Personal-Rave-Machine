#include <Adafruit_NeoPixel.h>

// #define PIN            12
// #define NUMPIXELS      36
// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(12, 7, NEO_GRB + NEO_KHZ800);


byte incomingByte;

int red = 5;
int green = 0;
int blue = 5;

int delay1 = 20;
int delay2 = 750;
int delay3 = 0;
int increment = 0;
int action = 0;

boolean noteOn = false; 
boolean controlChange = false;

int note = 0;
int controlType = 0;

int velocity = 0;
int controlValue = 0;

void setup() {
  Serial.begin(115200);
  pixels.begin(); 
  pixels2.begin(); 
}

void loop() {
  if(Serial.available() > 0) {

    incomingByte = Serial.read();    
    
    if (incomingByte == 144){        
      noteOn = true;                 
    }
      else if (incomingByte == 128){    
        noteOn = false;
      }
        else if (incomingByte == 176){
          controlChange = true;
        }
          else if (controlChange == true){
            controlType = incomingByte;
            delay1 = 1000;
          }
            else if (controlType == 17){
              controlValue = incomingByte;
              increment = controlValue - '0'; 
            }
              else if (noteOn == false && note == 0){ 
                clearLights();
                note = incomingByte;
                note = 0;
                velocity = 0;
              }
                else if (noteOn == true && note == 0){ 
                  pulseLights();
                  // sendLights();
                  note=incomingByte;
                } 
                  else if (noteOn == true && note != 0){ 
                    velocity=incomingByte;
                    note=0;
                    velocity=0;
                    action=0;
                  }
    else{
    }    
  }
}

void clearLights() {
  for(int i=0;i<36;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show(); 
}

void pulseLights() {
  int loops = 0;
  while (loops < 20)
  {
    red = red + 2;
    blue = blue + 2;
    for(int i=0; i<36; i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));
      pixels2.setPixelColor(i, pixels.Color(red, green, blue));
    }
    pixels.show();
    pixels2.show();
    delay(5);
    loops++;
  }
  red = 5;
  blue = 5;
}

void sendLights() {
// changeColor();
  for(int i=0;i<36;i++){
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
}

void changeColor()
{
  red = random(0,255);
  green = random(0,255);
  blue = random(0,255);
}
