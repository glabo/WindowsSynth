#include "Oscillator.h"

Oscillator::Oscillator(WAVE_TYPE type)
{
	waveType = type;
}

double Oscillator::Generate(const double dTime, double freq) {

	const double phase = freq * 2.0 * M_PI;
	switch (waveType) {
	case SINE:
		return sin(phase * dTime);
	}
}
