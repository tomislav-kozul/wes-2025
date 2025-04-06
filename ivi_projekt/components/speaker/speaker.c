#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac.h"
#include "esp_timer.h"

#include "speaker.h"

uint8_t tone_samples[(int)NUM_SAMPLES];
volatile int idx = 0;
esp_timer_handle_t tone_timer;

// Generate the sine wave samples
void generate_tone_samples(float duration) {
    int num_samples = (int)(duration * SAMPLE_RATE);
    for (int i = 0; i < num_samples; i++) {
        double t = (double)i / SAMPLE_RATE;  // time in seconds
        double sine_val = sin(2 * M_PI * TONE_FREQUENCY * t);
        // Scale sine wave (-1 to 1) to DAC range (0 to 255)
        tone_samples[i] = (uint8_t)(128 + 127 * sine_val);
    }
}

// Timer callback to output one sample at a time
static void tone_timer_callback(void* arg) {
    // Output the current sample to the DAC
    dac_output_voltage(DAC_CHANNEL_1, tone_samples[idx]);
    idx++;
    if (idx >= NUM_SAMPLES) {
        // Stop the timer once all samples are played
        esp_timer_stop(tone_timer);
        idx = 0; // reset if you wish to play it again later
    }
}

void init_speaker() {
    // Enable DAC channel
    dac_output_enable(DAC_CHANNEL_1);
    
    // Generate the tone samples
    generate_tone_samples(1);
    
    //Create and start a one-shot periodic timer at 50 µs intervals (20kHz)
    const esp_timer_create_args_t timer_args = {
        .callback = tone_timer_callback,
        .name = "tone_timer"
    };
    esp_timer_create(&timer_args, &tone_timer);
    esp_timer_start_periodic(tone_timer, 50);  // period in microseconds

    //Optional: keep the main task running until the tone is finished
    vTaskDelay(300 / portTICK_PERIOD_MS);
}

void green_zone(void) {
    generate_tone_samples(0.2);
    const esp_timer_create_args_t timer_args = {
        .callback = tone_timer_callback,
        .name = "tone_timer"
    };
    esp_timer_create(&timer_args, &tone_timer);
    esp_timer_start_periodic(tone_timer, 50);
}

void yellow_zone(void) {
    generate_tone_samples(0.3);
    const esp_timer_create_args_t timer_args = {
        .callback = tone_timer_callback,
        .name = "tone_timer"
    };
    esp_timer_create(&timer_args, &tone_timer);
    esp_timer_start_periodic(tone_timer, 50);
}

void red_zone(void) {
    generate_tone_samples(0.1);
    const esp_timer_create_args_t timer_args = {
        .callback = tone_timer_callback,
        .name = "tone_timer"
    };
    esp_timer_create(&timer_args, &tone_timer);
    esp_timer_start_periodic(tone_timer, 50);
}