#pragma once
#include <string>
#include <map>

class MidiNoteMap {
	// Piano key range: 88 notes, A0 (21) to C8 (108), 
private:
	const int NOTES_IN_OCTAVE = 12;

	// Keyboard Layout:
	// https://i.stack.imgur.com/iJ4XT.png
	/*
	* a - C
	* w - C#
	* s - D
	* e - D#
	* d - E
	* f - F
	* t - F#
	* g - G
	* y - G#
	* h - A
	* u - A#
	* j - B
	* k - C+1
	* o - C#+1
	* l - D+1
	* p - D#+1
	* ; - E+1
	* ' - F+1
	*/

	// Translates computer keyboard input into midi notes
	std::map<unsigned char,int> keyCodeToNoteOffset = {
		{0x41, 0},
		{0x57, 1},
		{0x53, 2},
		{0x45, 3},
		{0x44, 4}, // d
		{0x46, 5},
		{0x54, 6},
		{0x47, 7}, //g
		{0x59, 8},
		{0x48, 9},
		{0x55, 10},
		{0x4a, 11},
		{0x4b, 12}, // K, new octave
		{0x4f, 13},
		{0x4c, 14},
		{0x50, 15}, // p
		{0xBA, 16}, //;, VK_OEM_1
		{0xDE, 17}, // ', VK_OEM_7
	};

	std::map<int, std::string> offsetToNoteName = {
		{0, "C"},
		{1, "C#"},
		{2, "D"},
		{3, "D#"},
		{4, "E"},
		{5, "F"},
		{6, "F#"},
		{7, "G"},
		{8, "G#"},
		{9, "A"},
		{10, "A#"},
		{11, "B"},
	};

public:
	std::string GetNoteName(int midiNote) {
		std::string baseNoteName = offsetToNoteName[midiNote % NOTES_IN_OCTAVE];
		std::string octaveStr = std::to_string((midiNote / NOTES_IN_OCTAVE) - 1);
		return baseNoteName.append(octaveStr);
	}

	bool IsValidNote(unsigned char keyCode) {
		return keyCodeToNoteOffset.find(keyCode) != keyCodeToNoteOffset.end();
	}

	int KeyboardToMidiNote(unsigned char keyCode, int octave) {
		int offset = keyCodeToNoteOffset[keyCode];
		int midiNote = ((octave+1)*12) + offset;
		return midiNote;
	}

	double GetNoteFreq(int midiNote) {
		double freq = 440.0 * pow(2.0, (double)(midiNote - 69) / (double)12);
		return freq;
	}
};