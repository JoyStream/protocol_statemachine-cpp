/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 29 2016
 */

#ifndef JOYSTREAM_PROTOCOL_STATEMACHINE_REQUESTINGPIECES_HPP
#define JOYSTREAM_PROTOCOL_STATEMACHINE_REQUESTINGPIECES_HPP

#include <protocol_statemachine/SellerHasJoined.hpp>
#include <protocol_statemachine/event/RequestPiece.hpp>
#include <protocol_statemachine/event/SendPayment.hpp>
#include <protocol_statemachine/event/InvalidPieceReceived.hpp>
#include <protocol_statemachine/event/Recv.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    class RequestingPieces : public sc::simple_state<RequestingPieces, SellerHasJoined> {

    public:

        typedef boost::mpl::list<
                                sc::custom_reaction<event::RequestPiece>,
                                sc::custom_reaction<event::Recv<protocol_wire::FullPiece>>
                                sc::custom_reaction<event::SendPayment>,
                                sc::custom_reaction<event::InvalidPieceReceived>
                                > reactions;

        RequestingPieces();

        // Event handlers
        sc::result react(const event::RequestPiece &);
        sc::result react(const event::Recv<protocol_wire::FullPiece> &);
        sc::result react(const event::SendPayment &);
        sc::result react(const event::InvalidPieceReceived &);
    };

}
}

#endif // JOYSTREAM_PROTOCOL_STATEMACHINE_READYTOREQUESTPIECE_HPP
