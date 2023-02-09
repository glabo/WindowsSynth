#include "SynthModule.h"

SynthModule::SynthModule(int numOscillators)
{
	for (int i = 0; i < numOscillators; i++) {
		oscillators.push_back(new Oscillator(TRIANGLE));
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
		// Fix this logic, holding a note + hitting another note resets trigger time but not note value
		if (noteGenerator.IsValidNote(keycode)) {
			noteGenerator.OnNoteTrigger(keycode);
			//keyboardInputText.SetText(noteGenerator.PrintCurrentNote());

			/*for (auto osc : oscillators) {
				osc->TriggerNote(noteGenerator.GetCurrentNote());
			}*/
		}
	}
}

void SynthModule::ReleaseNote(unsigned char keycode)
{
	kbd.OnKeyReleased(static_cast<unsigned char>(keycode));
	if (noteGenerator.IsValidNote(keycode)) {
		noteGenerator.OnNoteRelease(keycode);
	}
}

double SynthModule::generateSoundCallback(double dTime, SynthModule* synth)
{
	return synth->generateSound(dTime);
}

double SynthModule::generateSound(double dTime)
{
	std::vector<std::string> trimNotes;
	double soundSample = 0.0;
	for (auto noteEntry : noteGenerator.GetCurrentNotes()) {
		std::string noteName = noteEntry.first;
		NoteEvent noteInfo = noteEntry.second;

		uint64_t curTime = Clock.GetTime();
		uint64_t releaseTime = noteInfo.GetReleaseTime();
		uint64_t timeDiff = noteInfo.GetReleaseTime() - curTime;

		// If the release envelope is complete, remove note from currently playing notes
		if (releaseTime > 0 && timeDiff > releaseTime) {
			trimNotes.push_back(noteName);
		}
		else {
			// generate sound
			for (auto osc : oscillators) {
				soundSample += osc->Generate(noteInfo.GetFreq(), dTime);
			}
		}
	}
	noteGenerator.TrimNotes(trimNotes);
	return soundSample;
}

std::string SynthModule::PrintCurrentNote()
{
	return noteGenerator.PrintCurrentNote();
}
