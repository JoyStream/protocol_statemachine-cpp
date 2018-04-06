/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 26 2016
 */

#include <protocol_statemachine/TestingSellerSpeed.hpp>
#include <protocol_statemachine/ReadyToInviteSeller.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

  TestingSellerSpeed::TestingSellerSpeed() {
      std::cout << "Entering TestingSellerSpeed state." << std::endl;
  }

  sc::result TestingSellerSpeed::react(const event::Recv<protocol_wire::SpeedTestPayload> & e) {

      std::cout << "Reacting to Recv<protocol_wire::SpeedTestPayload> event." << std::endl;

      context<CBStateMachine>().receivedTestPayload(e.message().payloadSize());

      // Return to ready to invite seller
      return transit<ReadyToInviteSeller>();
  }

}
}
