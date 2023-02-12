#pragma once
#include <string>
#include <chrono>

class NoteEvent
{
private:
	std::string noteName = "";
	int midiNote = 0;
	uint64_t triggerTime = 0L;
	// Set to -1 so that first note trig works
	uint64_t releaseTime = -1L;
public:
	void SetName(std::string name);
	void SetMidiNote(int note);
	int GetMidiNote();
	void SetTriggerTime(std::time_t time);
	uint64_t GetTriggerTime();
	void SetReleaseTime(std::time_t time);
	uint64_t GetReleaseTime();
	bool IsNoteHeld();
	std::string GetNoteInfo();
};