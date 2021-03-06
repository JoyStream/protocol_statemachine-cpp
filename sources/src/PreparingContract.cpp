/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 29 2016
 */

#include <protocol_statemachine/PreparingContract.hpp>
#include <protocol_statemachine/RequestingPieces.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    PreparingContract::PreparingContract() {
        std::cout << "Entering PreparingContract state." << std::endl;
    }

    sc::result PreparingContract::react(const event::ContractPrepared & e) {

        std::cout << "Reacting to ContractPrepared event." << std::endl;

        // Update payor state
        context<CBStateMachine>()._payor.setFunds(e.value());
        context<CBStateMachine>()._payor.setPayorContractKeyPair(e.contractKeyPair());
        context<CBStateMachine>()._payor.setPayorFinalPkHash(e.finalPkHash());
        context<CBStateMachine>()._payor.setAnchor(e.anchor());

        // Send ready message
        context<CBStateMachine>()._sendReadyMessage(joystream::protocol_wire::Ready(e.value(), e.anchor(), e.contractKeyPair().pk(), e.finalPkHash()));

        // Now ready to start requesting pieces
        return transit<RequestingPieces>();
    }
}
}
