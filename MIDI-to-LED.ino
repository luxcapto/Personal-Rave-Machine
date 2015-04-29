#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define INNER_PIN            2
#define OUTER_PIN            14
#define STRIP_PIN            6

#define INNER_PIXELS      12
#define OUTER_PIXELS      24
#define STRIP_PIXELS      144

Adafruit_NeoPixel innerPixels = Adafruit_NeoPixel(INNER_PIXELS, INNER_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel outerPixels = Adafruit_NeoPixel(OUTER_PIXELS, OUTER_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripPixels = Adafruit_NeoPixel(STRIP_PIXELS, STRIP_PIN, NEO_GRB + NEO_KHZ800);


int lastRed = 0;
int lastBlue = 0;
int lastGreen = 0;
byte noteReceived = 0;
bool off = false;

void setup() {
  Serial.begin(9600);
  innerPixels.begin();
  outerPixels.begin();
  stripPixels.begin();
  clearLights();
  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleControlChange(onControlChange);
}

void loop() {
  usbMIDI.read(1);
}

void onNoteOn(byte channel, byte note, byte velocity) {
  outerLightsOn(lastRed, lastGreen, lastBlue);
  innerLightsOn(lastRed, lastGreen, lastBlue);
  stripLightsOn(lastRed, lastGreen, lastBlue);
  off = false;
  noteReceived = note;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  clearLights();
  off = true;
}

void onControlChange(byte channel, byte controlType, byte value) {
  
  if(controlType == 20 && !off) {
    outerLightsOn((value*2), lastGreen, lastBlue);
    innerLightsOn((value*2), lastGreen, lastBlue);
    stripLightsOn((value*2), lastGreen, lastBlue);
  } else if (controlType == 20 && off) {
    lastRed = value*2;
  }
  
  else if (controlType == 21 && !off) {
      outerLightsOn(lastRed, (value*2), lastBlue);
      innerLightsOn(lastRed, (value*2), lastBlue);
      stripLightsOn(lastRed, (value*2), lastBlue);
  } else if (controlType == 21 && off) {
    lastGreen = value*2;
  }
  
  else if (controlType == 22 && !off) {
      outerLightsOn(lastRed, lastGreen, (value*2));
      innerLightsOn(lastRed, lastGreen, (value*2));
      stripLightsOn(lastRed, lastGreen, (value*2));
  } else if (controlType == 22 && off) {
    lastBlue = value*2;
  }
}

void innerLightsOn(int red, int green, int blue) {
  
  for(int i=0;i<INNER_PIXELS;i++){
    innerPixels.setPixelColor(i, innerPixels.Color(red, green, blue));
  }
  
  innerPixels.show();
  
  lastRed = red;
  lastGreen = green;
  lastBlue = blue;
}
  
void outerLightsOn(int red, int green, int blue) {
 
  for(int i=0;i<OUTER_PIXELS;i++){
    outerPixels.setPixelColor(i, outerPixels.Color(red, green, blue)); 
  }
    
  outerPixels.show(); 
  
  lastRed = red;
  lastGreen = green;
  lastBlue = blue;
}

void stripLightsOn(int red, int green, int blue) {

  if(noteReceived == 54) {
    for(int i=0;i<STRIP_PIXELS;i++) {
      stripPixels.setPixelColor(i, stripPixels.Color(red, green, blue)); 
    } 
    stripPixels.show();
  }
  
  lastRed = red;
  lastGreen = green;
  lastBlue = blue;
}

void clearLights() {
  
  for(int i=0;i<INNER_PIXELS;i++) {
    innerPixels.setPixelColor(i, innerPixels.Color(0,0,0)); 
  }  
    
  for(int i=0;i<OUTER_PIXELS;i++) {
    outerPixels.setPixelColor(i, outerPixels.Color(0,0,0));
  }
  
  for(int i=0;i<STRIP_PIXELS;i++){
    stripPixels.setPixelColor(i, stripPixels.Color(0, 0, 0));
  }
  
  innerPixels.show();
  outerPixels.show(); 
  stripPixels.show();
}
