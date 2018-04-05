/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 24 2016
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_TESTINGSELLERSPEED_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_TESTINGSELLERSPEED_HPP

#include <protocol_statemachine/Buying.hpp>
#include <protocol_statemachine/event/Recv.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    class TestingSellerSpeed : public sc::simple_state<TestingSellerSpeed, Buying> {

    public:

      typedef boost::mpl::list<
                              sc::custom_reaction<event::Recv<protocol_wire::SpeedTestPayload>>
                              > reactions;

      TestingSellerSpeed();

      // Event handlers
      sc::result react(const event::Recv<protocol_wire::SpeedTestPayload> &);

    };

}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOINVITESELLER_HPP
