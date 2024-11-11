/*
  ==============================================================================

    ParticleComponent.h
    Created: 11 Nov 2024 6:59:12pm
    Author:  Abhinav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/



class ParticleComponent  : public juce::Component, public juce::ChangeListener
{
public:
    ParticleComponent();
    ~ParticleComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    static juce::Atomic<bool> plucked;
    
private:   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParticleComponent)
};

