/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EternalArpsCloneAudioProcessor::EternalArpsCloneAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    init();
}

EternalArpsCloneAudioProcessor::~EternalArpsCloneAudioProcessor()
{
}


void EternalArpsCloneAudioProcessor::init()
{
    formatManager.registerBasicFormats();
    audioReader = formatManager.createReaderFor(juce::File("../../../../Assets/vibraphone-C6.wav"));
//    DBG(juce::File::getCurrentWorkingDirectory().getFullPathName());
    if (audioReader != nullptr)
    {
        juce::AudioFormatReaderSource* newSource = new juce::AudioFormatReaderSource(audioReader, true);
        transportSource.setSource(newSource, 0, nullptr, audioReader->sampleRate);
        transportSource.setGain(1.0f);
    }
}

//==============================================================================
const juce::String EternalArpsCloneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EternalArpsCloneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EternalArpsCloneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EternalArpsCloneAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EternalArpsCloneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EternalArpsCloneAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EternalArpsCloneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EternalArpsCloneAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EternalArpsCloneAudioProcessor::getProgramName (int index)
{
    return {};
}

void EternalArpsCloneAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EternalArpsCloneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    transportSource.prepareToPlay(samplesPerBlock, sampleRate);

// Load and play the sample when the plugin loads
//    playSound();
}

void EternalArpsCloneAudioProcessor::releaseResources()
{
    transportSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EternalArpsCloneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EternalArpsCloneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Pass the buffer to the transport source to fill it with sample audio
    juce::AudioSourceChannelInfo audioSourceInfo(buffer);
    transportSource.getNextAudioBlock(audioSourceInfo);
    
    if (RingComponent::plucked1.compareAndSetBool(false, true))
    {
        playSound();
    }
}

void EternalArpsCloneAudioProcessor::playSound()
{
    transportSource.setPosition(0.0);
    transportSource.start();
}

//==============================================================================
bool EternalArpsCloneAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EternalArpsCloneAudioProcessor::createEditor()
{
    return new EternalArpsCloneAudioProcessorEditor (*this);
}

//==============================================================================
void EternalArpsCloneAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EternalArpsCloneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//void changeListenerCallback (juce::ChangeBroadcaster* source)
//{
//}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EternalArpsCloneAudioProcessor();
}
