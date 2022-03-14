/*
    serial_parser.h

    Definition of function prototypes for parsing


*/
#ifndef SERIAL_PARSER
#define SERIAL_PARSER

#include <stdint.h>

void parse_message(void);
void transmit_message(uint8_t error);
uint8_t ascii_nibble_to_hex(uint8_t tmp);
uint8_t hex_nibble_to_ascii(uint8_t tmp);

#endif