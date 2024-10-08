#include "NoteEventGenerator.h"
#include <iostream>

void NoteEventGenerator::OnNoteTrigger(unsigned char keycode)
{
	if (!IsValidNote(keycode)) {
		return;
	}

	NoteEvent newNote;
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);

	if (curNotes.find(midiNote) != curNotes.end() && curNotes[midiNote].GetReleaseTime() != 0) {
		curNotes.erase(curNotes.find(midiNote));
	}

	newNote.SetMidiNote(midiNote);
	std::string noteName = midiNoteMap.GetNoteName(midiNote);
	newNote.SetName(noteName);

	uint64_t curTime = Clock.GetTime();
	newNote.SetTriggerTime(curTime);
	// Reset releaseTime
	newNote.SetReleaseTime(Clock.Zero());

	curNotes.insert({midiNote, newNote});
}

void NoteEventGenerator::OnNoteRelease(unsigned char keycode)
{
	if (!IsValidNote(keycode)) {
		return;
	}

	uint64_t curTime = Clock.GetTime();
	int midiNote = midiNoteMap.KeyboardToMidiNote((int)keycode, currentOctave);
	if (curNotes.find(midiNote) != curNotes.end()) {
		curNotes[midiNote].SetReleaseTime(curTime);
	}
}

void NoteEventGenerator::TrimNotes(std::vector<int> trimNotes)
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

bool NoteEventGenerator::IsValidNote(unsigned char keycode)
{
	return midiNoteMap.IsValidNote(keycode);
}

std::map<int, NoteEvent> NoteEventGenerator::GetCurrentNotes()
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
