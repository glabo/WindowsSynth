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

std::string NoteGenerator::PrintCurrentNote()
{
	return curNote.GetNoteInfo();
}

void NoteGenerator::NoteEvent::SetName(std::string name)
{
	noteName = name;
}

void NoteGenerator::NoteEvent::SetFreq(double freq)
{
	noteFrequency = freq;
}

void NoteGenerator::NoteEvent::SetTriggerTime(std::time_t time)
{
	triggerTime = time;
}

void NoteGenerator::NoteEvent::SetReleaseTime(std::time_t time)
{
	releaseTime = time;
}

bool NoteGenerator::NoteEvent::IsNoteHeld()
{
	// releaseTime == 0 when note is still held
	return releaseTime == 0;
}

std::string NoteGenerator::NoteEvent::GetNoteInfo()
{
	std::string noteTextOutput =
		"Note Name: " + noteName + "\n" +
		"Note Freq: " + std::to_string(noteFrequency) + "\n" +
		"Trigger time: " + std::to_string(triggerTime) + "\n" +
		"Release time: " + std::to_string(releaseTime) + "\n";
	return noteTextOutput;
}
