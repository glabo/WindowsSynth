#include "Oscillator.h"

Oscillator::Oscillator(WAVE_TYPE type)
{
	waveType = type;
}

double Oscillator::Generate(const double dTime, double freq) {

	const double phase = freq * 2.0 * M_PI;
	const double dPhase = phase * dTime;
	switch (waveType) {
	case SINE:
		return sin(dPhase);
	case SQUARE: // Square wave between -1 and +1
		return sin(dPhase) > 0 ? 1.0 : -1.0;

	case TRIANGLE: // Triangle wave between -1 and +1
		return asin(sin(dPhase)) * (2.0 / M_PI);

	case SAW_ANALOG: // Saw wave (analogue / warm / slow)
	{
		double dCustom = 50.0;
		double dOutput = 0.0;
		for (double n = 1.0; n < dCustom; n++)
			dOutput += (sin(n * dPhase)) / n;
		return dOutput * (2.0 / M_PI);
	}
	case SAW_DIGITAL:
		return (2.0 / M_PI) * (freq * M_PI * fmod(dTime, 1.0 / freq) - (M_PI / 2.0));

	case NOISE:
		return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;

	default:
		return 0.0;
	}
}
