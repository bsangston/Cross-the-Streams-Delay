/*
 *  Brandon Sangston 4/15/2015
 *  PluginProcessor.h
 *  Cross the Streams Delay VST3 Plugin
 *  Built using JUCE class library and framework and code from Luke Dahl
 */

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "UParam.h"
#include "BiQuad.h"
#include "Delay.h"
#include "Mu45FilterCalc.h"
#include "PitShift.h"


//==============================================================================
/**
*/
class EffectAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EffectAudioProcessor();
    ~EffectAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    float getParameterDefaultValue (int index) override;    // STEP 4.7a

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    //===== ADD NEW STUFF HERE =====================================================
    
    // STEP 4.1 - Create an enumerated type called 'Parameters' for the User Parameters
    enum Parameters
    {
        dryParam = 0, // set the first to zero
        fbParam,
        delayParam,
        pingParam,
        pongParam,
        wetLParam,
        wetRParam,
        wetCParam,
        totalNumParams      // must end with this variable
    };
    
    // STEP 4.2 - Create a float to store the value of each user parameter
    float uParamDryGain;
    float uParamFeedback;
    float uParamDelay;
    float uParamPingDelay;
    float uParamPongDelay;
    float uParamWetGainL;
    float uParamWetGainR;
    float uParamWetGainC;
    
    
    UParam getUserParams();
    UParam usrParams[totalNumParams];
    
    
private:
    //==============================================================================
    
    // STEP 6.1 - Add algorithm parameters here
    float fs;
    float maxDelayMsec = 1500.0;
    float dryGain;
    float pingGain, pongGain, fbGain, fbGain2;
    float wetL, wetR, wetC;
    
    //Delay Lines
    stk::Delay PingDelay;
    stk::Delay PongDelay;
    stk::Delay CenterDelay;
    stk::Delay fbDelay, fbDelay1, fbDelay2, fbDelay3;
    
    //Pitch Shifters
    stk::PitShift OctaveUp;
    stk::PitShift OctaveDown;
    
    //Filters
    stk::BiQuad highpass, lowpassL, lowpassR, lowpass, highpass2, lowpass2;
    
    // STEP XX - Add any methods used in algorithm parameter calculation or DSP
    void calcHighPass();
    void calcLowPass();
    void calcFilterCoeffs();
    void calcGains();
    void SetPitchShift();
    void calcDelays();
    int calcDelaySampsFromMsec(float Msec);
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectAudioProcessor)
    
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
