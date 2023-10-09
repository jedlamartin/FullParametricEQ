#include "ShelfFilter.h"

void ShelfFilter::setCutoffFrequency(float cutoffFrequency){
	this->cutoffFrequency = cutoffFrequency;
}

void ShelfFilter::setGain(float gain){
	this->gain = gain;
}

void ShelfFilter::setSamplingRate(float samplingRate){
	this->samplingRate = samplingRate;
}

void ShelfFilter::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
	constexpr float PI = 3.14159265359f;
	dnBuffer.resize(buffer.getNumChannels(), 0.f);

	const float tan= std::tan(PI * this->cutoffFrequency / this->samplingRate);
	float V0, H0, c;
	const float sign = this->kind == low ? 1.f : -1.f;

	switch (this->kind) {
	case low:
		V0 = std::pow(10.f, this->gain / 20.f);
		H0 = V0 - 1;
		c = this->gain >= 0 ? (tan - 1.f) / (tan + 1.f) : (tan - V0) / (tan + V0);
		break;
	case high:
		V0 = std::pow(10.f, this->gain / 20.f);
		H0 = V0 - 1;
		c = this->gain >= 0 ? (tan - 1.f) / (tan + 1.f) : (V0*tan - 1) / (V0*tan + 1);
		//c = (tan - 1.f) / (tan + 1.f);
		break;
	}
	
	//auto tan = std::tan(PI * this->cutoffFrequency / this->samplingRate);
	

	//const float V0 = std::pow(10.f, this->gain / 20.f);
	//const float B = V0 - 1;
	//const float c = this->gain >= 0 ? (tan - 1.f) / (tan + 1.f) : (tan - V0) / (tan + V0);


	for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
		auto channelSamples = buffer.getWritePointer(channel);
		for (int i = 0; i < buffer.getNumSamples(); i++) {
			const auto currSample = channelSamples[i];
			const auto allpassFilteredOutput = c * currSample + dnBuffer[channel];
			dnBuffer[channel] = currSample - c * allpassFilteredOutput;
			const auto filteredOutput = currSample + H0 * 0.5f * (currSample + sign * allpassFilteredOutput);

			//LP/HP:
			//const auto filteredOutput = 0.5f*(currSample + sign * allpassFilteredOutput);
			
			//write back to the buffer;
			channelSamples[i] = filteredOutput;


		}
	}

	

}


