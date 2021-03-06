/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 17 2016
 */

#ifndef JOYSTREAM_PROTOCOL_STATE_MACHINE_READYFORINVITATION_HPP
#define JOYSTREAM_PROTOCOL_STATE_MACHINE_READYFORINVITATION_HPP

#include <protocol_statemachine/Selling.hpp>
#include <protocol_statemachine/event/Recv.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    class ReadyForInvitation : public sc::simple_state<ReadyForInvitation, Selling> {

    public:

        typedef boost::mpl::list<
                                sc::custom_reaction<event::Recv<protocol_wire::JoinContract>>,
                                sc::custom_reaction<event::Recv<protocol_wire::SpeedTestRequest>>
                                > reactions;

        ReadyForInvitation();

        // Event handlers
        sc::result react(const event::Recv<protocol_wire::JoinContract> &);
        sc::result react(const event::Recv<protocol_wire::SpeedTestRequest> &);

    };
}
}

#endif // JOYSTREAM_PROTOCOL_STATE_MACHINE_READYFORINVITATION_HPP
