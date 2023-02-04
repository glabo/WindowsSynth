#pragma once
#include "WaveGenerator.h"
#include "NoteEvent.h"

class Oscillator
{
public:
	Oscillator() = default;
	Oscillator(WAVE_TYPE type);

	void TriggerNote(NoteEvent noteEvent);
	void ReleaseNote(NoteEvent noteEvent);
private:
	WaveGenerator waveGenerator;
	WAVE_TYPE waveType = SINE;
};

