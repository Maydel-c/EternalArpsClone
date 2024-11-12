/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EternalArpsCloneAudioProcessorEditor::EternalArpsCloneAudioProcessorEditor (EternalArpsCloneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)/* , ring1(particle1, particle2, particle3) */
{
    particleSeparationSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    particleSeparationSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
    particleSeparationSlider.setRange(-100.0, 100.0, 1.0);
    particleSeparationSlider.setValue((double)separation);
    
    particleSeparationSlider.onValueChange = [this] { updateSeparation(separation); };
    addAndMakeVisible(particleSeparationSlider);
    
    particle1.addChangeListener(&ring1);
    particle2.addChangeListener(&ring1);
    particle3.addChangeListener(&ring1);
    
    addAndMakeVisible(ring1);
    
    addAndMakeVisible(particle1);
    addAndMakeVisible(particle2);
    addAndMakeVisible(particle3);
    
    startTimerHz(60);
    setSize (400, 300);
}

EternalArpsCloneAudioProcessorEditor::~EternalArpsCloneAudioProcessorEditor()
{
    particle1.removeAllChangeListeners();
    particle2.removeAllChangeListeners();
    particle3.removeAllChangeListeners();
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
    particle1.setBounds(50, (int)(getHeight() * 0.33), 4, 4);
    particle2.setBounds(50 - separation, (int)(getHeight() * 0.49), 4, 4);
    particle3.setBounds(50 - (separation * 2), (int)(getHeight() * 0.66), 4, 4);
    
    particleSeparationSlider.setBounds(getWidth() / 2 - 100, getHeight() - 50, 200, 40);
}

void EternalArpsCloneAudioProcessorEditor::timerCallback()
{
    
//    updateSeparation(separation);
    
    auto particle1Position = particle1.getX() + 1;
    particle1Position %= (int)getWidth();
    particle1.setBounds(particle1Position, (int)(getHeight() * 0.33), 4, 4);
    
    auto particle2Position = particle2.getX() + 1;
    if(particle1Position - separation >= 0)
    {
        particle2Position = particle1.getX() - separation;
    }
    particle2Position %= (int)getWidth();
    particle2.setBounds(particle2Position, (int)(getHeight() * 0.49), 4, 4);
       
    auto particle3Position = particle3.getX() + 1;
    if(particle2Position - separation >= 0)
    {
        particle3Position = particle2.getX() - separation;
    }
    particle3Position %= (int)getWidth();
    particle3.setBounds(particle3Position, (int)(getHeight() * 0.66), 4, 4);

        
    
    bool entered1 = ((particle1.getX() + 4) == ring1.getX());
    if (entered1)
    {
        DBG("particle 1 entered in timerCallback");
        particle1.particleStrikes();
    }
    bool entered2 = ((particle2.getX() + 4) == ring1.getX());
    if (entered2)
    {
        DBG("particle 2 entered in timerCallback");
        particle2.particleStrikes();
    }
    bool entered3 = ((particle3.getX() + 4) == ring1.getX());
    if (entered3)
    {
        DBG("particle 3 entered in timerCallback");
        particle3.particleStrikes();
    }
        
    repaint();
}

void EternalArpsCloneAudioProcessorEditor::updateSeparation(int currentSep)
{
    separation = static_cast<int>(particleSeparationSlider.getValue());
    particle2.setBounds(particle2.getX() - separation, (int)(getHeight() * 0.49), 4, 4);
    particle3.setBounds(particle3.getX() - (2 * separation), (int)(getHeight() * 0.66), 4, 4);
}
