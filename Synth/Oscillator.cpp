#include "Oscillator.h"

Oscillator::Oscillator(WAVE_TYPE type)
{
	waveType = type;
}

void Oscillator::TriggerNote(NoteEvent noteEvent)
{
	waveGenerator.PlayTone(waveType, noteEvent.GetFreq());
}

void Oscillator::ReleaseNote(NoteEvent noteEvent)
{
}
