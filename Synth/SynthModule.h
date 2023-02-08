#pragma once
#include "NoteGenerator.h"
#include "Oscillator.h"
#include "Keyboard.h"
#include "WaveTypes.h"
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
	// NoteGenerator can only handle one note at a time right now

	// Sound pipeline:
	NoteGenerator noteGenerator;
	// pitch envelope
	std::vector<Oscillator*> oscillators;
	// osc output mux
	// ADSR envelope
	// FFT --> freq domain stage
	// Filter + it's own ADSR
};

