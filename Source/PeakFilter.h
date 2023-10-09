#pragma once
#include <vector>
#include "JuceHeader.h"

class PeakFilter {
public:
	void setCenterFrequency(float centerFrequency);
	void setGain(float gain);
	void setBandwidth(float bandwidth);
	void setSamplingRate(float samplingRate);
	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
	float centerFrequency;
	float gain;
	float bandwidth;
	float samplingRate;
	std::vector<std::vector<float>> dnBuffer;
};

