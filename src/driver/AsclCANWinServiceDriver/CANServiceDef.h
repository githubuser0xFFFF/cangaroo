#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace CANServiceCommon
{

/// @brief socket address of the windows service
const char * const ServiceAddr = "127.0.0.1";

/// @brief socket port of the windows service
const std::uint16_t ServicePort = 2223;

/// @brief CAN message
typedef struct
{
    std::uint32_t id;
    std::uint8_t size;
    // std::uint8_t reserved[3];
    std::uint8_t data[8];
} CANMessage;

typedef std::array<std::uint8_t, 16> CanMsgBytes;

/// @brief serialize CAN message to bytes
/// @param canMsg input message
/// @param data output binary data
inline void pack(const CANMessage & canMsg, CanMsgBytes & data)
{
    std::fill_n(data.begin(), data.size(), 0);
    memcpy(data.data(), &canMsg, 13);
}
} // namespace CANServiceCommon
