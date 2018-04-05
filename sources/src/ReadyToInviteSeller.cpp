/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 26 2016
 */

#include <protocol_statemachine/ReadyToInviteSeller.hpp>
#include <protocol_statemachine/TestingSellerSpeed.hpp>
#include <protocol_statemachine/exception/CannotInviteNonSeller.hpp>
#include <protocol_statemachine/exception/CannotSpeedTestNonSeller.hpp>
#include <protocol_statemachine/WaitingForSellerToJoin.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    ReadyToInviteSeller::ReadyToInviteSeller() {
        std::cout << "Entering ReadyToInviteSeller state." << std::endl;
    }

    sc::result ReadyToInviteSeller::react(const event::TestSellerSpeed & test) {
      std::cout << "Reacting to TestSellerSpeed." << std::endl;

      // Make sure the peer is actually a seller, otherwise throw exception
      protocol_statemachine::AnnouncedModeAndTerms peerMode = context<CBStateMachine>().announcedModeAndTermsFromPeer();

      if(peerMode.modeAnnounced() != ModeAnnounced::sell)
          throw exception::CannotSpeedTestNonSeller();

      // Send speed test request message to seller
      auto payloadSize = test.payloadSize();
      context<CBStateMachine>()._sendSpeedTestRequestMessage(protocol_wire::SpeedTestRequest(payloadSize));

      // Record start time of test
      context<CBStateMachine>().sentSpeedTestRequest();

      // Start waiting for seller to complete test
      return transit<TestingSellerSpeed>();
    }

    sc::result ReadyToInviteSeller::react(const event::InviteSeller &) {

        std::cout << "Reacting to InviteSeller." << std::endl;

        // Make sure the peer is actually a seller, otherwise throw exception
        protocol_statemachine::AnnouncedModeAndTerms peerMode = context<CBStateMachine>().announcedModeAndTermsFromPeer();

        if(peerMode.modeAnnounced() != ModeAnnounced::sell)
            throw exception::CannotInviteNonSeller();

        // Send invitation message to seller
        context<CBStateMachine>()._sendJoinContractMessage(protocol_wire::JoinContract(peerMode.index()));

        // Start waiting for the seller to join
        return transit<WaitingForSellerToJoin>();
    }

}
}
