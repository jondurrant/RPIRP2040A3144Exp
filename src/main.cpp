/**
 * Jon Durrant.
 *
 * Pico Hall Effect Sensor Test
 */

#include "pico/stdlib.h"
#include <stdio.h>

#define DELAY 500 // in microseconds
#define LED_PAD  15
#define HALL_PAD 14

int onCount = 0;
int offCount =0;


void gpioIrqCallback(uint gpio, uint32_t event_mask){
	if ((event_mask & GPIO_IRQ_EDGE_FALL)> 0){
		gpio_put(LED_PAD, 1);
		onCount++;
	}

	if ((event_mask & GPIO_IRQ_EDGE_RISE)> 0){
		gpio_put(LED_PAD, 0);
		offCount++;
	}
}


int main() {
	stdio_init_all();

    gpio_init(LED_PAD);
    gpio_set_dir(LED_PAD, GPIO_OUT);
    gpio_put(LED_PAD, 1);
    sleep_ms(DELAY);
    gpio_put(LED_PAD, 0);

    gpio_init(HALL_PAD);
    gpio_set_dir(HALL_PAD, GPIO_IN);
    gpio_set_irq_enabled_with_callback(HALL_PAD,
    		GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE,
			true,
			gpioIrqCallback
    );

    while (true) { // Loop forever
    	printf("ON %d OFF %d\n", onCount, offCount);
        sleep_ms(1000);
    }

}
