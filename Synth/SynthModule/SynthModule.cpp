#include "SynthModule.h"

SynthModule::SynthModule(int numOscillators)
{
	for (int i = 0; i < numOscillators; i++) {
		//oscillators.push_back(new Oscillator(TRIANGLE));
		oscillators.push_back(new Oscillator(SINE));
		oscillators.push_back(new Oscillator(SQUARE, 12, 1));
	}

	for (auto osc : oscillators) {
		maxReleaseValue = std::max(maxReleaseValue, osc->getReleaseTime());
	}
}

void SynthModule::TriggerNote(unsigned char keycode)
{
	kbd.OnKeyPressed(static_cast<unsigned char>(keycode));
	switch (keycode) {
	case 0x5a:
		noteGenerator.OctaveDown();
		break;
	case 0x58:
		noteGenerator.OctaveUp();
		break;
	default:
		noteGenerator.OnNoteTrigger(keycode);
	}
}

void SynthModule::ReleaseNote(unsigned char keycode)
{
	kbd.OnKeyReleased(static_cast<unsigned char>(keycode));
	noteGenerator.OnNoteRelease(keycode);
}

double SynthModule::generateSoundCallback(double dTime, SynthModule* synth)
{
	return synth->generateSound(dTime);
}

double SynthModule::generateSound(double dTime)
{
	std::vector<int> trimNotes;
	double soundSample = 0.0;
	for (auto noteEntry : noteGenerator.GetCurrentNotes()) {
		int midiNote = noteEntry.first;
		NoteEvent noteInfo = noteEntry.second;

		uint64_t releaseTime = noteInfo.GetReleaseTime();
		uint64_t timeSinceRelease = clock.GetTime() - releaseTime;

		// If the release envelope is complete, remove note from currently playing notes
		if (releaseTime > 0 && timeSinceRelease > maxReleaseValue) {
			trimNotes.push_back(midiNote);
		}
		// generate sound
		for (auto osc : oscillators) {
			// assumes all osc's have same volume
			soundSample += (osc->Generate(dTime, noteInfo)) / (double)oscillators.size();
		}
	}
	noteGenerator.TrimNotes(trimNotes);
	return soundSample;
}

std::string SynthModule::PrintCurrentNote()
{
	return noteGenerator.PrintCurrentNote();
}
