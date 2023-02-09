#include "SynthModule.h"

SynthModule::SynthModule(int numOscillators)
{
	for (int i = 0; i < numOscillators; i++) {
		oscillators.push_back(new Oscillator(NOISE));
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
		if (noteGenerator.IsValidNote(keycode) && !noteGenerator.IsCurrentNoteHeld()) {
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
	keycode = kbd.ReadKey().GetCode();
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
	if (noteGenerator.IsCurrentNoteHeld()) {
		double soundSample = 0.0;
		NoteEvent curNote = noteGenerator.GetCurrentNote();
		// generate sound
		for (auto osc : oscillators) {
			soundSample += osc->Generate(curNote.GetFreq(), dTime);
		}
		return soundSample;
	}
	else {
		return 0.0;
	}
}

std::string SynthModule::PrintCurrentNote()
{
	return noteGenerator.PrintCurrentNote();
}
