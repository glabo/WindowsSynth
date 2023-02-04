#pragma once
#include <string>
#include <map>
#include "MidiNoteMap.h"
#include "Clock.h"

// Need a letter -> note map in a header file to bring in here

class NoteGenerator
{
private:
	class NoteEvent
	{
	private:
		std::string noteName = "";
		double noteFrequency = 0L;
		uint64_t triggerTime = 0L;
		// Set to -1 so that first note trig works
		uint64_t releaseTime = -1L;
	public:
		void SetName(std::string name);
		void SetFreq(double freq);
		void SetTriggerTime(std::time_t time);
		void SetReleaseTime(std::time_t time);
		bool IsNoteHeld();
		std::string GetNoteInfo();
	};

public:
	NoteGenerator() = default;

	void OnNoteTrigger(unsigned char keycode);
	void OnNoteRelease(unsigned char keycode);

	void OctaveDown();
	void OctaveUp();

	bool IsCurrentNoteHeld();
	bool IsValidNote(unsigned char keycode);

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