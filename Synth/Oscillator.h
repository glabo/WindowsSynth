#pragma once
#include "WaveGenerator.h"
#include "NoteEvent.h"
#include "Clock.h"
#include "AudioConstants.h"

class Oscillator
{
public:
	Oscillator(WAVE_TYPE type);
	double Generate(const double time, double freq);
private:
	WaveGenerator waveGenerator;
	WAVE_TYPE waveType = SINE;
};

