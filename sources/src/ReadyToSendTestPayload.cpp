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

  sc::result ReadyToSendTestPayload::react(const event::UpdateTerms<protocol_wire::SellerTerms> & e) {

      std::cout << "Reacting to UpdateTerms<SellerTerms>." << std::endl;

      // Update our terms
      context<CBStateMachine>().clientToSellMode(e.terms(), 1 + context<CBStateMachine>()._index);

      // Remain in same state
      return discard_event();
  }

  sc::result ReadyToSendTestPayload::react(const event::Recv<protocol_wire::Buy> & e) {

      std::cout << "Reacting to Recv<protocol_wire::Buy> event." << std::endl;

      // Update the buyer's terms
      context<CBStateMachine>().peerToBuyMode(e.message().terms());

      // Notify client about announcement
      context<CBStateMachine>().peerAnnouncedMode();

      // remain in same state
      return discard_event();
  }

}
}
