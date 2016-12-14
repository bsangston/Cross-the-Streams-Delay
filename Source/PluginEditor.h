/*
 *  Brandon Sangston 4/15/2015
 *  PluginEditor.h
 *  Cross the Streams Delay VST3 Plugin
 *  Built using JUCE class library and framework and code from Luke Dahl
 */

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class EffectAudioProcessorEditor  :   public AudioProcessorEditor,
                                            public SliderListener,  // make Editor a SliderListener
                                            public Timer            // make Editor a Timer
{
public:
    EffectAudioProcessorEditor (EffectAudioProcessor&);
    ~EffectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override; // add the callback function
    void timerCallback() override;              // add the timer callback function
    
private:
    // This reference is provided as a quick way for the editor to
    // access the processor object that created it.
    EffectAudioProcessor& processor;
    
    //Add sliders
    Slider drySlider;
    Slider fbSlider;
    Slider delaySlider;
    Slider pingSlider;
    Slider pongSlider;
    Slider wetLSlider;
    Slider wetRSlider;
    Slider wetCSlider;
    
    //Add labels
    Label dryLabel;
    Label fbLabel;
    Label delayLabel;
    Label pingLabel;
    Label pongLabel;
    Label wetLLabel;
    Label wetRLabel;
    Label wetCLabel;
    
    
    //Image compatability
    Image yourImage;
    File imageFile;

    
    // Method that returns a pointer to the Processor object. This is how the Editor can send data to the processor
    EffectAudioProcessor& getProcessor() const
    {
        return static_cast<EffectAudioProcessor&> (processor);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
