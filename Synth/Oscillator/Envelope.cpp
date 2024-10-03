#include "Envelope.h"

double Envelope::calculateVolume(uint64_t triggerTime, uint64_t releaseTime)
{
	double volume = 0.0;
	// Calculate which part of the envelope we're in
	if (releaseTime == 0) {
		uint64_t timeFromTrigger = clock.GetTime() - triggerTime;
		if (timeFromTrigger < envelope.attack) {
			// attack phase
			volume = calculateAttackVolume(timeFromTrigger);
		}
		else if (timeFromTrigger < envelope.attack + envelope.decay) {
			// decay
			uint64_t curTime = timeFromTrigger - envelope.attack;
			volume = calculateDecayVolume(curTime);
		}
		else {
			// sustain phase
			volume = envelope.sustain;
		}
		previousVolume = volume;
	}
	else {
		// release phase
		uint64_t timeFromRelease = clock.GetTime() - releaseTime;
		volume = calculateReleaseVolume(timeFromRelease);
	}
	return volume;
}

int Envelope::getReleaseValue()
{
	return envelope.release;
}

double Envelope::calculateAttackVolume(uint64_t curTime)
{
	// slope from 0 to 1
	return (double)curTime / (double)envelope.attack;
}

double Envelope::calculateDecayVolume(uint64_t curTime)
{
	// slope from 1 to sustain
	double decayAttenuation = ((double)curTime / (double)envelope.decay) * (1.0 - envelope.sustain);
	return 1.0 - decayAttenuation;
}

double Envelope::calculateReleaseVolume(uint64_t curTime)
{
	// slope from sustain (or previous attn value if sustain wasn't reached..) to 0
	if (envelope.release == 0 || curTime > envelope.release) {
		return 0.0;
	}
	double releaseDecay = 1.0 - ((double)curTime / (double)envelope.release);
	return releaseDecay * previousVolume;
}
