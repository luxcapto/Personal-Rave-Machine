#include <Adafruit_NeoPixel.h>

#define PIN            12
#define NUMPIXELS      36
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte incomingByte;

//RGB variables
int red = 5;
int green = 0;
int blue = 5;

//Light control variables
int delay1 = 0;
int delay2 = 750;
int delay3 = 0;
int increment = 0;

//Status Bytes
boolean noteOn = false;
boolean controlChange = false;
boolean clearStatus = false;

//Second Byte
int note = 0;
int controlFuction = 0;

//Third Byte
int velocity = 0;
int controlValue = 0;

void setup() {
  //Intialize serial/MIDI com port and NeoPixels
  Serial.begin(115200);
  pixels.begin(); 
}

void loop() {
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 144){
      noteOn = true;
    }else if (incomingByte == 128){
      noteOn = false;
    }else if (incomingByte == 176){
      controlChange = true;
    }else if (controlChange == true){
      controlFunction = incomingByte;
    }else if (controlFunction == 17){
      controlValue = incomingByte;
      increment = controlValue - '0'; 
    }else if (noteOn == false && note == 0) ){ // if we received a "note off", we wait for which note (databyte)      
      clearLights();
      note = incomingByte;
      note = 0;
      velocity = 0;
      clearStatus = true;
   }else if (noteOn == true && note == 0){ // if we received a "note on", we wait for the note (databyte)
//     note=incomingByte;
      pulseLights();
   }else if (noteOn == true && note != 0){ // ...and then the velocity
     velocity=incomingByte;
     //playNote(note, velocity);
     note=0;
     velocity=0;
     action=0;
   }else{
     //nada
   }    
    
//    if(incomingByte == 176)
//    {
//      controlChange = true;
//    }
//    if(incomingByte == 11)
//    {
//      knob1Trigger = true; 
//    }
//    if(controlChange == true && knob1Trigger == true)
//    {
//      increment = incomingByte- '0';
//    }
//    
////    else if(controlChange == true)
////    {
////      increment = Serial.read();
////      controlChange = false;
////    }
//            
//    if (incomingByte == 144) {
//      pulseLights();
//    }
//    else if(incomingByte == 128) {
//      clearLights();
//    }
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
  while (loops < 10)
  {
    red = red + 5;
    blue = blue + 5;
    for(int i=24; i<25; i++)
    {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));        
    }
    pixels.show();
    delay(20);
    loops++;
  }
  loops = 0;
  if (action == 0) {
    while (loops < 10)
    {
      red = red - 5;
      blue = blue - 5;
      for(int i=24; i<25; i++)
      {
        pixels.setPixelColor(i, pixels.Color(red, green, blue));        
      }
      pixels.show();
      
      for(int i=24; i<25; i++)
      {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));        
      }
      pixels.show();
      loops++;
    }
  }
  red = 5;
  blue = 5;
}

void changeColor()
{
  red = random(0,255);
  green = random(0,255);
  blue = random(0,255);
}
