/*
    message_types.h

    Definition of all message types


*/

#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#define HEADER          0x0A
#define FOOTER          0x0D

enum message_type {
    FW_VERSION = 0x01,
    PH_MEASURE,
    DO_MEASURE,
    TEMP_MEASURE,
    TEC_CONTROL,
    REQUEST_ACK,
    ERROR,
};

#endif