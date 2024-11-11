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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

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
