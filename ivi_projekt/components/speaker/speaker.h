#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac.h"
#include "esp_timer.h"

#define SAMPLE_RATE       16000       // 20 kHz sample rate
#define TONE_DURATION_SEC 1         // 0.2 seconds duration
#define NUM_SAMPLES       (SAMPLE_RATE * TONE_DURATION_SEC)
#define TONE_FREQUENCY    12000       // 10 kHz tone


// Generate the sine wave samples
void generate_tone_samples(float duration);

// Timer callback to output one sample at a time
static void tone_timer_callback(void* arg);

void init_speaker(void);

void green_zone(void);

void yellow_zone(void);

void red_zone(void);