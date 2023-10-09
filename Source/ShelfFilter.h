#pragma once
#include <vector>
#include "JuceHeader.h"

enum ShelfFilterKind {
	low=0,
	high=1
};

class ShelfFilter{
//6dB/D
public:
	ShelfFilter(ShelfFilterKind kind) :kind(kind) {};
	void setCutoffFrequency(float cutoffFrequency);
	void setGain(float gain);
	void setSamplingRate(float samplingRate);
	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);
private:
	const ShelfFilterKind kind;
	float cutoffFrequency;
	float gain;
	float samplingRate;
	std::vector<float> dnBuffer;
};

