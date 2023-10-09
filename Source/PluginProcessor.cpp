/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FullParametricEQAudioProcessor::FullParametricEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
    :
#endif
parameters(*this, nullptr, juce::Identifier("FullParametricEQ"), {
    //Lowshelf
    std::make_unique<juce::AudioParameterFloat>("lowshelfCutoffFrequency","Low Frequency",juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.3f), 20.f) ,
    std::make_unique<juce::AudioParameterFloat>("lowshelfGain","Low Frequency Gain",juce::NormalisableRange<float>(-20.f,20.f,0.1f,1.f),0.f),
    //Highself
    std::make_unique<juce::AudioParameterFloat>("highshelfCutoffFrequency","High Frequency",juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.3f), 20000.f) ,
    std::make_unique<juce::AudioParameterFloat>("highshelfGain","High Frequency Gain",juce::NormalisableRange<float>(-20.f,20.f,0.1f,1.f),0.f) ,
    //Peak1
    std::make_unique<juce::AudioParameterFloat>("peakCenterFrequency","Peak Center Frequency",juce::NormalisableRange<float>(20.f,20000.f,1.f, 0.3f),2000.f) ,
    std::make_unique<juce::AudioParameterFloat>("peakGain","Peak Gain",juce::NormalisableRange<float>(-20.f,20.f,0.1f,1.f),0.f) ,
    std::make_unique<juce::AudioParameterFloat>("peakBandwidth","Peak Bandwidth",juce::NormalisableRange<float>(1.f,19980.f,1.f,0.3f),2000.f)
    }), lowshelfFilter(low), highshelfFilter(high)
{
    this->lowshelfCutoffFrequencyParameter = this->parameters.getRawParameterValue("lowshelfCutoffFrequency");
    this->lowshelfGainParameter = this->parameters.getRawParameterValue("lowshelfGain");

    this->highshelfCutoffFrequencyParameter = this->parameters.getRawParameterValue("highshelfCutoffFrequency");
    this->highshelfGainParameter = this->parameters.getRawParameterValue("highshelfGain");

    this->peakCenterFrequencyParameter = this->parameters.getRawParameterValue("peakCenterFrequency");
    this->peakGainParameter = this->parameters.getRawParameterValue("peakGain");
    this->peakBandwidthParameter = this->parameters.getRawParameterValue("peakBandwidth");
}

FullParametricEQAudioProcessor::~FullParametricEQAudioProcessor()
{
}

//==============================================================================
const juce::String FullParametricEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FullParametricEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FullParametricEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FullParametricEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FullParametricEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FullParametricEQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FullParametricEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FullParametricEQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FullParametricEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void FullParametricEQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FullParametricEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->lowshelfFilter.setSamplingRate(static_cast<float>(sampleRate));
    this->highshelfFilter.setSamplingRate(static_cast<float>(sampleRate));
    this->peakFilter.setSamplingRate(static_cast<float>(sampleRate));
}

void FullParametricEQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FullParametricEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FullParametricEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //Lowshelf
    const auto lowshelfCutoffFrequency = this->lowshelfCutoffFrequencyParameter->load();
    const auto lowshelfGain = this->lowshelfGainParameter->load();
    this->lowshelfFilter.setCutoffFrequency(lowshelfCutoffFrequency);
    this->lowshelfFilter.setGain(lowshelfGain);

    this->lowshelfFilter.processBlock(buffer, midiMessages);

    //Highself
    const auto highshelfCutoffFrequency = this->highshelfCutoffFrequencyParameter->load();
    const auto highshelfGain = this->highshelfGainParameter->load();
    this->highshelfFilter.setCutoffFrequency(highshelfCutoffFrequency);
    this->highshelfFilter.setGain(highshelfGain);

    this->highshelfFilter.processBlock(buffer, midiMessages);

    //Peak1
    const auto peakCenterFrequency = this->peakCenterFrequencyParameter->load();
    const auto peakGain = this->peakGainParameter->load();
    const auto peakBandwidth = this->peakBandwidthParameter->load();
    this->peakFilter.setCenterFrequency(peakCenterFrequency);
    this->peakFilter.setGain(peakGain);
    this->peakFilter.setBandwidth(peakBandwidth);

    this->peakFilter.processBlock(buffer, midiMessages);
}

//==============================================================================
bool FullParametricEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FullParametricEQAudioProcessor::createEditor()
{
    return new FullParametricEQAudioProcessorEditor (*this, this->parameters);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void FullParametricEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = this->parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void FullParametricEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(this->parameters.state.getType()))
           this->parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FullParametricEQAudioProcessor();
}
