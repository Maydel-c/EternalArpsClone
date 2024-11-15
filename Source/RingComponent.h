/*
  ==============================================================================

    RingComponent.h
    Created: 11 Nov 2024 6:58:47pm
    Author:  Abhinav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ParticleComponent.h"

//==============================================================================
/*
*/
class RingComponent  : public juce::Component, public juce::ChangeListener
{
public:
    RingComponent();
    ~RingComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    static juce::Atomic<bool> plucked1 /* ,plucked2, plucked3 */;


private:
//    ParticleComponent& particle1;
//    ParticleComponent& particle2;
//    ParticleComponent& particle3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RingComponent)
};
