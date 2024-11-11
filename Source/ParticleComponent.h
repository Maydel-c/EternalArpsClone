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



class ParticleComponent  : public juce::Component, public juce::ChangeBroadcaster
{
public:
    ParticleComponent();
    ~ParticleComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void particleStrikes();
    
    
    int setParticleId(int Id);
private:
    int particleId;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParticleComponent)
};

