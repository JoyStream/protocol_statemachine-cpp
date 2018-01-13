/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 29 2016
 */

#include <protocol_statemachine/RequestingPieces.hpp>
#include <protocol_statemachine/WaitingForFullPiece.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    RequestingPieces::RequestingPieces() {
        std::cout << "Entering RequestingPieces state." << std::endl;
    }

    sc::result RequestingPieces::react(const event::RequestPiece & e) {

        std::cout << "Reacting to RequestPiece event." << std::endl;

        // Request piece from seller
        context<CBStateMachine>()._sendRequestFullPieceMessage(protocol_wire::RequestFullPiece(e.pieceIndex()));

        context<SellerHasJoined>()._outstandingRequests++;

        // return to RequestingPieces state
        return transit<RequestingPieces>();
    }

    sc::result RequestingPieces::react(const event::Recv<protocol_wire::FullPiece> & e) {

        std::cout << "Reacting to Recv<wire::FullPiece> event." << std::endl;

        int outstandingPieces = context<SellerHasJoined>()._outstandingRequests;

        // We should be expecting a full piece
        if (outstandingPieces == 0) {
          // Inform client of overflow
          context<CBStateMachine>()._receiveFullPieceOverflow();

          // Terminate the statemachine
          return terminate();
        }

        // Send piece to client
        context<CBStateMachine>()._receivedFullPiece(e.message().pieceData());

        context<SellerHasJoined>()._outstandingRequests--;

        // return to RequestingPieces state
        return transit<RequestingPieces>();
    }

    sc::result RequestingPieces::react(const event::SendPayment &) {

        std::cout << "Reacting to SendPayment event." << std::endl;

        // Make payment signature
        Coin::Signature sig = context<CBStateMachine>()._payor.makePayment();

        // Send payment
        context<CBStateMachine>()._sendPaymentMessage(protocol_wire::Payment(sig));

        // return to RequestingPieces state
        return transit<RequestingPieces>();
    }

    sc::result RequestingPieces::react(const event::InvalidPieceReceived &) {

        std::cout << "Reacting to InvalidPieceReceived event." << std::endl;

        // Stop state machine
        return terminate();
    }
}
}
