/*
  ==============================================================================

    Welcome to Project Paradigm's Step Sequencer Processor cpp file

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ParadigmSeqAudioProcessor::ParadigmSeqAudioProcessor()
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
    , apvts(*this, nullptr, "Params", parameterLayout()) //This is where we initialize the APVTS
{

}

AudioProcessorValueTreeState::ParameterLayout ParadigmSeqAudioProcessor::parameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //This is where the parameter list begins

    return { params.begin(), params.end() };
}


ParadigmSeqAudioProcessor::~ParadigmSeqAudioProcessor()
{
}

//==============================================================================
const juce::String ParadigmSeqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ParadigmSeqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ParadigmSeqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ParadigmSeqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ParadigmSeqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ParadigmSeqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ParadigmSeqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ParadigmSeqAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ParadigmSeqAudioProcessor::getProgramName (int index)
{
    return {};
}

void ParadigmSeqAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ParadigmSeqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void ParadigmSeqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ParadigmSeqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ParadigmSeqAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

}

//==============================================================================
bool ParadigmSeqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ParadigmSeqAudioProcessor::createEditor()
{
    return new ParadigmSeqAudioProcessorEditor (*this);
}

//==============================================================================
void ParadigmSeqAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ParadigmSeqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ParadigmSeqAudioProcessor();
}
