# Cross the Streams Delay VST3 Plugin
  
  Built using JUCE 3.10 class library and API for Mac OSX (C/C++)

![alt text](https://github.com/Bsangston/Cross-the-Streams-Delay/blob/master/Cross%20the%20Streams%20Delay.png)

## Description:
Intricate pitch-shifting ping-pong delay with an additional centered delay channel. When the signal is streamed to the left channel (ping delay), it is pitched up one octave, and when it is streamed to the right channel (pong delay), it is pitched down one octave. A simple feedback control is associated with the feedback parameters of all delay streams. Additional controls include individual delay times and dry/wet mix for each. Designed to create rich textures from pitched content and implement intricate delay lines with nuanced harmonic content.

![alt text](https://github.com/Bsangston/Cross-the-Streams-Delay/blob/master/PluginWindow.png)

## Included:
- All audio processing, effect, and GUI code built with the JUCE framework
- [StkLite](https://ccrma.stanford.edu/software/stk/), including base code for delay, filter, and pitch shift objects
- Additional code by Luke Dahl for calculating filter coefficients and including parameter automation functionality
- Background image resource

## Required:
- JUCE framework installation required for compilation, found here <https://www.juce.com/> 

## Source:
- PluginEditor.h 
- PluginEditor.cpp (GUI Implementation)
- PluginProcessor.h
- PluginProcessor.cpp (The guts of the program)

### From Luke Dahl:
- Mu45FilterCalc.h
- Mu45FilterCalc.cpp (Filter coefficient calculations for several different filter types)
- UParam.h (Allows for automation of VST parameters)

## StkLite 
### src
- BiQuad.cpp	
- DelayA.cpp 
- Fir.cpp		
- Iir.cpp		
- OneZero.cpp	
- Stk.cpp		
- TwoPole.cpp
- Delay.cpp	
- DelayL.cpp	
- FormSwep.cpp	
- OnePole.cpp	
- PoleZero.cpp	
- TapDelay.cpp	
- TwoZero.cpp

### include:
- BiQuad.h	
- DelayL.h	
- FormSwep.h	
- OneZero.h	
- TapDelay.h
- Delay.h		
- Filter.h	
- Iir.h		
- PoleZero.h	
- TwoPole.h
- DelayA.h	
- Fir.h		
- OnePole.h
- Stk.h		
- TwoZero.h
