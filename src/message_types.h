/*
    message_types.h

    Definition of all message types


*/

#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#define HEADER          0x0A
#define FOOTER          0x0D

#define ERROR           0x09

#define FW_VERSION      0x01
#define TEMP_MEASURE    0x02
#define PH_MEASURE      0x03
#define DO_MEASURE      0x04
#define TEC_CONTROL     0x05
#define REQUEST_ACK     0x0B

#endif