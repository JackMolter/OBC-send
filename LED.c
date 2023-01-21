#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"

#include "LED.h"

void led_fade() {
    static int blue = 255;
    static int red = 0;
    static int green = 0;
    static bool going_up = true;

    gpio_set_function(LEDB, GPIO_FUNC_PWM);
    gpio_set_function(LEDG, GPIO_FUNC_PWM);
    gpio_set_function(LEDR, GPIO_FUNC_PWM);

    uint sliceb = pwm_gpio_to_slice_num(LEDB);
    uint sliceg = pwm_gpio_to_slice_num(LEDG);
    uint slicer = pwm_gpio_to_slice_num(LEDR);

    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 4.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slicer, &config, true);
    pwm_init(sliceg, &config, true);
    pwm_init(sliceb, &config, true);
;
    while(1){

        if (red > 0 && blue == 0) {
            red--;
            green++;
        }
        if ( green > 0 && red == 0) {
            green--;
            blue++;
        }
        if ( blue > 0 && green == 0) {
            red++;
            blue--;
        }

        pwm_set_gpio_level(LEDR, red * red);
        pwm_set_gpio_level(LEDG, green * green);
        pwm_set_gpio_level(LEDB, blue * blue );
        sleep_ms(10);

        printf("red: %d | green: %d | blue: %d\r\n ", red, green, blue);

    }
}
