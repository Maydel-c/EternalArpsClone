/*
  ==============================================================================

    ParticleComponent.cpp
    Created: 11 Nov 2024 6:59:12pm
    Author:  Abhinav

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParticleComponent.h"

//==============================================================================
ParticleComponent::ParticleComponent()
{

}

ParticleComponent::~ParticleComponent()
{
}

juce::Atomic<bool> ParticleComponent::plucked { false };

void ParticleComponent::paint (juce::Graphics& g)
{
    auto bounds = juce::Rectangle<float>(4, 4);
    g.setColour(juce::Colours::limegreen);
    g.fillEllipse(bounds);
}

void ParticleComponent::resized()
{

}

void ParticleComponent::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    DBG("Changed in listenerCallback");
    plucked.set(true);
}

