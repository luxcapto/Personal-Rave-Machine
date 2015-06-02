#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define LOWER_STRIP_PIN        6
#define UPPER_STRIP_PIN        20

#define LOWER_STRIP_PIXELS     72
#define UPPER_STRIP_PIXELS     72

Adafruit_NeoPixel lowerStrip = Adafruit_NeoPixel(LOWER_STRIP_PIXELS, LOWER_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel upperStrip = Adafruit_NeoPixel(UPPER_STRIP_PIXELS, UPPER_STRIP_PIN, NEO_GRB + NEO_KHZ800);

int lowerStripRed = 0;
int lowerStripBlue = 0;
int lowerStripGreen = 0;
int upperStripRed = 0;
int upperStripBlue = 0;
int upperStripGreen = 0;

byte noteReceived = 0;
byte noteOffReceived = 0;
bool off = false;

void setup() {
//  Serial.begin(9600);
  innerRing.begin();
  outerRing.begin();
  lowerStrip.begin();
  upperStrip.begin();

  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleControlChange(onControlChange);

  lowerStripOn(55,55,55);
  delay(2500);
  clearStrips();
}

void loop() {
  usbMIDI.read();
}

void onNoteOn(byte channel, byte note, byte velocity) {
  if (note == 54) {
    lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
  } else if (note == 46) {
    upperStripOn(upperStripRed, upperStripGreen, upperStripBlue);
  } 
  off = false;
  noteReceived = note;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (note == 54) {
    clearLowerStrip();
  } else if (note == 46) {
    clearUpperStrip();
  }
  off = true;
  noteOffReceived = note;
}

void onControlChange(byte channel, byte controlType, byte value) {
  
  // **** INNER LIGHTS ****
  
  if(controlType == 20) {
    if(noteReceived == 51) {
      innerRingLastRed = (int)value*2;
      innerLightsOn(innerRingLastRed, innerRingLastGreen, innerRingLastBlue);
    } else {
        innerRingLastRed = (int)value*2;
    }
  } else if (controlType == 21) {
      if(noteReceived == 51) {
        innerRingLastGreen = (int)value*2;
        innerLightsOn(innerRingLastRed, innerRingLastGreen, innerRingLastBlue);
      } else {
          innerRingLastGreen = (int)value*2;
      }
  } else if (controlType == 22) {
      if(noteReceived == 51) {
        innerRingLastBlue = (int)value*2;
        innerLightsOn(innerRingLastRed, innerRingLastGreen, innerRingLastBlue);
      } else {
          innerRingLastBlue = (int)value*2;
      }
      
  // **** OUTER LIGHTS ****
  
  } else if(controlType == 23) {
    if(noteReceived == 46) {
      outerRingLastRed = (int)value*2;
      outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
    } else {
        outerRingLastRed = (int)value*2;
    }
  } else if (controlType == 24) {
      if(noteReceived == 46) {
        outerRingLastGreen = (int)value*2;
        outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
      } else {
          outerRingLastGreen = (int)value*2;
      }
  } else if (controlType == 25) {
      if(noteReceived == 46) {
        outerRingLastBlue = (int)value*2;
        outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
      } else {
          outerRingLastBlue = (int)value*2;
      }
  // **** STRIP LIGHTS ****    
      
  } else if(controlType == 26) {
    if(noteReceived == 54) {
      lowerStripRed = (int)value*2;
      lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
    } else {
        lowerStripRed = (int)value*2;
    }
  } else if (controlType == 27) {
      if(noteReceived == 54) {
        lowerStripGreen = (int)value*2;
        lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
      } else {
          lowerStripGreen = (int)value*2;
      }
  } else if (controlType == 28) {
      if(noteReceived == 54) {
        lowerStripBlue = (int)value*2;
        lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
      } else {
          lowerStripBlue = (int)value*2;
      }
  }
}

void stripsOn(int red, green, blue) {
  lowerStripOn(red, green blue);
  upperStripOn(red, green blue);
}

void lowerStripOn(int red, int green, int blue) {
  
  for(int i=0;i<LOWER_STRIP_PIXELS;i++) {
      lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue)); 
  } 

  lowerStrip.show();
  
  lowerStripRed = red;
  lowerStripGreen = green;
  lowerStripBlue = blue;
}

void upperStripOn(int red, int green, int blue) {  

  for(int i=0;i<UPPER_STRIP_PIXELS;i++) {
      upperStrip.setPixelColor(i, upperStrip.Color(red, green, blue)); 
  } 
  
  upperStrip.show();
  
  upperStripRed = red;
  upperStripGreen = green;
  upperStripBlue = blue;
}

void clearStrips() {
  clearLowerStrip();
  clearUpperStrip();
}

void clearLowerStrip() {
  for(int i=0;i<LOWER_STRIP_PIXELS;i++){
    lowerStrip.setPixelColor(i, lowerStrip.Color(0, 0, 0));
  } 
  lowerStrip.show();
}

void clearUpperStrip() {
  for(int i=0;i<UPPER_STRIP_PIXELS;i++){
    upperStrip.setPixelColor(i, upperStrip.Color(0, 0, 0));
  } 
  upperStrip.show();
}
