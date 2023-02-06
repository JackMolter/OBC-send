// This file will hold any commands we want to send from the ground station to the OpenLST
// This file could probably be combined with UART.c and renamed OpenLST
// All of this assumes that addind the header bytes and hwid to a set of data tells the OpenLST that it should
// transmitted. TODO: confirm this 

// to test: when a packet is sent over OpenLST are the header and ending bytes included in the UART RX packet??
// example does 0x22 0x69 0x03 0x01 0x02 0x03 0x01 0x17 --> 0x01 0x02 0x03 ???? 

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "settings.h"
#include "commands.h"

// More thought into this functions use needs to be done
void get_command() {

}


// start here then improve upon
// assumes that FIFO has been enabled, and some data has been found in the TX fifo
void get_command_simple() {
    uint8_t com[1];

    if(uart_is_readable != 0) { // if there exists data in the fifo
        //uart_read_blocking(uart0, )
    }

    

}

