#include "NoteEvent.h"

void NoteEvent::SetName(std::string name)
{
	noteName = name;
}

void NoteEvent::SetFreq(float freq)
{
	noteFrequency = freq;
}

float NoteEvent::GetFreq()
{
	return noteFrequency;
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

bool NoteEvent::IsNoteHeld()
{
	// releaseTime == 0 when note is still held
	return releaseTime == 0;
}

std::string NoteEvent::GetNoteInfo()
{
	std::string noteTextOutput =
		"Note Name: " + noteName + "\n" +
		"Note Freq: " + std::to_string(noteFrequency) + "\n" +
		"Trigger time: " + std::to_string(triggerTime) + "\n" +
		"Release time: " + std::to_string(releaseTime) + "\n";
	return noteTextOutput;
}