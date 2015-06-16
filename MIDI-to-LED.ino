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

  // lowerStrip.show();
  // stripsOn(55,55,55);
  // delay(2500);
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
  } else if (note == 55) {
    lowerStripFirst(lowerStripRed, lowerStripGreen, lowerStripBlue);
  } else if (note == 56) {
    lowerStripSecond(lowerStripRed, lowerStripGreen, lowerStripBlue);
  }
  off = false;
  noteReceived = note;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (note == 54) {
    clearLowerStrip();
  } else if (note == 46) {
    clearUpperStrip();
  } else if (note == 55) {
    clearLowerStrip();
  } else if (note == 56) {
    clearLowerStrip();
  }
  off = true;
  noteOffReceived = note;
}

void onControlChange(byte channel, byte controlType, byte value) {
  if(controlType == 26) {
    if(noteReceived == 54) {
      lowerStripRed = (int)value*2;
      lowerStripOn(lowerStripRed, lowerStripGreen, lowerStripBlue);
      // upAndDown (lowerStripRed, lowerStripGreen, lowerStripBlue, (int)value);
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
  for (int i=12;i<23;i++) {
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
int lastCC = 0;
void upAndDown(int red, int green, int blue, int ccValue) {
  lowerStrip.setPixelColor(lastCC, lowerStrip.Color(0, 0, 0));
  lowerStrip.show();
  if(ccValue < 72)
  {
      lowerStrip.setPixelColor(ccValue, lowerStrip.Color(red, green, blue));
      lowerStrip.show();
  }
  lastCC = ccValue;

}

//change color with x axis (cc what?)
//change brightness with y axis (cc what?)

//need to write fade animation 
//correlate center led out with data from xy pad
// void lowerStripExpand(int red, int green, int blue, int ccValue) {

// //mess with delay knoh for actual expand
//   // 72 pixels (0-71)
//   // start at 36

//   // cc value 1 ->>> led 36
//   // cc value 2 ->>> led 35, 36, 37
//   // cc value 3 ->>> led 34, 34, 35, 36, 37

//   int forward = 36;
//   for(int i=36; i<(ccValue/2);i--)
//   {
//     lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
//     forward++;
//     lowerStrip.setPixelColor(forward, lowerStrip.Color(red, green, blue));
//     lowerStrip.show();
//   }  

//   int forward = 36;
//   for(int i=36; i<LOWER_STRIP_PIXELS;i++)
//   {
//     //get the cc value
//     //if cc value is withing
//     int ledPosition = i;
//     lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
//     lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue));
//     forward++;
//     lowerStrip.setPixelColor(forward, lowerStrip.Color(red, green, blue));
//     lowerStrip.show();
//   }

// }

// void lowerStripScroll(int red int green, int blue, int ccValue) {
//     for(int i=0;i<ccValue*2;i++) {
//       lowerStrip.setPixelColor(i, lowerStrip.Color(red, green, blue)); 
//   } 
  
//   lowerStrip.show();
// }

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
