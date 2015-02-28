#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
// #define PIN            12
// #define NUMPIXELS      36
// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(12, 7, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(4,5);

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
  mySerial.begin(9600);
  mySerial.write("FUCKER");
  pixels.begin(); 
  pixels2.begin(); 
}

void loop() {

  if(Serial.available() > 0) {

    incomingByte = Serial.read();    
    
    // 144, 128, 176 always status bytes
    if (incomingByte == 144){ //note on           
      noteOn = true;
      controlChange = false;                 
    }
      else if (incomingByte == 128){ //note off
        noteOn = false;
        controlChange = false; 
      }
        else if (incomingByte == 176){ //control change
          noteOn = false;
          controlChange = true; 
        }
          else if (noteOn == false && note == 0){ //
            clearLights();
            // note = incomingByte; // not useful
            // do something with this note off note
            note = 0;
            velocity = 0;
          }
            else if (noteOn == true && note == 0){ 
              // pulseLights();
              sendLights();
              note = incomingByte;
              // do something with the note
              // note = 0; //double flickers if uncommented?
              velocity = 0;
            } 
              else if (noteOn == true && note != 0){ 
                velocity = incomingByte;
                // do something with the velocity
                note = 0;
                velocity = 0;
              }
                else if(controlChange == true && controlType == 0) {
                  controlType = incomingByte;
                  // do something with the control type
                  // controlType = 0;
                  controlValue = 0;
                }
                  else if(controlChange == true && controlType != 0) {
                    controlValue = incomingByte;
                    // do something with the control value
                    green = controlValue;
                    // controlType = 0;
                    controlValue = 0;
                  }
    else{
    }    
  }
}

void clearLights() {
  for(int i=0;i<26;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }  
  for(int i=0;i<12;i++){
    pixels2.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show(); 
  pixels2.show();
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
  for(int i=0;i<26;i++){
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  for(int i=0;i<12;i++){
    pixels2.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
  pixels2.show();


}

void changeColor()
{
  red = random(0,255);
  green = random(0,255);
  blue = random(0,255);
}
