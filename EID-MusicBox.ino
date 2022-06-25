

//***************************************************
// Code for my project in the EID Course
//
// 
// Pots on Pins: 14,15,16,17,18,19,22
//
// edoardo focante
//***************************************************
#include "DIYSynthWorkshop.h"  
#include <Bounce.h>




#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2; //xy=78,315.00000381469727
AudioSynthWaveform       waveform1;      //xy=81,251.00000381469727
AudioSynthWaveformModulated waveformMod2;   //xy=238.00000381469727,315.00000381469727
AudioSynthWaveformModulated waveformMod1;   //xy=241,258.00000381469727
AudioEffectEnvelope      envelope1;      //xy=410.00000762939453,251.00000381469727
AudioEffectEnvelope      envelope2;      //xy=414.00000762939453,312.00000381469727
AudioMixer4              mixer1;         //xy=628.0000076293945,274.00002670288086
AudioEffectFreeverbStereo freeverbs1;     //xy=759.0000114440918,112.00000190734863
AudioFilterStateVariable filter1;        //xy=759.0000114440918,211.00000190734863
AudioOutputI2S           i2s1;           //xy=905.0000152587891,116.00001335144043
AudioConnection          patchCord1(waveform2, 0, waveformMod2, 0);
AudioConnection          patchCord2(waveform1, 0, waveformMod1, 0);
AudioConnection          patchCord3(waveformMod2, envelope2);
AudioConnection          patchCord4(waveformMod1, envelope1);
AudioConnection          patchCord5(envelope1, 0, mixer1, 0);
AudioConnection          patchCord6(envelope2, 0, mixer1, 1);
AudioConnection          patchCord7(mixer1, 0, filter1, 0);
AudioConnection          patchCord8(freeverbs1, 0, i2s1, 0);
AudioConnection          patchCord9(freeverbs1, 1, i2s1, 1);
AudioConnection          patchCord10(filter1, 0, freeverbs1, 0);
// GUItool: end automatically generated code












float scale[] = {130.81,155.56,174.61,207.65,233.08,261.63}; //C3 Eb3 F Ab3 Bb3 C4 
float scale1[] = {130.81,155.56,196,233.08,261.63};

unsigned long time_now1 = 0;
unsigned long time_now2 = 0;
bool noteflag1 = false;
bool noteflag2 = false;
bool b = true;
bool c = true;
float d;
float e;
bool pitch = false;
int wf1 = 0;
int wf2 = 0;
float pitchChord = 0;
bool vcfflag = true;
float vcf = 1500;


Bounce button1 = Bounce(1, 10);
Bounce button2 = Bounce(2, 10);
Bounce button3 = Bounce(3, 10);
Bounce button4 = Bounce(4, 10);



