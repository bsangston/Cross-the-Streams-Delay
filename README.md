# Cross the Streams Delay VST3 Plugin
  
  Built using JUCE 3.10 class library and API for Mac OSX (C/C++)

## Included:
- All audio processing, effect, and GUI code built with the JUCE framework
- [StkLite](https://ccrma.stanford.edu/software/stk/), including base code for delay, filter, and pitch shift objects
- Additional code by Luke Dahl for calculating filter coefficients and including parameter automation functionality
- Background image resource

## Required:
- JUCE framework installation required for compilation, found here <https://www.juce.com/> 

## Source:
- PluginEditor.h
- PluginEditor.cpp
- PluginProcessor.h
- PluginProcessor.cpp
### From Luke Dahl
- Mu45FilterCalc.h
- Mu45FilterCalc.cpp
- UParam.h

## StkLite 
#### src
- BiQuad.cpp	
- DelayA.cpp	- 
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
#### include
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
