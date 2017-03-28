/*
 *  Brandon Sangston 4/15/2015
 *  PluginProcessor.cpp
 *  Cross the Streams Delay VST3 Plugin
 *  Built using JUCE class library and framework and code from Luke Dahl
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BiQuad.h"
#include "Delay.h"

#define JucePlugin_Name "Cross the Streams Delay"

// Defined default values for all user params
const int defaultDry = 100;
const int defaultFeedback = 75;
const float defaultDelayTime = 250;
const float defaultPingDelay = 1000;
const float defaultPongDelay = 500;
const int defaultWetL = 75;
const int defaultWetC = 50;
const int defaultWetR = 75;


//==============================================================================
EffectAudioProcessor::EffectAudioProcessor()
{
    // Set default values for all usrParams
   
    usrParams[dryParam].setMinMax(0, 100);
    usrParams[dryParam].setWithUparam(defaultDry);
    
    usrParams[fbParam].setMinMax(0, 100);
    usrParams[fbParam].setWithUparam(defaultFeedback);
    
    usrParams[delayParam].setMinMax(0, 1500);
    usrParams[delayParam].setWithUparam(defaultDelayTime);
    
    usrParams[pingParam].setMinMax(0, 1500);
    usrParams[pingParam].setWithUparam(defaultPingDelay);
    
    usrParams[pongParam].setMinMax(0, 1500);
    usrParams[pongParam].setWithUparam(defaultPongDelay);
    
    usrParams[wetLParam].setMinMax(0, 100);
    usrParams[wetLParam].setWithUparam(defaultWetL);
    
    usrParams[wetRParam].setMinMax(0, 100);
    usrParams[wetRParam].setWithUparam(defaultWetR);
    
    usrParams[wetCParam].setMinMax(0, 100);
    usrParams[wetCParam].setWithUparam(defaultWetC);
    
}

EffectAudioProcessor::~EffectAudioProcessor()
{
}

const String EffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

// Return the correct number of user parameters
int EffectAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float EffectAudioProcessor::getParameter (int index)
{
    // Returns the slider value of a user param when called with its index
    switch (index)
    {
        case dryParam:
            return usrParams[dryParam].getVstVal();
        case fbParam:
            return usrParams[fbParam].getVstVal();
        case delayParam:
            return usrParams[delayParam].getVstVal();
        case pingParam:
            return usrParams[pingParam].getVstVal();
        case pongParam:
            return usrParams[pongParam].getVstVal();
        case wetLParam:
            return usrParams[wetLParam].getVstVal();
        case wetRParam:
            return usrParams[wetRParam].getVstVal();
        case wetCParam:
            return usrParams[wetCParam].getVstVal();
        
        default:
            return 0.0f;
    }
    
    
}

void EffectAudioProcessor::setParameter (int index, float newValue)
{
    
// Set algorithm parameters from user parameters
    switch (index)
    {
        //Dry
        case dryParam:
            usrParams[dryParam].setWithVstVal(newValue);
            calcGains();
            break;
        //Feedback
        case fbParam:
            usrParams[fbParam].setWithVstVal(newValue);
            calcGains();
            break;
        //Delay Time Center
        case delayParam:
            usrParams[delayParam].setWithVstVal(newValue);
            calcDelays();
            break;
        //Ping Delay
        case pingParam:
            usrParams[pingParam].setWithVstVal(newValue);
            calcDelays();
            break;
        //Pong Delay
        case pongParam:
            usrParams[pongParam].setWithVstVal(newValue);
            calcDelays();
            break;
        //Wet Left
        case wetLParam:
            usrParams[wetLParam].setWithVstVal(newValue);
            calcGains();
            break;
        //Wet Right
        case wetRParam:
            usrParams[wetRParam].setWithVstVal(newValue);
            calcGains();
            break;
        //Wet Center
        case wetCParam:
            usrParams[wetCParam].setWithVstVal(newValue);
            calcGains();
            break;

        default:
            break;
    }
    
}

//Calculates delay from ms to samples
int EffectAudioProcessor::calcDelaySampsFromMsec(float Msec)
{
    int samps = round(Msec * (fs/1000));
    return samps;
}


//Calculates and sets delays in signal chain
void EffectAudioProcessor::calcDelays()
{
    float MsecL = usrParams[pingParam].getUparamVal();
    int sampsL = calcDelaySampsFromMsec(MsecL);
    PingDelay.setDelay(sampsL);
    
    float MsecC = usrParams[delayParam].getUparamVal();
    int sampsC = calcDelaySampsFromMsec(MsecC);
    CenterDelay.setDelay(sampsC);
    
    float fbDelayTime = (sampsC/2);
    fbDelay.setDelay(fbDelayTime);
    
    float MsecR = usrParams[pongParam].getUparamVal();
    int sampsR = calcDelaySampsFromMsec(MsecR);
    PongDelay.setDelay(sampsR);
    
}

//Calculates and sets all gains in signal chain
void EffectAudioProcessor::calcGains()
{
    dryGain = 0.01 * usrParams[dryParam].getUparamVal();
    
    wetL = 0.01 * usrParams[wetLParam].getUparamVal();
    wetC = 0.01 * usrParams[wetCParam].getUparamVal();
    wetR = 0.01 * usrParams[wetRParam].getUparamVal();
    
    fbGain = 0.90 * 0.01 * usrParams[fbParam].getUparamVal();
    
}

//Calculate filter coeffs for all high pass filters in signal chain
void EffectAudioProcessor::calcHighPass()
{
    float Q = 0.71;
    float coeffs[5];
    float fc = 200;
    
    Mu45FilterCalc::calcCoeffsHPF(coeffs, fc, Q, fs);
    
    highpass.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    highpass2.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);

}

//Calculate filter coeffs forlow pass filters in signal chain
void EffectAudioProcessor::calcLowPass()
{
    float Q = 0.71;
    float coeffs[5];
    float fc = 10000;
    
    Mu45FilterCalc::calcCoeffsLPF(coeffs, fc, Q, fs);
    
    lowpass.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    lowpass2.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    lowpassL.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    lowpassR.setCoefficients(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
    
}

//Method to call all filter calculations
void EffectAudioProcessor::calcFilterCoeffs()
{
    calcHighPass();
    calcLowPass();
}

//Sets pitch shift of each channel
void EffectAudioProcessor::SetPitchShift()
{
    OctaveUp.setShift(2.0);
    OctaveDown.setShift(0.5);
}

//Returns default parameter values
float EffectAudioProcessor::getParameterDefaultValue (int index)
{
    switch (index)
    {
        case dryParam:
            return defaultDry;
        case fbParam:
            return defaultFeedback;
        case pingParam:
            return defaultPingDelay;
        case delayParam:
            return defaultDelayTime;
        case pongParam:
            return defaultPongDelay;
        case wetLParam:
            return defaultWetL;
        case wetCParam:
            return defaultWetC;
        case wetRParam:
            return defaultWetR;
        
        default:            break;
    }
    
    return 0.0f;
}

// Returns parameter names
const String EffectAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case dryParam:         return "Dry Mix";
        case fbParam:          return "Feedback";
        case pingParam:        return "Ping Delay";
        case delayParam:       return "Center Delay";
        case pongParam:        return "Pong Delay";
        case wetLParam:        return "Wet Left";
        case wetCParam:        return "Wet Center";
        case wetRParam:        return "Wet Right";
        
        default:            break;
    }
    
    return String::empty;
}

const String EffectAudioProcessor::getParameterText (int index)
{
    return String( usrParams[index].getUparamVal() );
   // return String (getParameter (index), 2);
}

const String EffectAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String EffectAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool EffectAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool EffectAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool EffectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EffectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EffectAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double EffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EffectAudioProcessor::getCurrentProgram()
{
    return 1;
}

void EffectAudioProcessor::setCurrentProgram (int index)
{
}

const String EffectAudioProcessor::getProgramName (int index)
{
    return String();
}

void EffectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // pre-playback initialisation that you need..
    fs = sampleRate;
    
    //initialize delays with maximum length
    int samps = calcDelaySampsFromMsec(maxDelayMsec);
    PingDelay.setMaximumDelay(samps);
    CenterDelay.setMaximumDelay(samps);
    fbDelay.setMaximumDelay(samps);
    PongDelay.setMaximumDelay(samps);
    
    // calc all algorithm params
    calcGains();
    calcDelays();
    calcFilterCoeffs();
    SetPitchShift();
}

void EffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void EffectAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Guts of the audio processing
    const int numSamples = buffer.getNumSamples();
    
    // assumes two channels
    float* channelDataL = buffer.getWritePointer (0);
    float* channelDataR = buffer.getWritePointer (1);
    
    float tempUP, tempDOWN, tempC, channelDataC, tempC2, tempL, tempR;
    //the inner loop
    for (int i = 0; i < numSamples; ++i)
    {
        // DSP magic:
        
        channelDataC = 0.75*(channelDataL[i] + channelDataR[i]);
        
        // get next out
        tempL = PingDelay.nextOut();
        tempR = PongDelay.nextOut();
        tempC = CenterDelay.nextOut();
        tempC2 = (fbGain/2)*fbDelay.nextOut();
        
        //pitch shifting
        tempUP = OctaveUp.tick(channelDataL[i] + tempR*fbGain);
        tempDOWN = OctaveDown.tick(channelDataR[i] + tempL*fbGain);
       
        // compute next input to filter (with feedback) and tick
        tempL = PingDelay.tick(tempUP);
        tempL = lowpassL.tick(tempL);
    
        tempR = PongDelay.tick(tempDOWN);
        tempR = lowpassR.tick(tempR);
        
        tempC = CenterDelay.tick(channelDataC + fbGain*tempC);
        tempC = highpass.tick(tempC);
        tempC = lowpass.tick(tempC);
        
        tempC2 = fbDelay.tick(tempC + tempC2);
        tempC2 = highpass2.tick(tempC2);
        tempC2 = lowpass2.tick(tempC2);
        
        // mix wet and dry
        channelDataL[i] = dryGain*channelDataL[i] + wetL*tempL + wetC*(tempC);
        channelDataR[i] = dryGain*channelDataR[i] + wetR*tempR + wetC*(tempC);
        
        
        
    }
}

//==============================================================================
bool EffectAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* EffectAudioProcessor::createEditor()
{
    return new EffectAudioProcessorEditor (*this);
}

//==============================================================================
void EffectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EffectAudioProcessor();
}
