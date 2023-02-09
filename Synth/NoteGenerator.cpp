#include "NoteGenerator.h"
#include <iostream>

void NoteGenerator::OnNoteTrigger(unsigned char keycode)
{
	NoteEvent newNote;
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);
	std::string noteName = midiNoteMap.GetNoteName(midiNote);
	newNote.SetName(noteName);

	double freq = midiNoteMap.GetNoteFreq(midiNote);
	newNote.SetFreq(freq);

	uint64_t curTime = Clock.GetTime();
	newNote.SetTriggerTime(curTime);
	// Reset releaseTime
	newNote.SetReleaseTime(Clock.Zero());

	curNotes.insert({ noteName, newNote });
}

void NoteGenerator::OnNoteRelease(unsigned char keycode)
{
	uint64_t curTime = Clock.GetTime();
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);
	std::string noteName = midiNoteMap.GetNoteName(midiNote);
	if (curNotes.find(noteName) != curNotes.end()) {
		curNotes[noteName].SetReleaseTime(curTime);
	}
}

void NoteGenerator::TrimNotes(std::vector<std::string> trimNotes)
{
	for (auto trimNote : trimNotes) {
		auto it = curNotes.find(trimNote);
		if (it != curNotes.end()) {
			curNotes.erase(it);
		}
	}
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
	//return curNote.IsNoteHeld();
	return false;
}

bool NoteGenerator::IsValidNote(unsigned char keycode)
{
	return midiNoteMap.IsValidNote(keycode);
}

std::map<std::string, NoteEvent> NoteGenerator::GetCurrentNotes()
{
	return curNotes;
}

std::string NoteGenerator::PrintCurrentNote()
{
	if (curNotes.begin() == curNotes.end()) {
		return "";
	}
	NoteEvent note = curNotes.begin()->second;
	return note.GetNoteInfo();
}
