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

int lastCC = 0;

byte noteReceived = 0;
byte noteOffReceived = 0;
bool off = false;
bool cc = false;

void setup() {
 Serial.begin(9600);
  lowerStrip.begin();
  upperStrip.begin();

  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleControlChange(onControlChange);

 for(int i=0;i<LOWER_STRIP_PIXELS;i++) {
      lowerStrip.setPixelColor(i, lowerStrip.Color(255, 0, 0));
      upperStrip.setPixelColor(i, upperStrip.Color(255, 0, 0));

      delay(5);
      lowerStrip.show(); 
      upperStrip.show();
  } 
  delay(500);

  // stripsOn(55,55,55);
  // delay(250);
   clearStrips();
}

void loop() {
  usbMIDI.read();
}

void onNoteOn(byte channel, byte note, byte velocity) {
  if (note == 54) {
    panOut(lowerStripRed, lowerStripGreen, lowerStripBlue, lastCC);
  } else if (note == 46) {
    upperStripOn(upperStripRed, upperStripGreen, upperStripBlue);
  } else if (note == 55) {
    lowerStripFirst(lowerStripRed, lowerStripGreen, lowerStripBlue);
  } else if (note == 56) {
    lowerStripSecond(lowerStripRed, lowerStripGreen, lowerStripBlue);
  } else if (note == 57) {
    lowerStripThird(lowerStripRed, lowerStripGreen, lowerStripBlue);
  }
  off = false;
  noteReceived = note;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  // Serial.write("Note off received");
  if (note == 54) {
    clearLowerStrip();
  } else if (note == 46) {
    clearUpperStrip();
  } else if (note == 55) {
    clearLowerStrip();
  } else if (note == 56) {
    clearLowerStrip();
  } else if (note == 57) 
    clearLowerStrip();
  } 
  
  off = true;
  noteOffReceived = note;
}

void onControlChange(byte channel, byte controlType, byte value) {
  if(!off) {
    if(controlType == 26) {
      if(noteReceived == 54) {
        // lowerStripRed = (int)value*2;
        // lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
        panOut (lowerStripRed, lowerStripGreen, lowerStripBlue, (int)value);
        lastCC = (int)value;
      } else {
          // lowerStripRed = (int)value*2;
      }
      } else if (controlType == 22) {
        if(noteReceived == 54) {
          lowerStripRed = (int)value*2;
          lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
          Serial.println("Red changed inside 54");

        } else {
            lowerStripRed = (int)value*2;
          Serial.println("Red changed outside 54");
        }

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
    } else if(controlType == 23) {
        if(noteReceived == 46) {
          upperStripRed = (int)value*2;
          upperStripOn(upperStripRed, upperStripGreen, upperStripBlue);
        } else {
            upperStripRed = (int)value*2;
        }
    } else if (controlType == 24) {
        if(noteReceived == 46) {
          upperStripGreen = (int)value*2;
          upperStripOn(upperStripRed, upperStripGreen, upperStripBlue);
        } else {
            upperStripGreen = (int)value*2;
        }
    } else if (controlType == 25) {
        if(noteReceived == 46) {
          upperStripBlue = (int)value*2;
          upperStripOn(upperStripRed, upperStripGreen, upperStripBlue);
        } else {
            upperStripBlue = (int)value*2;
        }
    }
  }


void stripsOn(int red, int green, int blue) {
  lowerStripOn(red, green, blue);
  upperStripOn(red, green, blue);
}

void stripsOff() {
  lowerStripOn(0, 0, 0);
  upperStripOn(0, 0, 0);
  lowerStrip.show();
  upperStrip.show();
}

void panOut(int red, int green, int blue, int control) {
  //Go through the loop 'control' amount of times
  //Loop? Needs to increment and decrement at the same time
  //Two variables- the more 'control' the more LEDs light up
  //72 leds in Strip -> always minus 1 when coding
  //middle LEDs are 35+36 with -1
  //can't compare LED position with control- control needs to be relative
 
  // control = (35/127)*control;
  // Serial.write("Coverted control is " + control);
  // Serial.write("Last control is " + lastCC);


  
  if(!off) {  

    int starting = 35 - control;
    int ending = control + 36;

    if (starting < 0) {
      starting = 0;
    }

    if (ending > 71) {
      ending = 71;
    }

    //led less than needs to be 35
    //need to subtrac number off from 35

    for (int i=35;i>starting;i--) {
      lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
    }
    for (int i=36;i<ending;i++) {
      lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
    }

    lowerStrip.show();
  }
}


void lowerStripFirst(int red, int green, int blue) {
  for (int i=0;i<11;i++) {
    lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
  }

  lowerStrip.show();

  lowerStripRed = red;
  lowerStripGreen = green;
  lowerStripBlue = blue;
}

void lowerStripSecond(int red, int green, int blue) {
  for (int i=11;i<22;i++) {
    lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
  }

  lowerStrip.show();

  lowerStripRed = red;
  lowerStripGreen = green;
  lowerStripBlue = blue;
}

void lowerStripThird(int red, int green, int blue) {
  for (int i=22;i<33;i++) {
    lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
  }

  lowerStrip.show();

  lowerStripRed = red;
  lowerStripGreen = green;
  lowerStripBlue = blue;
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
