/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 19 2016
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_SERVICINGPIECEREQUESTS_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_SERVICINGPIECEREQUESTS_HPP

#include <protocol_statemachine/StartedSelling.hpp>
#include <protocol_statemachine/event/PieceLoaded.hpp>
#include <protocol_statemachine/event/Recv.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    class ServicingPieceRequests : public sc::simple_state<ServicingPieceRequests, StartedSelling> {

    public:

        typedef boost::mpl::list<
                                sc::custom_reaction<event::Recv<protocol_wire::RequestFullPiece>>,
                                sc::custom_reaction<event::PieceLoaded>,
                                sc::custom_reaction<event::Recv<protocol_wire::Payment>>
                                > reactions;

        ServicingPieceRequests();

        // Event handlers
        sc::result react(const event::Recv<protocol_wire::RequestFullPiece> &);
        sc::result react(const event::Recv<protocol_wire::Payment> &);
        sc::result react(const event::PieceLoaded &);

    private:
      uint32_t _totalRequestsReceived;
      uint32_t _totalPiecesSent;
      uint32_t _totalPaymentsReceived;
    };

}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_SERVICINGPIECEREQUESTS_HPP
