/*
 *  Brandon Sangston 4/15/2015
 *  PluginEditor.cpp
 *  Cross the Streams Delay VST3 Plugin
 *  Built using JUCE class library and framework and code from Luke Dahl
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

EffectAudioProcessorEditor::EffectAudioProcessorEditor (EffectAudioProcessor& p)
:   AudioProcessorEditor (&p), processor (p),

        drySlider("dry mix"),
        fbSlider("feedback"),
        delaySlider("delay time center"),
        pingSlider("ping delay"),
        pongSlider("pong delay"),
        wetLSlider("wet left"),
        wetRSlider("wet right"),
        wetCSlider("wet center"),

        dryLabel("", "Dry Gain"),
        fbLabel("", "Feedback"),
        delayLabel("", "Center Delay (ms)"),
        pingLabel("", "Ping Delay (ms)"),
        pongLabel("", "Pong Delay (ms)"),
        wetLLabel("", "Wet Left"),
        wetRLabel("", "Wet Right"),
        wetCLabel("", "Wet Center")


{
    //Dry
    addAndMakeVisible(drySlider);
    drySlider.setRange (0, 100, 1);
    drySlider.setSliderStyle (Slider::LinearVertical);
    drySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    drySlider.setColour (Slider::thumbColourId, Colour (0xff229bff));
    drySlider.setColour (Slider::trackColourId, Colour (0x7fffffff));
    drySlider.addListener(this);
    addAndMakeVisible(dryLabel);
    dryLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    dryLabel.setColour (Label::textColourId, Colours::white);
    dryLabel.setJustificationType(Justification::centred);
    
    //Feedback
    addAndMakeVisible(fbSlider);
    fbSlider.setRange (0, 100, 1);
    fbSlider.setSliderStyle (Slider::LinearVertical);
    fbSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    fbSlider.setColour (Slider::thumbColourId, Colour (0xff229bff));
    fbSlider.setColour (Slider::trackColourId, Colour (0x7fffffff));
    fbSlider.addListener(this);
    addAndMakeVisible(fbLabel);
    fbLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    fbLabel.setColour (Label::textColourId, Colours::white);
    fbLabel.setJustificationType(Justification::centred);
    
    //Center Delay
    addAndMakeVisible(delaySlider);
    delaySlider.setRange (0, 1500, 1);
    delaySlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    delaySlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    delaySlider.setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    delaySlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    delaySlider.addListener(this);
    addAndMakeVisible(delayLabel);
    delayLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    delayLabel.setColour (Label::textColourId, Colours::white);
    delayLabel.setJustificationType(Justification::centred);
    
    //Ping Delay
    addAndMakeVisible(pingSlider);
    pingSlider.setRange (0, 1500, 1);
    pingSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    pingSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pingSlider.setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    pingSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    pingSlider.addListener(this);
    addAndMakeVisible(pingLabel);
    pingLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    pingLabel.setColour (Label::textColourId, Colours::white);
    pingLabel.setJustificationType(Justification::centred);
    
    //Pong Delay
    addAndMakeVisible(pongSlider);
    pongSlider.setRange (0, 1500, 1);
    pongSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    pongSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    pongSlider.setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    pongSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    pongSlider.addListener(this);
    addAndMakeVisible(pongLabel);
    pongLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    pongLabel.setColour (Label::textColourId, Colours::white);
    pongLabel.setJustificationType(Justification::centred);

    //Wet Left
    addAndMakeVisible(wetLSlider);
    wetLSlider.setRange (0, 100, 1);
    wetLSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    wetLSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    wetLSlider.setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    wetLSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    wetLSlider.addListener(this);
    addAndMakeVisible(wetLLabel);
    wetLLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    wetLLabel.setColour (Label::textColourId, Colours::white);
    wetLLabel.setJustificationType(Justification::centred);
    
    //Wet Right
    addAndMakeVisible(wetRSlider);
    wetRSlider.setRange (0, 100, 1);
    wetRSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    wetRSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    wetRSlider.setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    wetRSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    wetRSlider.addListener(this);
    addAndMakeVisible(wetRLabel);
    wetRLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    wetRLabel.setColour (Label::textColourId, Colours::white);
    wetRLabel.setJustificationType(Justification::centred);

    //Wet Center
    addAndMakeVisible(wetCSlider);
    wetCSlider.setRange (0, 100, 1);
    wetCSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    wetCSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    wetCSlider.setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    wetCSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    wetCSlider.addListener(this);
    addAndMakeVisible(wetCLabel);
    wetCLabel.setFont(Font ("Harrington", 14.00f, Font::plain));
    wetCLabel.setColour (Label::textColourId, Colours::white);
    wetCLabel.setJustificationType(Justification::centred);
    

    //load image from binary data
    yourImage = ImageFileFormat::loadFrom(BinaryData::PluginBackground_jpg, (size_t) BinaryData::PluginBackground_jpgSize);
    
    
    //Set editor size before constructor is finished
    setSize (460, 325);
    
    //Start the timer
    startTimer (50);      // timerCallback() will get called every 50 msec.
}

EffectAudioProcessorEditor::~EffectAudioProcessorEditor()
{
}

//Paints GUI and loads backgroud image/fonts
void EffectAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    
    g.setColour (Colours::black);
    g.drawImage(yourImage, 0, 0, 460, 325, 0, 0, yourImage.getWidth(), yourImage.getHeight(), false);
    
    g.setGradientFill (ColourGradient (Colour (0xffff9700),
                                       200.0f, 80.0f,
                                       Colour (0xff00c4ff),
                                       104.0f, static_cast<float> (-56),
                                       false));
    g.setFont (Font ("Futura", 20.00f, Font::plain));
    g.drawText (TRANS("CROSS THE STREAMS DELAY"),
                8, -2, 264, 30,
                Justification::centred, true);
   
    
}

void EffectAudioProcessorEditor::resized()
{
    // Set the position and size of the slider objects
    drySlider.setBounds (376, 40, 63, 265);
    fbSlider.setBounds (296, 40, 63, 265);
    pingSlider.setBounds (24, 96, 72, 72);
    pongSlider.setBounds (184, 96, 72, 72);
    delaySlider.setBounds (104, 48, 72, 72);
    wetLSlider.setBounds (24, 232, 72, 72);
    wetRSlider.setBounds (184, 232, 72, 72);
    wetCSlider.setBounds (104, 184, 72, 72);
    dryLabel.setBounds (360, 16, 96, 24);
    fbLabel.setBounds (280, 16, 96, 24);
    delayLabel.setBounds (88, 24, 104, 24);
    pingLabel.setBounds (8, 72, 104, 24);
    pongLabel.setBounds (168, 72, 104, 24);
    wetCLabel.setBounds (88, 160, 104, 24);
    wetRLabel.setBounds (168, 208, 104, 24);
    wetLLabel.setBounds (8, 208, 104, 24);
    
}

// Implement the listener callback function
// This is the Slider::Listener callback, when the user drags a slider.
void EffectAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    float vstVal;
   
    // It's vital to use setParameterNotifyingHost to change any parameters that are automatable
    // by the host, rather than just modifying them directly, otherwise the host won't know
    // that they've changed.
    // first set the usrParam from the slider, and get the vst normalized version of the uParam:
    
    if (slider == &drySlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::dryParam].setWithUparam(drySlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::dryParam, vstVal);
    
    }
   
    else if (slider == &fbSlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::fbParam].setWithUparam(fbSlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::fbParam, vstVal);
        
    }
   
    else if (slider == &delaySlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::delayParam].setWithUparam(delaySlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::delayParam, vstVal);
        
    }
    
    else if (slider == &pingSlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::pingParam].setWithUparam(pingSlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::pingParam, vstVal);
        
    }
   
    else if (slider == &pongSlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::pongParam].setWithUparam(pongSlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::pongParam, vstVal);
    }

    else if (slider == &wetLSlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::wetLParam].setWithUparam(wetLSlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::wetLParam, vstVal);
    }
    
    else if (slider == &wetRSlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::wetRParam].setWithUparam(wetRSlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::wetRParam, vstVal);
    }
    
    else if (slider == &wetCSlider)
    {
        vstVal = getProcessor().usrParams[EffectAudioProcessor::wetCParam].setWithUparam(wetCSlider.getValue());
        getProcessor().setParameterNotifyingHost (EffectAudioProcessor::wetCParam, vstVal);
    }
    
}

// Set the timer callback to update the UI
// This timer periodically checks whether any of the filter's parameters have changed...
void EffectAudioProcessorEditor::timerCallback()
{
    // get a pointer to our Processor object
    EffectAudioProcessor& ourProcessor = getProcessor();
    
    // these get will update the sliders in the UI
    drySlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::dryParam].getUparamVal(), dontSendNotification);
    fbSlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::fbParam].getUparamVal(), dontSendNotification);
    delaySlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::delayParam].getUparamVal(), dontSendNotification);
    pingSlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::pingParam].getUparamVal(), dontSendNotification);
    pongSlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::pongParam].getUparamVal(), dontSendNotification);
    wetLSlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::wetLParam].getUparamVal(), dontSendNotification);
    wetRSlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::wetRParam].getUparamVal(), dontSendNotification);
    wetCSlider.setValue(ourProcessor.usrParams[EffectAudioProcessor::wetCParam].getUparamVal(), dontSendNotification);
    
    
}


