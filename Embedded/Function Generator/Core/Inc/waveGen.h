#ifndef WAVEGEN_H
#define WAVEGEN_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"

#define SAMPLES 500
#define PI 3.14159265F

extern uint32_t wave_lut[SAMPLES];

void sinWave();
void squareWave();
void triangleWave();
void sawtoothWave();

bool wave_freq(uint16_t frequency);


#endif // WAVEGEN_H