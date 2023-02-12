#include "Oscillator.h"

Oscillator::Oscillator(WAVE_TYPE type, int coarseOffset, int fineOffset)
{
	this->waveType = type;
	this->coarseOffset = coarseOffset;
	this->fineOffset = fineOffset;
}

double Oscillator::Generate(const double dTime, NoteEvent noteInfo) {
	// Frequency Calculation
	double baseFreq = CalculateFreqForMidiNote(noteInfo.GetMidiNote() + coarseOffset);
	double freq = baseFreq + fineOffset;
	const double phase = freq * 2.0 * M_PI;
	const double dPhase = phase * dTime;

	// Attenuation Calculation
	double volume = envelope.calculateVolume(noteInfo.GetTriggerTime(), noteInfo.GetReleaseTime());
	double baseValue = 0.0;
	switch (waveType) {
	case SINE:
		baseValue = sin(dPhase);
		break;
	case SQUARE: // Square wave between -1 and +1
		baseValue = sin(dPhase) > 0 ? 1.0 : -1.0;
		break;
	case TRIANGLE: // Triangle wave between -1 and +1
		baseValue = asin(sin(dPhase)) * (2.0 / M_PI);
		break;
	case SAW_ANALOG: // Saw wave (analogue / warm / slow)
	{
		double dCustom = 50.0;
		double dOutput = 0.0;
		for (double n = 1.0; n < dCustom; n++)
			dOutput += (sin(n * dPhase)) / n;
		baseValue = dOutput * (2.0 / M_PI);
		break;
	}
	case SAW_DIGITAL:
		baseValue = (2.0 / M_PI) * (freq * M_PI * fmod(dTime, 1.0 / freq) - (M_PI / 2.0));
		break;
	case NOISE:
		baseValue = 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
		break;
	default:
		baseValue = 0.0;
	}
	return baseValue * volume;
}

double Oscillator::CalculateFreqForMidiNote(int midiNote)
{
	double freq = 440.0 * pow(2.0, (double)(midiNote - 69) / (double)12);
	return freq;
}
