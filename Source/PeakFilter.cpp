#include "PeakFilter.h"

void PeakFilter::setCenterFrequency(float centerFrequency) {
	this->centerFrequency = centerFrequency;
}

void PeakFilter::setGain(float gain) {
	this->gain = gain;
}

void PeakFilter::setBandwidth(float bandwidth) {
	this->bandwidth = bandwidth;
}

void PeakFilter::setSamplingRate(float samplingRate) {
	this->samplingRate = samplingRate;
}

void PeakFilter::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
	constexpr float PI = 3.14159265359f;
	dnBuffer.resize(buffer.getNumChannels());
	auto tan = std::tan(PI * this->bandwidth / this->samplingRate);
	auto c = (tan - 1) / (tan + 1);
	auto d = -std::cos(2 * PI * this->centerFrequency / this->samplingRate);

	const float V0 = std::pow(10.f, this->gain / 20.f);
	const float T = V0 - 1.f;

	for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
		dnBuffer[channel].resize(2, 0.f);
		auto channelSamples = buffer.getWritePointer(channel);
		for (int i = 0; i < buffer.getNumSamples(); i++) {
			const auto currSample = channelSamples[i];
			const auto allpassFilteredOutput = dnBuffer[channel][1] - c * currSample;
			dnBuffer[channel][1] = dnBuffer[channel][0] + d * (1 - c) * (currSample - allpassFilteredOutput);
			dnBuffer[channel][0] = currSample + c * allpassFilteredOutput;

			//bandpass
			//const auto filteredOutput = 0.5f * (currSample - allpassFilteredOutput);
			
			//peak
			const auto filteredOutput = currSample + T * 0.5f * (currSample - allpassFilteredOutput);

			//write back to the buffer
			channelSamples[i] = filteredOutput;
		}
	}

}
