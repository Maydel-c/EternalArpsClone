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
RingComponent::RingComponent( /* ParticleComponent& particle1,
                             ParticleComponent& particle2,
                             ParticleComponent& particle3 */)
             /*: particle1(particle1), particle2(particle2), particle3(particle3) */
{
//    particle1.addChangeListener(this);
//    particle2.addChangeListener(this);
//    particle3.addChangeListener(this);
}

RingComponent::~RingComponent()
{
//    particle1.removeChangeListener(this);
//    particle2.removeChangeListener(this);
//    particle3.removeChangeListener(this);
}

juce::Atomic<bool> RingComponent::plucked1 { false };
//juce::Atomic<bool> RingComponent::plucked2 { false };
//juce::Atomic<bool> RingComponent::plucked3 { false };

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
    DBG("Change received from broadcaster1");
    plucked1.set(true);

}
