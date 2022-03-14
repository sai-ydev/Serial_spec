/*

    serialparser.c

*/
#include "Arduino.h"
#include "serial_parser.h"
#include "message_types.h"

// message parser parses all messages

void parse_message(void)
{
  byte rx_buffer[16];
  byte calc_crc;
  byte rec_crc;
  byte high_nib;
  byte low_nib;
  //calculate crc
  long running_total = 0;
  uint8_t rx_count = 0;

  // average message length is 3 bytes
  // without CRC
  while (Serial.available() <= 3)
    ;

  while (Serial.available() && rx_count <= 5)
  {
    rx_buffer[rx_count] = Serial.read();
    rx_count++;
  }
  // parse message according to structure
  if (rx_buffer[0] == HEADER)
  {
    running_total += rx_buffer[0];
  }
  else
  {
    transmit_message(ERROR);
    return;
  }

  if (rx_buffer[1] >= FW_VERSION && rx_buffer[1] <= TEC_CONTROL)
  {
    running_total += rx_buffer[1];
  }
  else
  {
    transmit_message(ERROR);
    return;
  }

  if (rx_buffer[1] == TEMP_MEASURE || rx_buffer[1] == TEC_CONTROL)
  {
    // TODO: Further parsing required for channel & current info
  }

  if (rx_buffer[2] == FOOTER)
  {
    running_total += rx_buffer[2];
  }
  else
  {
    transmit_message(ERROR);
    return;
  }

  high_nib = ascii_nibble_to_hex(rx_buffer[3]);
  low_nib = ascii_nibble_to_hex(rx_buffer[4]);

  calc_crc = running_total & 0xFF;
  rec_crc = ((high_nib << 4) & 0xF0) | (low_nib & 0x0F);

  if (calc_crc != rec_crc)
  {
    //TODO: Spawn message transmission as a separate task
    transmit_message(ERROR);
  }
  else
  {
    transmit_message(REQUEST_ACK);
    // TODO: spawn temperature/pH/DO tasks on scheduler
  }
}
// transmit message back to Pi
void transmit_message(uint8_t msg_type)
{
  byte tx_buffer[5];
  byte crc = (HEADER + FOOTER + msg_type) & 0xFF;

  byte high_nib = hex_nibble_to_ascii((crc & 0xF0) >> 4);
  byte low_nib = hex_nibble_to_ascii(crc & 0x0F);

  tx_buffer[0] = HEADER;
  tx_buffer[1] = msg_type;
  // TODO: Include error type or further information
  tx_buffer[2] = FOOTER;
  tx_buffer[3] = high_nib;
  tx_buffer[4] = low_nib;

  Serial.write(tx_buffer, 5);
}

uint8_t ascii_nibble_to_hex(uint8_t tmp)
{

  // convert '0' to '9'
  if (tmp <= 0x39)
  {
    tmp &= 0x0F;
  }
  else if (tmp <= 0x46)
  {
    // convert 'A' - 'F'
    tmp -= 0x37;
  }
  else
  {
    // or convert 'a' - 'f'
    tmp -= 0x57;
  }

  return (0x0F & tmp);
}

uint8_t hex_nibble_to_ascii(uint8_t tmp)
{
  tmp &= 0x0F;

  // convert to 0xA - 0xF
  if (tmp >= 10)
  {
    tmp += 55;
  }
  else
  {
    // convert 0-9 to ascii
    tmp |= 0x30;
  }

  return tmp;
}