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


int ringLastRed = 0;
int ringLastBlue = 0;
int ringLastGreen = 0;

int innerRingLastRed = 0;
int innerRingLastBlue = 0;
int innerRingLastGreen = 0;

int outerRingLastRed = 0;
int outerRingLastBlue = 0;
int outerRingLastGreen = 0;

int stripLastRed = 0;
int stripLastBlue = 0;
int stripLastGreen = 0;

byte noteReceived = 0;
byte noteOffReceived = 0;
bool off = false;

void setup() {
  Serial.begin(9600);
  innerPixels.begin();
  outerPixels.begin();
  stripPixels.begin();
  clearRings();
  clearStrip();
  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleControlChange(onControlChange);
}

void loop() {
  usbMIDI.read(1);
}

void onNoteOn(byte channel, byte note, byte velocity) {
  // 
  if (note == 51) {
    ringLightsOn(ringLastRed, ringLastGreen, ringLastBlue);
  } else if(note == 54) {
    stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
  }
  off = false;
  noteReceived = note;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (note == 51) {
    clearRings();
  } else if (note == 54) {
    clearStrip();
  }
  off = true;
  noteOffReceived = note;
}

void onControlChange(byte channel, byte controlType, byte value) {
  
  if(controlType == 20 && !off) {
    if(noteOffReceived == 51 ) {
      ringLastRed = (int)value*2;
      ringLightsOn(ringLastRed, ringLastGreen, ringLastBlue);
      Serial.println("Ring red");
      Serial.println(ringLastRed);

    }
    if (noteOffReceived == 54) {
        stripLastRed = (int)value*2;
        stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
        Serial.println("Strip red");
        Serial.println(stripLastRed);


    }
  }
 
   if(noteOnReceived == 51 && controlType == 20 && !off) {
     
   } 
 
//  if(controlType == 21 && !off) {
//    if(noteOffReceived == 51 ) {
//      ringLastGreen = (int)value*2;
//      ringLightsOn(ringLastRed, ringLastGreen, ringLastBlue);
//      Serial.println("Ring green" + ringLastGreen);
//
//    } else if (noteOffReceived == 54) {
//        stripLastGreen = (int)value*2;
//        stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
//        Serial.println("Strip green" + stripLastGreen);
//
//    }
//  }  
// 
//  if(controlType == 22 && !off) {
//    if(noteOffReceived == 51 ) {
//      ringLastBlue = (int)value*2;
//      ringLightsOn(ringLastRed, ringLastGreen, ringLastBlue);
//      Serial.println("Ring blue" + ringLastBlue);
//
//    } else if (noteOffReceived == 54) {
//        stripLastBlue = (int)value*2;
//        stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
//        Serial.println("Strip blue" + stripLastBlue);
//    }
//  }   

//  } else if (controlType == 20 && off) {
//    ringLastRed = value*2;
//  }
  
//  else if (controlType == 21 && !off) {
//      ringLightsOn(ringLastRed, (value*2), ringLastBlue);
//      stripLightsOn(ringLastRed, (value*2), ringLastBlue);
//  } else if (controlType == 21 && off) {
//    ringLastGreen = value*2;
//  }
//  
//  else if (controlType == 22 && !off) {
//      ringLightsOn(ringLastRed, ringLastGreen, (value*2));
//      stripLightsOn(ringLastRed, ringLastGreen, (value*2));
//  } else if (controlType == 22 && off) {
//    ringLastBlue = value*2;
//  }
}

void innerLightsOn(int red, int green, int blue) {
  
  for(int i=0;i<INNER_PIXELS;i++){
    innerPixels.setPixelColor(i, innerPixels.Color(red, green, blue));
  }
  
  innerPixels.show();
  
  ringLastRed = red;
  ringLastGreen = green;
  ringLastBlue = blue;
}
  
void outerLightsOn(int red, int green, int blue) {
 
  for(int i=0;i<OUTER_PIXELS;i++){
    outerPixels.setPixelColor(i, outerPixels.Color(red, green, blue)); 
  }
    
  outerPixels.show(); 
  
  ringLastRed = red;
  ringLastGreen = green;
  ringLastBlue = blue;
}

void ringLightsOn(int red, int green, int blue) {
  for(int i=0;i<INNER_PIXELS;i++){
    innerPixels.setPixelColor(i, innerPixels.Color(red, green, blue));
  }
    
  for(int i=0;i<OUTER_PIXELS;i++){
    outerPixels.setPixelColor(i, outerPixels.Color(red, green, blue)); 
  }
 
  innerPixels.show(); 
  outerPixels.show(); 
  
  ringLastRed = red;
  ringLastGreen = green;
  ringLastBlue = blue;
}

void stripLightsOn(int red, int green, int blue) {
  
  for(int i=0;i<STRIP_PIXELS;i++) {
      stripPixels.setPixelColor(i, stripPixels.Color(red, green, blue)); 
  } 
  
  stripPixels.show();
  
  stripLastRed = red;
  stripLastGreen = green;
  stripLastBlue = blue;
  
}

void clearRings() {
  
  for(int i=0;i<INNER_PIXELS;i++) {
    innerPixels.setPixelColor(i, innerPixels.Color(0,0,0)); 
  } 
  for(int i=0;i<OUTER_PIXELS;i++) {
    outerPixels.setPixelColor(i, outerPixels.Color(0,0,0));
  }
 
  innerPixels.show();
  outerPixels.show(); 

  
}

void clearStrip() {
  for(int i=0;i<STRIP_PIXELS;i++){
    stripPixels.setPixelColor(i, stripPixels.Color(0, 0, 0));
  } 
  stripPixels.show();
  
}
