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

  sc::result TestingSellerSpeed::react(const event::Recv<protocol_wire::Sell> & e) {

      std::cout << "Reacting to Recv<protocol_wire::Sell> event." << std::endl;

      // update peer terms
      protocol_wire::Sell m = e.message();
      context<CBStateMachine>().peerToSellMode(m.terms(), m.index());

      // Notify client about announcement
      context<CBStateMachine>().peerAnnouncedMode();

      // remain in same state
      return discard_event();
  }

  sc::result TestingSellerSpeed::react(const event::UpdateTerms<joystream::protocol_wire::BuyerTerms> & e) {

      std::cout << "Reacting to UpdateTerms<BuyerTerms>." << std::endl;

      // update our terms
      context<CBStateMachine>().clientToBuyMode(e.terms());

      // remain in same state
      return discard_event();
  }

}
}
