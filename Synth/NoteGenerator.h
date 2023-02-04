#pragma once
#include <string>
#include <map>
#include "MidiNoteMap.h"
#include "Clock.h"
#include "NoteEvent.h"

// Need a letter -> note map in a header file to bring in here

class NoteGenerator
{
public:
	NoteGenerator() = default;

	void OnNoteTrigger(unsigned char keycode);
	void OnNoteRelease(unsigned char keycode);

	void OctaveDown();
	void OctaveUp();

	bool IsCurrentNoteHeld();
	bool IsValidNote(unsigned char keycode);

	NoteEvent GetCurrentNote();
	std::string PrintCurrentNote();

private:
	const int MIN_OCTAVE = 0;
	const int MAX_OCTAVE = 8;
	int currentOctave = 4; // C4 is middle C
	//std::map<int, NoteEvent> curNote[88]; // map of currently playing notes, future improvement
	NoteEvent curNote;
	MidiNoteMap midiNoteMap;
	Clock Clock;
};