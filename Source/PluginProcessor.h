/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ShelfFilter.h"
#include "PeakFilter.h"

//==============================================================================
/**
*/
class FullParametricEQAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FullParametricEQAudioProcessor();
    ~FullParametricEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    juce::AudioProcessorValueTreeState parameters;
    
    ShelfFilter lowshelfFilter;
    std::atomic<float>* lowshelfCutoffFrequencyParameter = nullptr;
    std::atomic<float>* lowshelfGainParameter = nullptr;

    ShelfFilter highshelfFilter;
    std::atomic<float>* highshelfCutoffFrequencyParameter = nullptr;
    std::atomic<float>* highshelfGainParameter = nullptr;
    
    PeakFilter peakFilterL;
    std::atomic<float>* peakLCenterFrequencyParameter = nullptr;
    std::atomic<float>* peakLGainParameter = nullptr;
    std::atomic<float>* peakLBandwidthParameter = nullptr;

    PeakFilter peakFilterM;
    std::atomic<float>* peakMCenterFrequencyParameter = nullptr;
    std::atomic<float>* peakMGainParameter = nullptr;
    std::atomic<float>* peakMBandwidthParameter = nullptr;

    PeakFilter peakFilterH;
    std::atomic<float>* peakHCenterFrequencyParameter = nullptr;
    std::atomic<float>* peakHGainParameter = nullptr;
    std::atomic<float>* peakHBandwidthParameter = nullptr;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FullParametricEQAudioProcessor)
};
