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
class LookAndFeel : public juce::LookAndFeel_V4{
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;


};

class RotarySliderWithLabels : public juce::Slider {
public:
    RotarySliderWithLabels(juce::RangedAudioParameter& param, juce::String& labelName, juce::String& labelText, juce::String& suffix);

    ~RotarySliderWithLabels() {
        setLookAndFeel(nullptr);
        delete label;
    }

    void paint(juce::Graphics& g) override;

    int getStringHeight() const { return 15; };
    juce::String getDisplayText() const;
    juce::String getLabelText() const;



private:
    juce::RangedAudioParameter* param;
    juce::String suffix;
    juce::Label* label;
    LookAndFeel lookAndFeel;
    //külön implementálni az attachmenteket a main classba, és a constr-ba beadni őket
};

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

    LookAndFeel lookAndFeel;

    RotarySliderWithLabels lowshelfCutoffFrequency, lowshelfGain, highshelfCutoffFrequency, highshelfGain, peakLCenterFrequency, peakLGain, peakLQuality, peakMCenterFrequency, peakMGain, peakMQuality, peakHCenterFrequency, peakHGain, peakHQuality;
    juce::Label *lowshelfLabel, *peakLabel, *highshelfLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowshelfCutoffFrequencyAttachment, lowshelfGainAttachment, highshelfCutoffFrequencyAttachment, highshelfGainAttachment, peakLCenterFrequencyAttachment, peakLGainAttachment, peakLQualityAttachment, peakMCenterFrequencyAttachment, peakMGainAttachment, peakMQualityAttachment, peakHCenterFrequencyAttachment, peakHGainAttachment, peakHQualityAttachment;

    /*//Lowshelf
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

    //PeakL
    juce::Label peakLCenterFrequencyLabel;
    juce::Slider peakLCenterFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakLCenterFrequencyAttachment;

    juce::Label peakLGainLabel;
    juce::Slider peakLGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakLGainAttachment;
    
    juce::Label peakLBandwidthLabel;
    juce::Slider peakLBandwidthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakLBandwidthAttachment;

    //PeakM
    juce::Label peakMCenterFrequencyLabel;
    juce::Slider peakMCenterFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakMCenterFrequencyAttachment;

    juce::Label peakMGainLabel;
    juce::Slider peakMGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakMGainAttachment;

    juce::Label peakMBandwidthLabel;
    juce::Slider peakMBandwidthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakMBandwidthAttachment;

    //PeakH
    juce::Label peakHCenterFrequencyLabel;
    juce::Slider peakHCenterFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakHCenterFrequencyAttachment;

    juce::Label peakHGainLabel;
    juce::Slider peakHGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakHGainAttachment;

    juce::Label peakHBandwidthLabel;
    juce::Slider peakHBandwidthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakHBandwidthAttachment;
    */
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FullParametricEQAudioProcessorEditor)
};
