#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define INNER_RING_PIN         2
#define OUTER_RING_PIN         14
#define LOWER_STRIP_PIN        6
#define UPPER_STRIP_PIN        20

#define INNER_RING_PIXELS      12
#define OUTER_RING_PIXELS      24
#define LOWER_STRIP_PIXELS     72
#define UPPER_STRIP_PIXELS     72

Adafruit_NeoPixel innerRing = Adafruit_NeoPixel(INNER_RING_PIXELS, INNER_RING_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel outerRing = Adafruit_NeoPixel(OUTER_RING_PIXELS, OUTER_RING_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel lowerStrip = Adafruit_NeoPixel(LOWER_STRIP_PIXELS, LOWER_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel upperStrip = Adafruit_NeoPixel(UPPER_STRIP_PIXELS, UPPER_STRIP_PIN, NEO_GRB + NEO_KHZ800);


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
//  Serial.begin(9600);
  innerRing.begin();
  outerRing.begin();
  lowerStrip.begin();
  upperStrip.begin();

  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleControlChange(onControlChange);
  
  stripLightsOn(55,55,55);
  delay(2500);
  clearRings();
  clearStrip();
}

void loop() {
  usbMIDI.read();
}

void onNoteOn(byte channel, byte note, byte velocity) {
  if (note == 51) {
    innerLightsOn(innerRingLastRed, innerRingLastGreen, innerRingLastBlue);
  } else if (note == 46) {
    outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
  } 
  else if(note == 54) {
    stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
  }
  off = false;
  noteReceived = note;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (note == 51) {
    clearInnerLights();
  } else if (note == 46) {
    clearOuterLights();
  } else if (note == 54) {
    clearStrip();
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
      Serial.println("Inner ring red updated to");
      Serial.println(innerRingLastRed);
    } else {
        innerRingLastRed = (int)value*2;
        Serial.println("Inner ring red updated to");
        Serial.println(innerRingLastRed);
    }
  } else if (controlType == 21) {
      if(noteReceived == 51) {
        innerRingLastGreen = (int)value*2;
        innerLightsOn(innerRingLastRed, innerRingLastGreen, innerRingLastBlue);
        Serial.println("Inner ring green updated to");
        Serial.println(innerRingLastGreen);
      } else {
          innerRingLastGreen = (int)value*2;
          Serial.println("Inner ring green updated to");
          Serial.println(innerRingLastGreen);
      }
  } else if (controlType == 22) {
      if(noteReceived == 51) {
        innerRingLastBlue = (int)value*2;
        innerLightsOn(innerRingLastRed, innerRingLastGreen, innerRingLastBlue);
        Serial.println("Inner ring blue updated to");
        Serial.println(innerRingLastBlue);
      } else {
          innerRingLastBlue = (int)value*2;
          Serial.println("Inner ring blue updated to");
          Serial.println(innerRingLastBlue);
      }
      
  // **** OUTER LIGHTS ****
  
  } else if(controlType == 23) {
    if(noteReceived == 46) {
      outerRingLastRed = (int)value*2;
      outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
      Serial.println("Outer ring red updated to");
      Serial.println(outerRingLastRed);
    } else {
        outerRingLastRed = (int)value*2;
        Serial.println("Outer ring red updated to");
        Serial.println(outerRingLastRed);
    }
  } else if (controlType == 24) {
      if(noteReceived == 46) {
        outerRingLastGreen = (int)value*2;
        outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
        Serial.println("Outer ring green updated to");
        Serial.println(outerRingLastGreen);
      } else {
          outerRingLastGreen = (int)value*2;
          Serial.println("Outer ring green updated to");
          Serial.println(outerRingLastGreen);
      }
  } else if (controlType == 25) {
      if(noteReceived == 46) {
        outerRingLastBlue = (int)value*2;
        outerLightsOn(outerRingLastRed, outerRingLastGreen, outerRingLastBlue);
        Serial.println("Outer ring blue updated to");
        Serial.println(outerRingLastBlue);
      } else {
          outerRingLastBlue = (int)value*2;
          Serial.println("Outer ring blue updated to");
          Serial.println(outerRingLastBlue);
      }
  // **** STRIP LIGHTS ****    
      
  } else if(controlType == 26) {
    if(noteReceived == 54) {
      stripLastRed = (int)value*2;
      stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
      Serial.println("Strip red updated to");
      Serial.println(stripLastRed);
    } else {
        stripLastRed = (int)value*2;
        Serial.println("Strip red updated to");
        Serial.println(stripLastRed);
    }
  } else if (controlType == 27) {
      if(noteReceived == 54) {
        stripLastGreen = (int)value*2;
        stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
        Serial.println("Strip green updated to");
        Serial.println(stripLastGreen);
      } else {
          stripLastGreen = (int)value*2;
          Serial.println("Strip green updated to");
          Serial.println(stripLastGreen);
      }
  } else if (controlType == 28) {
      if(noteReceived == 54) {
        stripLastBlue = (int)value*2;
        stripLightsOn(stripLastRed, stripLastGreen, stripLastBlue);
        Serial.println("Strip blue updated to");
        Serial.println(stripLastBlue);
      } else {
          stripLastBlue = (int)value*2;
          Serial.println("Strip blue updated to");
          Serial.println(stripLastBlue);
      }
  }
}

void innerLightsOn(int red, int green, int blue) {
  
  for(int i=0;i<INNER_RING_PIXELS;i++){
    innerRing.setPixelColor(i, innerRing.Color(red, green, blue));
  }
  
  innerRing.show();
  
  ringLastRed = red;
  ringLastGreen = green;
  ringLastBlue = blue;
}
  
void outerLightsOn(int red, int green, int blue) {
 
  for(int i=0;i<OUTER_RING_PIXELS;i++){
    outerRing.setPixelColor(i, outerRing.Color(red, green, blue)); 
  }
    
  outerRing.show(); 
  
  ringLastRed = red;
  ringLastGreen = green;
  ringLastBlue = blue;
}

void ringLightsOn(int red, int green, int blue) {
  for(int i=0;i<INNER_RING_PIXELS;i++){
    innerRing.setPixelColor(i, innerRing.Color(red, green, blue));
  }
    
  for(int i=0;i<OUTER_RING_PIXELS;i++){
    outerRing.setPixelColor(i, outerRing.Color(red, green, blue)); 
  }
 
  innerRing.show(); 
  outerRing.show(); 
  
  ringLastRed = red;
  ringLastGreen = green;
  ringLastBlue = blue;
}

void stripLightsOn(int red, int green, int blue) {
  
  for(int i=0;i<LOWER_STRIP_PIXELS;i++) {
      lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue)); 
  } 

  for(int i=0;i<UPPER_STRIP_PIXELS;i++) {
      upperStrip.setPixelColor(i, upperStrip.Color(red, green, blue)); 
  } 
  
  lowerStrip.show();
  upperStrip.show();
  
  stripLastRed = red;
  stripLastGreen = green;
  stripLastBlue = blue;
  
}

