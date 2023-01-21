// Get accelerometer reading, copys the data to flash, reads the flash, sends the data to the OpenLST, infinite loop

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

uint32_t target_addr = 0;   // for simplicity 
uint8_t imu[6];


void main() {
    // initilize all 
    imu_init();
    flash_setup(FLASH_CS);
    uart_setup();
    openlst_setup();
    sleep_ms(100);

    while(1) {
        // get accelerometer values 
        get_accel();
        sleep_ms(50);

        // flash 
        flash_write_data( target_addr, imu, ACCEL_DATA_LEN);    // writes accel data to a section in flash memory
        sleep_ms(50);
        flash_read_data(target_addr, dat, ACCEL_DATA_LEN);      // reads the flash data
        sleep_ms(50);

        // UART
        send_packet(dat, ACCEL_DATA_LEN, OPENLST_HWID);     // sends the data to the OpenLST 

        // erase of flash not needed for this since flash memory address isnt changing
        flash_erase_4k(target_addr);        // erase flash data 
        sleep_ms(300);
    }

}