/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 8 2016
 */

#include <protocol_statemachine/Selling.hpp>
#include <protocol_statemachine/Buying.hpp>

#include <iostream>
#include <cassert>

namespace joystream {
namespace protocol_statemachine {

    Selling::Selling() {
        std::cout << "Entering Selling state." << std::endl;
    }

    sc::result Selling::react(const event::ObserveModeStarted &) {

        std::cout << "Reacting to ObserveModeStarted." << std::endl;

        // Client to observe mode
        context<CBStateMachine>().clientToObserveMode();

        // Transiti
        return transit<Observing>();
    }

    sc::result Selling::react(const event::BuyModeStarted & e) {

        std::cout << "Reacting to BuyModeStarted." << std::endl;

        // Client to buy mode
        context<CBStateMachine>().clientToBuyMode(e.terms());

        // Transition to Buy state
        return transit<Buying>();
    }

    sc::result Selling::react(const event::UpdateTerms<protocol_wire::SellerTerms> & e) {

        std::cout << "Reacting to UpdateTerms<SellerTerms>." << std::endl;

        // Client to sell mode
        context<CBStateMachine>().clientToSellMode(e.terms(), 1 + context<CBStateMachine>()._index);

        // Transition back to initial Selling state
        return transit<Selling>();
    }

    sc::result Selling::react(const event::Recv<protocol_wire::Observe> &) {

        std::cout << "Reacting to Recv<protocol_wire::Observe> event." << std::endl;

        // Switch peer state
        context<CBStateMachine>().peerToObserveMode();

        // Notify client about announcement
        context<CBStateMachine>().peerAnnouncedMode();

        // Transition back to initial Selling state
        return transit<Selling>();
    }

    sc::result Selling::react(const event::Recv<protocol_wire::Buy> & e) {

        std::cout << "Reacting to Recv<protocol_wire::Buy> event." << std::endl;

        // Switch peer state
        context<CBStateMachine>().peerToBuyMode(e.message().terms());

        // Notify client about announcement
        context<CBStateMachine>().peerAnnouncedMode();

        // Transition back to initial Selling state
        return transit<Selling>();
    }

    sc::result Selling::react(const event::Recv<protocol_wire::Sell> & e) {

        std::cout << "Reacting to Recv<protocol_wire::Sell> event." << std::endl;

        // Switch peer state
        protocol_wire::Sell m = e.message();
        context<CBStateMachine>().peerToSellMode(m.terms(), m.index());

        // Notify client about announcement
        context<CBStateMachine>().peerAnnouncedMode();

        // Transition back to initial Selling state
        return transit<Selling>();
    }
}
}
