#pragma once
#include <string>
#include <map>
#include <vector>
#include "MidiNoteMap.h"
#include "Clock.h"
#include "NoteEvent.h"

class NoteEventGenerator
{
public:
	NoteEventGenerator() = default;

	void OnNoteTrigger(unsigned char keycode);
	void OnNoteRelease(unsigned char keycode);
	void TrimNotes(std::vector<std::string> trimNotes);

	void OctaveDown();
	void OctaveUp();

	bool IsValidNote(unsigned char keycode);

	std::map<std::string, NoteEvent> GetCurrentNotes();
	std::string PrintCurrentNote();

private:
	const int MIN_OCTAVE = 0;
	const int MAX_OCTAVE = 8;
	int currentOctave = 4; // C4 is middle C
	std::map<std::string, NoteEvent> curNotes;
	MidiNoteMap midiNoteMap;
	Clock Clock;
};