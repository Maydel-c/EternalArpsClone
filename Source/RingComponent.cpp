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

void RingComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::whitesmoke);
    g.fillRect (getLocalBounds());
}

void RingComponent::resized()
{
}

void RingComponent::particleStrikes()
{
    sendChangeMessage();
}
