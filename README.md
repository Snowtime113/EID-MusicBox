
# EID-MusicBox
Project for the Experimental Instrument Design Course @X

Designed for Teensy 4.0

The project aims to create a probabilistic Music Box, with two oscillators gated by an envelope generator. The envelope is trigger by a bernoulli gate, which plays the note according to a certain probability. This is implemented by a random guess at each clock tick. The probability can be controlled by knobs, as well as the clock rate. The controls are separated for each oscillator, as they are meant to be played as separate instruments in a collaborative environment. One can be used as based while the other can be used to generate a random melody on top, or they can be made to duet with each other. 

The notes are picked from a hard-coded scale which can be changed by manually writing down frequencies in the scale array [].
Modulation of the oscillators is included, but not implemented yet due to limited time and lack of knobs.

The Teensy Audio schematic can be found below.

![chrome_VJyW3RIddv](https://user-images.githubusercontent.com/55795025/175766335-1bd99442-58da-45e0-9e57-128e46fa9bba.png)


Pin Map:

Analog:

14 -> Master Volume  
15 -> Filter Cutoff / 2nd Oscillator Pitch (+- 1 oct)
16 -> Sustain 2nd Oscillator
17 -> Gate Probability 2nd Oscillator
18 -> Rate 2nd Oscillator
19 -> Sustain 1st Oscillator
20 -> LCK DAC
21 -> BCK DAC
22 -> Gate Probability 1st Oscillator
23 -> Rate 1st Oscillator

Digital:

1 -> Waveform Change Osc 1
2 -> Waveform Change Osc 1
3 -> Toggle Pitch Shift On/Off
4 -> Toggle Knob 15 usage
