/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EternalArpsCloneAudioProcessorEditor::EternalArpsCloneAudioProcessorEditor (EternalArpsCloneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    ring1.addChangeListener(&particle1);
    
    addAndMakeVisible(ring1);
    addAndMakeVisible(particle1);
    
    startTimerHz(60);
    setSize (400, 300);
}

EternalArpsCloneAudioProcessorEditor::~EternalArpsCloneAudioProcessorEditor()
{
    ring1.removeAllChangeListeners();
}

//==============================================================================
void EternalArpsCloneAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void EternalArpsCloneAudioProcessorEditor::resized()
{
    ring1.setBounds(getWidth() / 2 - 1, getHeight() / 2 - 100, 2, 200);
    particle1.setBounds(getWidth() / 10, getHeight() / 2, 4, 4);
}

void EternalArpsCloneAudioProcessorEditor::timerCallback()
{
    auto particlePosition = particle1.getX() % (int)(getWidth() * 0.9f);
    particle1.setBounds(particlePosition + 1, getHeight() / 2, 4, 4);
    
    bool entered = ((particle1.getX() + 4) == ring1.getX());
    if (entered)
    {
        DBG("enter in timerCallback");
        ring1.particleStrikes();
    }
    
    repaint();
}
