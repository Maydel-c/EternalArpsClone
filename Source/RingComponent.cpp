/*
  ==============================================================================

    RingComponent.cpp
    Created: 11 Nov 2024 6:58:47pm
    Author:  Abhinav

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RingComponent.h"

//==============================================================================
RingComponent::RingComponent()
{
}

RingComponent::~RingComponent()
{
}

juce::Atomic<bool> RingComponent::plucked1 { false };
// juce::Atomic<bool> RingComponent::plucked2 { false };
// juce::Atomic<bool> RingComponent::plucked3 { false };

void RingComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::whitesmoke);
    g.fillRect (getLocalBounds());
}

void RingComponent::resized()
{
}


void RingComponent::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    DBG("Changed in listenerCallback");
    plucked1.set(true);
}
