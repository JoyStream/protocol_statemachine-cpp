/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#include <protocol_statemachine/event/TestSellerSpeed.hpp>

namespace joystream {
namespace protocol_statemachine {
namespace event {

    TestSellerSpeed::TestSellerSpeed(uint32_t payloadSize)
      : _payloadSize(payloadSize) {
    }

    uint32_t TestSellerSpeed::payloadSize() const {
      return _payloadSize;
    }
}
}
}
