#pragma once
#include "tsCommon.h"
#include <string>

/*
MPEG-TS packet:
`        3                   2                   1                   0  `
`      1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0  `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `
`   0 |                             Header                            | `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `
`   4 |                  Adaptation field + Payload                   | `
`     |                                                               | `
` 184 |                                                               | `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `


MPEG-TS packet header:
`        3                   2                   1                   0  `
`      1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0  `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `
`   0 |       SB      |E|S|T|           PID           |TSC|AFC|   CC  | `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `

Sync byte                    (SB ) :  8 bits
Transport error indicator    (E  ) :  1 bit
Payload unit start indicator (S  ) :  1 bit
Transport priority           (T  ) :  1 bit
Packet Identifier            (PID) : 13 bits
Transport scrambling control (TSC) :  2 bits
Adaptation field control     (AFC) :  2 bits
Continuity counter           (CC ) :  4 bits
*/


//=============================================================================================================================================================================

class xTS
{
public:
  static constexpr uint32_t TS_PacketLength  = 188;
  static constexpr uint32_t TS_HeaderLength  = 4;

  static constexpr uint32_t PES_HeaderLength = 6;

  static constexpr uint32_t BaseClockFrequency_Hz         =    90000; //Hz
  static constexpr uint32_t ExtendedClockFrequency_Hz     = 27000000; //Hz
  static constexpr uint32_t BaseClockFrequency_kHz        =       90; //kHz
  static constexpr uint32_t ExtendedClockFrequency_kHz    =    27000; //kHz
  static constexpr uint32_t BaseToExtendedClockMultiplier =      300;
};

//=============================================================================================================================================================================

class xTS_PacketHeader
{
protected:
  uint8_t m_SB;       // Sync Byte (8 bits)
  uint8_t m_E : 1;    // Transport Error Indicator (1 bit)
  uint8_t m_S : 1;    // Payload Unit Start Indicator (1 bit)
  uint8_t m_T : 1;    // Transport Priority (1 bit)
  uint16_t m_PID : 13; // Packet Identifier (13 bits)
  uint8_t m_TSC : 2;  // Transport Scrambling Control (2 bits)
  uint8_t m_AFC : 2;  // Adaptation Field Control (2 bits)
  uint8_t m_CC : 4;   // Continuity Counter (4 bits)

public:
  void Reset()
  {
    m_SB = 0;
    m_E = 0;
    m_S = 0;
    m_T = 0;
    m_PID = 0;
    m_TSC = 0;
    m_AFC = 0;
    m_CC = 0;
  }

  int32_t Parse(const uint8_t* Input)
  {
    if (Input == nullptr) return -1; // Błąd jeśli dane wejściowe są puste

    m_SB = Input[0]; // Sync Byte
    m_E  = (Input[1] >> 7) & 0x01;
    m_S  = (Input[1] >> 6) & 0x01;
    m_T  = (Input[1] >> 5) & 0x01;
    m_PID = ((Input[1] & 0x1F) << 8) | Input[2];
    m_TSC = (Input[3] >> 6) & 0x03;
    m_AFC = (Input[3] >> 4) & 0x03;
    m_CC = Input[3] & 0x0F;

    return 0; // Sukces
  }

  void Print() const
  {
    printf("Sync Byte: 0x%02X\n", m_SB);
    printf("Transport Error Indicator: %d\n", m_E);
    printf("Payload Unit Start Indicator: %d\n", m_S);
    printf("Transport Priority: %d\n", m_T);
    printf("PID: 0x%X\n", m_PID);
    printf("Transport Scrambling Control: 0x%X\n", m_TSC);
    printf("Adaptation Field Control: 0x%X\n", m_AFC);
    printf("Continuity Counter: 0x%X\n", m_CC);
  }
};


//=============================================================================================================================================================================