void clearInnerLights() {
  
  for(int i=0;i<INNER_RING_PIXELS;i++) {
    innerRing.setPixelColor(i, innerRing.Color(0,0,0)); 
  } 
  
  innerRing.show();
  
}

void clearOuterLights() {
  
  for(int i=0;i<OUTER_RING_PIXELS;i++) {
    outerRing.setPixelColor(i, outerRing.Color(0,0,0));
  }
 
  outerRing.show(); 
  
}

void clearRings() {
  
  for(int i=0;i<INNER_RING_PIXELS;i++) {
    innerRing.setPixelColor(i, innerRing.Color(0,0,0)); 
  } 
  for(int i=0;i<OUTER_RING_PIXELS;i++) {
    outerRing.setPixelColor(i, outerRing.Color(0,0,0));
  }
 
  innerRing.show();
  outerRing.show(); 

  
}

void clearStrip() {
  for(int i=0;i<LOWER_STRIP_PIXELS;i++){
    lowerStrip.setPixelColor(i, lowerStrip.Color(0, 0, 0));
  } 
  lowerStrip.show();

    for(int i=0;i<UPPER_STRIP_PIXELS;i++){
    upperStrip.setPixelColor(i, upperStrip.Color(0, 0, 0));
  } 
  upperStrip.show();
  
}
