#include "NoteEvent.h"

void NoteEvent::SetName(std::string name)
{
	noteName = name;
}

void NoteEvent::SetMidiNote(int note)
{
	midiNote = note;
}

int NoteEvent::GetMidiNote()
{
	return midiNote;
}

void NoteEvent::SetTriggerTime(std::time_t time)
{
	triggerTime = time;
}

uint64_t NoteEvent::GetTriggerTime()
{
	return triggerTime;
}

void NoteEvent::SetReleaseTime(std::time_t time)
{
	releaseTime = time;
}

uint64_t NoteEvent::GetReleaseTime()
{
	return releaseTime;
}

bool NoteEvent::IsNoteHeld()
{
	// releaseTime == 0 when note is still held
	return releaseTime == 0;
}

std::string NoteEvent::GetNoteInfo()
{
	std::string noteTextOutput =
		"Note Name: " + noteName + "\n" +
		"Midi Note: " + std::to_string(midiNote) + "\n" +
		"Trigger time: " + std::to_string(triggerTime) + "\n" +
		"Release time: " + std::to_string(releaseTime) + "\n";
	return noteTextOutput;
}