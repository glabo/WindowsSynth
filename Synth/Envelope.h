#pragma once
#include "Clock.h"

class Envelope {
public:
	Envelope() = default;

	double calculateVolume(uint64_t triggerTime, uint64_t releaseTime);
	int getReleaseValue();
private:
	double calculateAttackVolume(uint64_t curTime);
	double calculateDecayVolume(uint64_t curTime);
	double calculateReleaseVolume(uint64_t curTime);

private:
	struct EnvelopeStruct {
		int attack = 300;			// in ms
		int decay = 1000;			// in ms
		double sustain = 0.1;	// a volume value from 1 to 0
		int release = 1000;		// in ms
	};
	EnvelopeStruct envelope;
	double previousVolume = 0.0;
	Clock clock;
};