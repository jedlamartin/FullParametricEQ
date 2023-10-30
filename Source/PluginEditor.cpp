/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FullParametricEQAudioProcessorEditor::FullParametricEQAudioProcessorEditor (FullParametricEQAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState (vts), 
    lowshelfCutoffFrequency(vts, juce::String("lowshelfCutoffFrequency"), juce::String("Hz")), 
    lowshelfGain(vts, juce::String("lowshelfGain"), juce::String("dB")), 
    highshelfCutoffFrequency(vts, juce::String("highshelfCutoffFrequency"), juce::String("Hz")),
    highshelfGain(vts, juce::String("highshelfGain"), juce::String("dB")),
    peakLCenterFrequency(vts, juce::String("peakLCenterFrequency"), juce::String("Hz")),
    peakLGain(vts, juce::String("peakLGain"), juce::String("dB")),
    peakLQuality(vts, juce::String("peakLBandwidth"), juce::String("")),
    peakMCenterFrequency(vts, juce::String("peakMCenterFrequency"), juce::String("Hz")),
    peakMGain(vts, juce::String("peakMGain"), juce::String("dB")),
    peakMQuality(vts, juce::String("peakMBandwidth"), juce::String("")),
    peakHCenterFrequency(vts, juce::String("peakHCenterFrequency"), juce::String("Hz")),
    peakHGain(vts, juce::String("peakHGain"), juce::String("dB")),
    peakHQuality(vts, juce::String("peakHBandwidth"), juce::String(""))

{
    addAndMakeVisible(lowshelfCutoffFrequency);
    addAndMakeVisible(lowshelfGain);
    addAndMakeVisible(highshelfCutoffFrequency);
    addAndMakeVisible(highshelfGain);
    addAndMakeVisible(peakLCenterFrequency);
    addAndMakeVisible(peakLGain);
    addAndMakeVisible(peakLQuality);
    addAndMakeVisible(peakMCenterFrequency);
    addAndMakeVisible(peakMGain);
    addAndMakeVisible(peakMQuality);
    addAndMakeVisible(peakHCenterFrequency);
    addAndMakeVisible(peakHGain);
    addAndMakeVisible(peakHQuality);

    //setLookAndFeel(&this->lookAndFeel);

    //Lowshelf
    //lowshelfCutoffFrequencyLabel.setText("Lowshelf Cutoff Frequency", juce::dontSendNotification);
    //addAndMakeVisible(lowshelfCutoffFrequencyLabel);

    /*addAndMakeVisible(lowshelfCutoffFrequencySlider);
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


    //PeakL
    addAndMakeVisible(peakLCenterFrequencySlider);
    this->peakLCenterFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakLCenterFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakLCenterFrequencyAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakLCenterFrequency", peakLCenterFrequencySlider));

    addAndMakeVisible(peakLGainSlider);
    this->peakLGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakLGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakLGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakLGain", peakLGainSlider));

    addAndMakeVisible(peakLBandwidthSlider);
    this->peakLBandwidthSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakLBandwidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakLBandwidthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakLBandwidth", peakLBandwidthSlider));

    //PeakM
    addAndMakeVisible(peakMCenterFrequencySlider);
    this->peakMCenterFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakMCenterFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakMCenterFrequencyAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakMCenterFrequency", peakMCenterFrequencySlider));

    addAndMakeVisible(peakMGainSlider);
    this->peakMGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakMGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakMGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakMGain", peakMGainSlider));

    addAndMakeVisible(peakMBandwidthSlider);
    this->peakMBandwidthSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakMBandwidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakMBandwidthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakMBandwidth", peakMBandwidthSlider));

    //PeakH
    addAndMakeVisible(peakHCenterFrequencySlider);
    this->peakHCenterFrequencySlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakHCenterFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakHCenterFrequencyAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakHCenterFrequency", peakHCenterFrequencySlider));

    addAndMakeVisible(peakHGainSlider);
    this->peakHGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakHGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakHGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakHGain", peakHGainSlider));

    addAndMakeVisible(peakHBandwidthSlider);
    this->peakHBandwidthSlider.setSliderStyle(juce::Slider::RotaryHorizontalDrag);
    this->peakHBandwidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    this->peakHBandwidthAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peakHBandwidth", peakHBandwidthSlider));

    */

    //setSize(paramSliderWidth + paramLabelWidth, juce::jmax(100, paramControlHeight * 2));

    setSize (600, 400);
}

FullParametricEQAudioProcessorEditor::~FullParametricEQAudioProcessorEditor(){
    this->setLookAndFeel(nullptr);
}

//==============================================================================
void FullParametricEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


    g.fillAll(juce::Colour(0, 0, 0));

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

    auto lowshelfArea = bounds.removeFromLeft(bounds.getWidth() * 0.2);
    auto lowshelfFreqArea = lowshelfArea.removeFromTop(lowshelfArea.getHeight() * 0.5);
    auto lowshelfGainArea = lowshelfArea;

    auto peakArea = bounds.removeFromLeft(bounds.getWidth() * 0.75);
    auto peakLArea = peakArea.removeFromLeft(peakArea.getWidth() * 0.33);
    auto peakLFreqArea = peakLArea.removeFromTop(peakLArea.getHeight() * 0.33);
    auto peakLGainArea = peakLArea.removeFromTop(peakLArea.getHeight() * 0.5);
    auto peakLBandwidthArea = peakLArea;

    auto peakMArea = peakArea.removeFromLeft(peakArea.getWidth() * 0.5);
    auto peakMFreqArea = peakMArea.removeFromTop(peakMArea.getHeight() * 0.33);
    auto peakMGainArea = peakMArea.removeFromTop(peakMArea.getHeight() * 0.5);
    auto peakMBandwidthArea = peakMArea;

    auto peakHArea = peakArea;
    auto peakHFreqArea = peakHArea.removeFromTop(peakHArea.getHeight() * 0.33);
    auto peakHGainArea = peakHArea.removeFromTop(peakHArea.getHeight() * 0.5);
    auto peakHBandwidthArea = peakHArea;
    
    /*auto peakFreqArea = peakArea.removeFromTop(peakArea.getHeight() * 0.33);
    auto peakGainArea = peakArea.removeFromTop(peakArea.getHeight() * 0.5);
    auto peakBandwidthArea = peakArea;*/

    auto highshelfFreqArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    auto highshelfGainArea = bounds;

    this->lowshelfCutoffFrequency.setBounds(lowshelfFreqArea);
    this->lowshelfGain.setBounds(lowshelfGainArea);

    this->peakLCenterFrequency.setBounds(peakLFreqArea);
    this->peakLGain.setBounds(peakLGainArea);
    this->peakLQuality.setBounds(peakLBandwidthArea);

    this->peakMCenterFrequency.setBounds(peakMFreqArea);
    this->peakMGain.setBounds(peakMGainArea);
    this->peakMQuality.setBounds(peakMBandwidthArea);

    this->peakHCenterFrequency.setBounds(peakHFreqArea);
    this->peakHGain.setBounds(peakHGainArea);
    this->peakHQuality.setBounds(peakHBandwidthArea);

    this->highshelfCutoffFrequency.setBounds(highshelfFreqArea);
    this->highshelfGain.setBounds(highshelfGainArea);
    /*this->lowshelfCutoffFrequencySlider.setBounds(lowshelfFreqArea);
    this->lowshelfGainSlider.setBounds(lowshelfGainArea);

    this->peakLCenterFrequencySlider.setBounds(peakLFreqArea);
    this->peakLGainSlider.setBounds(peakLGainArea);
    this->peakLBandwidthSlider.setBounds(peakLBandwidthArea);

    this->peakMCenterFrequencySlider.setBounds(peakMFreqArea);
    this->peakMGainSlider.setBounds(peakMGainArea);
    this->peakMBandwidthSlider.setBounds(peakMBandwidthArea);

    this->peakHCenterFrequencySlider.setBounds(peakHFreqArea);
    this->peakHGainSlider.setBounds(peakHGainArea);
    this->peakHBandwidthSlider.setBounds(peakHBandwidthArea);

    this->highshelfCutoffFrequencySlider.setBounds(highshelfFreqArea);
    this->highshelfGainSlider.setBounds(highshelfGainArea);*/
}

void LookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) {
    
    //auto outline = juce::Colour(66,108,125);    
    auto fill = juce::Colour(12, 219, 237);
    //auto fill = juce::Colour(85, 196, 232);
    auto outline = juce::Colour(57, 120, 125);

    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(15);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;
    
    //216.00002 503.999987

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(outline);
    g.strokePath(backgroundArc, juce::PathStrokeType(5.f));

    if (slider.isEnabled()) {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, toAngle, true);

        g.setColour(fill);
       // g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        g.strokePath(valueArc, juce::PathStrokeType(5.f));
    }
    
    juce::Path pointer;
    pointer.addRectangle(bounds.getCentreX(), bounds.getCentreY()-radius/5*4+lineW, 2.f, -radius / 5);
    pointer.applyTransform(juce::AffineTransform::rotation(toAngle, bounds.getCentreX(), bounds.getCentreY()));
    //pointer.applyTransform(juce::AffineTransform::rotation(toAngle+(rotaryEndAngle-juce::float_Pi/2), bounds.getCentreX(), bounds.getCentreY()));
    g.setColour(juce::Colours::white);
    g.fillPath(pointer);
}

RotarySliderWithLabels::RotarySliderWithLabels(juce::AudioProcessorValueTreeState& vts, juce::String& paramID, juce::String& suffix) :juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalDrag, NoTextBox), suffix(suffix) {
    this->param.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, paramID, *this));
    setLookAndFeel(&lookAndFeel);
}

void RotarySliderWithLabels::paint(juce::Graphics& g) {
    auto startAngle = juce::degreesToRadians(180.f + 45.f);
    auto endAngle = juce::degreesToRadians(180.f - 45.f) + 2 * juce::float_Pi;
    auto range = this->getRange();

    g.setColour(juce::Colours::red);
    g.drawRect(getLocalBounds());




    this->lookAndFeel.drawRotarySlider(g, this->getLocalBounds().getX(), this->getLocalBounds().getY(), this->getLocalBounds().getWidth(), this->getLocalBounds().getHeight(), juce::jmap(this->getValue(), this->getRange().getStart(), this->getRange().getEnd(), 0.0, 1.0), startAngle, endAngle, *this);
}