int cyclewf(int curr){
   // cycle through waveforms given the current
    int current_waveform  = 0;
    switch (curr) {
      case WAVEFORM_SINE:
        current_waveform = WAVEFORM_SAWTOOTH;
        Serial.println("Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH:
        current_waveform = WAVEFORM_SQUARE;
        Serial.println("Reverse Sawtooth");
        break;
      case WAVEFORM_SQUARE:
        current_waveform = WAVEFORM_TRIANGLE;
        Serial.println("Triangle");
        break;
      case WAVEFORM_TRIANGLE:
        current_waveform = WAVEFORM_SINE;
        Serial.println("Variable Triangle");
        break;
     
    }
        return current_waveform;
    }

  
float randomNote(float prevNote){
  //pick a random note from global scale[]
  
  int g = random(100);
  float newNote = 0;
  do{
     newNote = scale[random(0,6)];
    }while (prevNote == newNote);
  return newNote;
  }
  
    
  

bool chance(float th) {
  // return a gate (true or false) for a certain probability
  float a = random(100);
  Serial.println((String)"prob: "+th);
  Serial.println((String)"guess: "+ a);
  return (a < th);
}

void setup() {
  // put your setup code here, to run once:
   // Setup input knobs to control the synth parameters
  setupKnobs();

  filter1.frequency(1500);
  filter1.resonance(1);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  // Setup serial communication with your laptop to print debug info
  Serial.begin(9600);
  
  AudioMemory(1500);
  wf1 = WAVEFORM_SINE;
  wf2 = WAVEFORM_SINE;
  //begin waveforms so they are triggered by the envelope
  waveformMod2.begin(wf2);
  waveformMod1.begin(wf1);
  waveform1.begin(WAVEFORM_SINE);
  waveform2.begin(WAVEFORM_SINE);
  waveformMod1.amplitude(0.8);
  waveformMod2.amplitude(0.8);
  waveform1.amplitude(0.5);
  waveform2.amplitude(0.5);
  waveform1.frequency(0);
  waveform2.frequency(0);
  
  
  envelope1.attack(20);
  envelope1.release(20);
  envelope1.sustain(0.8);
  envelope2.decay(10);
  
  envelope2.attack(20);
  envelope2.release(20);
  envelope2.sustain(0.8);
  envelope2.decay(10);
  
  freeverbs1.roomsize(0.4);
  freeverbs1.damping(0.6);
  
  
}

void loop() {
  updateKnobs();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  float vol = map(readKnob(14),0.0,1023.0,0.0,0.9);
 
  
  if (button4.fallingEdge()){
    vcfflag = !vcfflag;
    if (!vcfflag){
      pitch = true;
    }
  }
  if ((vcfflag)){
    vcf = map(readKnob(15),0.0,1023.0,200,2000);
    filter1.frequency(vcf);
    
  } 
  
  
  
  if (button3.fallingEdge()){
    pitch = !pitch;
    if (!pitch){
      vcfflag = true;
    }
  }
  
  if ((pitch) && (!vcfflag)) {
      pitchChord = map(readKnob(15),0.0,1023.0,-1,1); 
      
  }
  
  if ((!pitch)) {
    pitchChord = 0;
    
  }
  
  float dur2 = map(readKnob(16),0.0,1023.0,5,6000); //
  float prob2 = map(readKnob(17),0.0,1023.0,-1,101);
  float rate2 = map(readKnob(18),0.0,1023.0,10,400);
  float dur1 =  map(readKnob(19),0.0,1023.0,5,6000); //
  float prob1 = map(readKnob(22) ,0.0,1023.0,-1,101); //
  float rate1 = map(readKnob(23),0.0,1023.0,10,400); //
 
  if (button1.fallingEdge()){
   
      wf1 = cyclewf(wf1);
      waveformMod1.begin(wf1);
      Serial.println("Nando");
  }
  
  if (button2.fallingEdge()){
   
      wf2 = cyclewf(wf2);
      waveformMod2.begin(wf2);
  }
  
   
  
  
  mixer1.gain(0,vol);
  mixer1.gain(1,vol);
  
  float period1 = 60/rate1*1000;
  float period2 = 60/rate2*1000;
 
  
 
  
  
  if ((millis()-time_now1 > period1)) {
  b = chance(prob1);
 
  time_now1 = millis();
    if (b){
      count = count+1;
    
      d = randomNote(d);
      waveformMod1.frequency(2*d);
      
      if (!noteflag1) {
      envelope1.noteOn();
      }
      
      noteflag1 = true;
      
    }
  }
 
  

    if ((millis()-time_now2 > period2)) {
    c = chance(prob2);
   
    time_now2 = millis();
    if (c){

      e = randomNote(e);
      
      waveformMod2.frequency(2*e+(e*pitchChord));
      if (!noteflag2) {
      envelope2.noteOn();
      }
      noteflag2 = true;
      
     
   
    }
    
    }
  
 
  
  if ((noteflag2) && (millis()-time_now2 > dur2 )){
    
   
   envelope2.noteOff();
   noteflag2 = false;
  }
  
  
  if ((noteflag1) && (millis()-time_now1 > dur1 )){
    
   envelope1.noteOff();
   noteflag1 =  false;

  }

  delay(5);

}
