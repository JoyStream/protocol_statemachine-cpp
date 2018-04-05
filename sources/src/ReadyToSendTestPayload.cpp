/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 26 2016
 */

 #include <protocol_statemachine/ReadyForInvitation.hpp>
 #include <protocol_statemachine/ReadyToSendTestPayload.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

  ReadyToSendTestPayload::ReadyToSendTestPayload() {
      std::cout << "Entering ReadyToSendTestPayload state." << std::endl;
  }

  sc::result ReadyToSendTestPayload::react(const event::SendTestPayload & e) {

      std::cout << "Reacting to SendTestPayload event." << std::endl;

      uint32_t payloadSize = context<CBStateMachine>()._requestedTestPayloadSize;

      context<CBStateMachine>()._sendSpeedTestPayloadMessage(protocol_wire::SpeedTestPayload(payloadSize));

      // Return to ready for invitation
      return transit<ReadyForInvitation>();
  }

}
}
