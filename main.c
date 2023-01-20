#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

#include "IMU.h"
#include "flash.h"
#include "UART.h"


void main() {
    imu_init();
    
}