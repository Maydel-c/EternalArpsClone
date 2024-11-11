/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RingComponent.h"
#include "ParticleComponent.h"

//==============================================================================
/**
*/
class EternalArpsCloneAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    EternalArpsCloneAudioProcessorEditor (EternalArpsCloneAudioProcessor&);
    ~EternalArpsCloneAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void updateSeparation(int currentSep);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EternalArpsCloneAudioProcessor& audioProcessor;
    
    juce::Slider particleSeparationSlider;
    
    RingComponent ring1;
    ParticleComponent particle1, particle2, particle3;
    
    int separation = 50;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EternalArpsCloneAudioProcessorEditor)
};
