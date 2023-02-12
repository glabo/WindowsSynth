#include "NoteEventGenerator.h"
#include <iostream>

void NoteEventGenerator::OnNoteTrigger(unsigned char keycode)
{
	NoteEvent newNote;
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);
	newNote.SetMidiNote(midiNote);
	std::string noteName = midiNoteMap.GetNoteName(midiNote);
	newNote.SetName(noteName);

	uint64_t curTime = Clock.GetTime();
	newNote.SetTriggerTime(curTime);
	// Reset releaseTime
	newNote.SetReleaseTime(Clock.Zero());

	curNotes.insert({ noteName, newNote });
}

void NoteEventGenerator::OnNoteRelease(unsigned char keycode)
{
	uint64_t curTime = Clock.GetTime();
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);
	std::string noteName = midiNoteMap.GetNoteName(midiNote);
	if (curNotes.find(noteName) != curNotes.end()) {
		curNotes[noteName].SetReleaseTime(curTime);
	}
}

void NoteEventGenerator::TrimNotes(std::vector<std::string> trimNotes)
{
	for (auto trimNote : trimNotes) {
		auto it = curNotes.find(trimNote);
		if (it != curNotes.end()) {
			curNotes.erase(it);
		}
	}
}

void NoteEventGenerator::OctaveDown()
{
	if (currentOctave > MIN_OCTAVE) {
		currentOctave--;
	}
}

void NoteEventGenerator::OctaveUp()
{
	if (currentOctave < MAX_OCTAVE) {
		currentOctave++;
	}
}

bool NoteEventGenerator::IsCurrentNoteHeld()
{
	//return curNote.IsNoteHeld();
	return false;
}

bool NoteEventGenerator::IsValidNote(unsigned char keycode)
{
	return midiNoteMap.IsValidNote(keycode);
}

std::map<std::string, NoteEvent> NoteEventGenerator::GetCurrentNotes()
{
	return curNotes;
}

std::string NoteEventGenerator::PrintCurrentNote()
{
	if (curNotes.begin() == curNotes.end()) {
		return "";
	}
	NoteEvent note = curNotes.begin()->second;
	return note.GetNoteInfo();
}
