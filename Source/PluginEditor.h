/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FullParametricEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FullParametricEQAudioProcessorEditor (FullParametricEQAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~FullParametricEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FullParametricEQAudioProcessor& audioProcessor;

    juce::AudioProcessorValueTreeState& valueTreeState;

    //Lowshelf
    juce::Label lowshelfCutoffFrequencyLabel;
    juce::Slider lowshelfCutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowshelfCutoffFrequencyAttachment;

    juce::Label lowshelfGainLabel;
    juce::Slider lowshelfGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowshelfGainAttachment;

    //Highself
    juce::Label highshelfCutoffFrequencyLabel;
    juce::Slider highshelfCutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highshelfCutoffFrequencyAttachment;

    juce::Label highshelfGainLabel;
    juce::Slider highshelfGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highshelfGainAttachment;

    //Peak1
    juce::Label peakCenterFrequencyLabel;
    juce::Slider peakCenterFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakCenterFrequencyAttachment;

    juce::Label peakGainLabel;
    juce::Slider peakGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakGainAttachment;
    
    juce::Label peakBandwidthLabel;
    juce::Slider peakBandwidthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakBandwidthAttachment;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FullParametricEQAudioProcessorEditor)
};
