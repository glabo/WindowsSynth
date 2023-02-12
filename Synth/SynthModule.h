#pragma once
#include "NoteEventGenerator.h"
#include "Oscillator.h"
#include "Keyboard.h"
#include "WaveTypes.h"
#include "Clock.h"
#include <vector>

class SynthModule
{
public:
	SynthModule(int numOscillators=1);
	void TriggerNote(unsigned char keycode);
	void ReleaseNote(unsigned char keycode);

	// callback for sound driver
	static double generateSoundCallback(double dTime, SynthModule* synth);
	double generateSound(double dTime);

	/************ Debug functions *************/
	std::string PrintCurrentNote();
private:
	Keyboard kbd;
	Clock clock;
	// NoteGenerator can only handle one note at a time right now

	// Sound pipeline:
	NoteEventGenerator noteGenerator;
	// pitch envelope
	std::vector<Oscillator*> oscillators;
	// Longest release time for an oscillator, for evicting notes from queue
	int maxReleaseValue = 0;
	// osc output mux
	// FFT --> freq domain stage
	// Filter + it's own ADSR
};

