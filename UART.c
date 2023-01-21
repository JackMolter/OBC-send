#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/uart.h"

#include "UART.h"

// some example data
//uint8_t data[12] = {0,1,2,3,4,5,6,7,8,9,10,11};


void uart_setup() {
    uart_init(UART_ID, UART_BAUD_RATE);     // sets baud and peripheral

    gpio_set_function(UART_TX, GPIO_FUNC_UART);     // sets pins
    gpio_set_function(UART_RX, GPIO_FUNC_UART);

    uart_set_hw_flow(UART_ID, false, false);    // flow control

    // TODO: add interrupt and DMA stuff 
    // This will be useful for the large data transfers of the OpenLST
}

// sets the pins on the OpenLST
// doesnt do anything ? 
void openlst_setup() {
    uart_init(OPENLST_UART_ID, OPENLST_UART_BAUD_RATE);

    gpio_set_function(OPENLST_UART_TX, GPIO_FUNC_UART);     // sets pins
    gpio_set_function(OPENLST_UART_RX, GPIO_FUNC_UART);

    uart_set_hw_flow(OPENLST_UART_ID, false, false);    // flow control

}

// sends a string to serial, viewable through minicom 
void uart_test() {
    //uart_putc_raw(UART_ID, 'J'); // sends a J
    //uart_putc(UART_ID, 'M');
    uart_puts(UART_ID, "Jack was here");
}

// simple test of sending and recieivng ack 
void uart_ack_test() {
    uint8_t ack_packet[9]; // initilizes and sets length of the ack packet
    uint8_t acknowledge[9];

    ack_packet[0] = OPENLST_PACKET_HEADER_1;   // always the same
    ack_packet[1] = OPENLST_PACKET_HEADER_2;   // always the same
    ack_packet[2] = 0x06;
    ack_packet[3] = 0xFF;
    ack_packet[4] = 0xFF;
    ack_packet[5] = 0x3D;   // increments up 1 each time ??
    ack_packet[6] = 0x59;
    ack_packet[7] = 0x01;
    ack_packet[8] = 0x10;   // this byte can most likely be anything 

    uart_write_blocking(UART_ID, ack_packet, 9);
    uart_read_blocking(UART_ID, acknowledge, 9);
}

// sends a packet to get some useful telemetry info back
void uart_get_telem() {
    uint8_t get_telem[9];
    uint8_t telem[87];  // length of telem message 

    get_telem[0] = OPENLST_PACKET_HEADER_1;
    get_telem[1] = OPENLST_PACKET_HEADER_2;
    get_telem[2] = 0x06;
    get_telem[3] = 0xFF;
    get_telem[4] = 0xFF;
    get_telem[5] = 0x3F;
    get_telem[6] = 0x59;
    get_telem[7] = 0x01;
    get_telem[8] = 0x17;

    uart_write_blocking(UART_ID, get_telem, 9);
    uart_read_blocking(UART_ID, telem, 87);
}

// sends the packet through the OpenLST
// needs data, length of data, HWID of destination
void send_packet(uint8_t *data, int len, int dest_hwid) {

    if (len > MAX_PAYLOAD_LEN) {
        // ?
    }

    uint8_t packet[len + 5];    // length of full packet

    // parts of the packet that are always the same
    packet[0] = OPENLST_PACKET_HEADER_1;
    packet[1] = OPENLST_PACKET_HEADER_2;
    packet[2] = len;    // length of data, not full packet
    packet[len + 3] = dest_hwid;
    packet[len + 4] = 0x18; // random? does this matter?? TODO: test

    // this loop puts the data inbetween the starting bytes and the ending bytes
    int j = 0;
    for(int i = 3; i < (len + 3); i++) {
        packet[i] = data[j];
        j++ ; 
 
    }
    // send the packet 
    uart_write_blocking(UART_ID, packet, (len + 5));    // 3 header bytes and 2 ending bytes 
}
/*
int main() {
    stdio_init_all();
    uart_setup();
    sleep_ms(50);
    openlst_setup();
    //uart_test();
    //uart_ack_test();
    //uart_get_telem();
    sleep_ms(100);
    send_packet(data,12,OPENLST_HWID);

}
*/