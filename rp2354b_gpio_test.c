#include "pico/stdlib.h"

// {out, in}
static const uint8_t k_out_pins[16] = {
    36, 34, 32, 27,
    33, 30, 31, 35,
    16, 18, 19, 17,
    14, 12, 15, 13,
};

static const uint8_t k_in_pins[16] = {
    10, 9, 11, 8,
    1, 2, 0, 3,
    20, 23, 21, 22,
    4, 6, 5, 7,
};

// RGB LED (common anode)
#define RGB_R_PIN 45
#define RGB_G_PIN 46
#define RGB_B_PIN 47

static inline bool is_switch_on(uint pin) {
    // Pull-up input: LOW means switch is pressed (ON)
    return gpio_get(pin) == 0;
}

static inline void set_common_anode_rgb(bool red_on, bool green_on, bool blue_on) {
    // Common anode LED: active LOW
    gpio_put(RGB_R_PIN, red_on ? 0 : 1);
    gpio_put(RGB_G_PIN, green_on ? 0 : 1);
    gpio_put(RGB_B_PIN, blue_on ? 0 : 1);
}

int main(void) {
    stdio_init_all();

    for (int i = 0; i < 16; ++i) {
        gpio_init(k_in_pins[i]);
        gpio_set_dir(k_in_pins[i], GPIO_IN);
        gpio_pull_up(k_in_pins[i]);

        gpio_init(k_out_pins[i]);
        gpio_set_dir(k_out_pins[i], GPIO_OUT);
        gpio_put(k_out_pins[i], 0);
    }

    gpio_init(RGB_R_PIN);
    gpio_set_dir(RGB_R_PIN, GPIO_OUT);
    gpio_init(RGB_G_PIN);
    gpio_set_dir(RGB_G_PIN, GPIO_OUT);
    gpio_init(RGB_B_PIN);
    gpio_set_dir(RGB_B_PIN, GPIO_OUT);

    set_common_anode_rgb(false, false, false);

    while (true) {
        int pressed_count = 0;

        for (int i = 0; i < 16; ++i) {
            bool on = is_switch_on(k_in_pins[i]);
            gpio_put(k_out_pins[i], on ? 1 : 0);
            if (on) {
                ++pressed_count;
            }
        }

        if (pressed_count == 1) {
            set_common_anode_rgb(true, false, false);   // Red
        } else if (pressed_count == 2) {
            set_common_anode_rgb(false, true, false);   // Green
        } else if (pressed_count == 3) {
            set_common_anode_rgb(false, false, true);   // Blue
        } else if (pressed_count >= 4) {
            set_common_anode_rgb(true, true, true);     // White
        } else {
            set_common_anode_rgb(false, false, false);  // Off
        }

        tight_loop_contents();
    }
}
