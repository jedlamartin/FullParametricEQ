/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FullParametricEQAudioProcessorEditor::FullParametricEQAudioProcessorEditor (FullParametricEQAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState (vts)
{
    //Lowshelf
    //lowshelfCutoffFrequencyLabel.setText("Lowshelf Cutoff Frequency", juce::dontSendNotification);
    //addAndMakeVisible(lowshelfCutoffFrequencyLabel);

    addAndMakeVisible(lowshelfCutoffFrequencySlider);
    this->lowshelfCutoffFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->lowshelfCutoffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->lowshelfCutoffFrequencyAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lowshelfCutoffFrequency", lowshelfCutoffFrequencySlider));
    
    //lowshelfGainLabel.setText("Gain", juce::dontSendNotification);
    //addAndMakeVisible(lowshelfGainLabel);

    addAndMakeVisible(lowshelfGainSlider);
    this->lowshelfGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->lowshelfGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->lowshelfGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lowshelfGain", lowshelfGainSlider));
    
    //Highshelf
    addAndMakeVisible(highshelfCutoffFrequencySlider);
    this->highshelfCutoffFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->highshelfCutoffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->highshelfCutoffFrequencyAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "highshelfCutoffFrequency", highshelfCutoffFrequencySlider));

    addAndMakeVisible(highshelfGainSlider);
    this->highshelfGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->highshelfGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->highshelfGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "highshelfGain", highshelfGainSlider));


    //Peak1
    addAndMakeVisible(peakCenterFrequencySlider);
    this->peakCenterFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakCenterFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakCenterFrequencyAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakCenterFrequency", peakCenterFrequencySlider));

    addAndMakeVisible(peakGainSlider);
    this->peakGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakGain", peakGainSlider));

    addAndMakeVisible(peakBandwidthSlider);
    this->peakBandwidthSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakBandwidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakBandwidthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakBandwidth", peakBandwidthSlider));


    

    //setSize(paramSliderWidth + paramLabelWidth, juce::jmax(100, paramControlHeight * 2));

    setSize (600, 400);
}

FullParametricEQAudioProcessorEditor::~FullParametricEQAudioProcessorEditor()
{
}

//==============================================================================
void FullParametricEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);

    /*juce::AudioBuffer<float> delta(1, 512);
    delta.clear();
    *(delta.getWritePointer(0))=1;
    //*(delta.getWritePointer(1))=1;
    this->audioProcessor.processBlock(delta, juce::MidiBuffer());
    delta.setSize(1, 1024, true, true);
    juce::dsp::FFT(9).performRealOnlyForwardTransform(delta.getWritePointer(0));
    */
}

void FullParametricEQAudioProcessorEditor::resized()
{
    

    auto bounds = this->getLocalBounds();
    //auto responseArea = bounds.removeFromTop(bounds.getHeight() * 0.33);

    auto lowshelfArea = bounds.removeFromLeft(bounds.getWidth() * 0.33);
    auto lowshelfFreqArea = lowshelfArea.removeFromTop(lowshelfArea.getHeight() * 0.5);
    auto lowshelfGainArea = lowshelfArea;

    auto peakArea = bounds.removeFromLeft(bounds.getWidth() * 0.5);
    auto peakFreqArea = peakArea.removeFromTop(peakArea.getHeight() * 0.33);
    auto peakGainArea = peakArea.removeFromTop(peakArea.getHeight() * 0.5);
    auto peakBandwidthArea = peakArea;

    auto highshelfFreqArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    auto highshelfGainArea = bounds;

    this->lowshelfCutoffFrequencySlider.setBounds(lowshelfFreqArea);
    this->lowshelfGainSlider.setBounds(lowshelfGainArea);

    this->peakCenterFrequencySlider.setBounds(peakFreqArea);
    this->peakGainSlider.setBounds(peakGainArea);
    this->peakBandwidthSlider.setBounds(peakBandwidthArea);

    this->highshelfCutoffFrequencySlider.setBounds(highshelfFreqArea);
    this->highshelfGainSlider.setBounds(highshelfGainArea);
}
