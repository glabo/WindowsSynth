#include "NoteGenerator.h"
#include <iostream>

void NoteGenerator::OnNoteTrigger(unsigned char keycode)
{
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);
	std::string noteName = midiNoteMap.GetNoteName(midiNote);
	curNote.SetName(noteName);

	double freq = midiNoteMap.GetNoteFreq(midiNote);
	curNote.SetFreq(freq);

	uint64_t curTime = Clock.GetTime();
	curNote.SetTriggerTime(curTime);
	// Reset releaseTime
	curNote.SetReleaseTime(Clock.Zero());
}

void NoteGenerator::OnNoteRelease(unsigned char keycode)
{
	uint64_t curTime = Clock.GetTime();
	curNote.SetReleaseTime(curTime);
}

void NoteGenerator::OctaveDown()
{
	if (currentOctave > MIN_OCTAVE) {
		currentOctave--;
	}
}

void NoteGenerator::OctaveUp()
{
	if (currentOctave < MAX_OCTAVE) {
		currentOctave++;
	}
}

bool NoteGenerator::IsCurrentNoteHeld()
{
	return curNote.IsNoteHeld();
}

bool NoteGenerator::IsValidNote(unsigned char keycode)
{
	return midiNoteMap.IsValidNote(keycode);
}

NoteEvent NoteGenerator::GetCurrentNote()
{
	return curNote;
}

std::string NoteGenerator::PrintCurrentNote()
{
	return curNote.GetNoteInfo();
}
