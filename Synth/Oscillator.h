#pragma once
#include "WaveGenerator.h"
#include "NoteEvent.h"
#include "Clock.h"
#include "AudioConstants.h"
#include "Envelope.h"

class Oscillator
{
public:
	Oscillator(WAVE_TYPE type, int coarseOffset = 0, int fineOffset = 0);
	double Generate(const double time, NoteEvent noteInfo);

	int getReleaseTime();
private:
	double CalculateFreqForMidiNote(int midiNote);

	WaveGenerator waveGenerator;
	WAVE_TYPE waveType = SINE;
	int coarseOffset = 0; // offset in midi notes/half steps
	int fineOffset = 0;  // offset in Hz

	Clock clock;
	Envelope envelope;
};

