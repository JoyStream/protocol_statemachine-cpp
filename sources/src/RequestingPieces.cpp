/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 29 2016
 */

#include <protocol_statemachine/RequestingPieces.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    RequestingPieces::RequestingPieces() :
      _totalRequestsSent(0),
      _totalPiecesReceived(0),
      _totalPaymentsSent(0) {
        std::cout << "Entering RequestingPieces state." << std::endl;
    }

    sc::result RequestingPieces::react(const event::RequestPiece & e) {

        std::cout << "Reacting to RequestPiece event." << std::endl;

        // Request piece from seller
        context<CBStateMachine>()._sendRequestFullPieceMessage(protocol_wire::RequestFullPiece(e.pieceIndex()));

        _totalRequestsSent++;

        // Remain in same state
        return discard_event();
    }

    sc::result RequestingPieces::react(const event::Recv<protocol_wire::FullPiece> & e) {

        std::cout << "Reacting to Recv<wire::FullPiece> event." << std::endl;

        _totalPiecesReceived++;

        // We should be expecting a full piece
        if (_totalPiecesReceived > _totalRequestsSent) {
          // Inform client of overflow
          context<CBStateMachine>()._remoteMessageOverflow();

          // Terminate the statemachine
          return terminate();
        }

        // Send piece to client
        context<CBStateMachine>()._receivedFullPiece(e.message().pieceData());

        // Remain in same state
        return discard_event();
    }

    sc::result RequestingPieces::react(const event::SendPayment &) {

        std::cout << "Reacting to SendPayment event." << std::endl;

        _totalPaymentsSent++;

        // Allow for polite seller compensations
        if (_totalPaymentsSent > _totalRequestsSent) {
          // Inform client of overflow
          context<CBStateMachine>()._localMessageOverflow();

          // Terminate the statemachine
          return terminate();
        }

        // Make payment signature
        Coin::Signature sig = context<CBStateMachine>()._payor.makePayment();

        // Send payment
        context<CBStateMachine>()._sendPaymentMessage(protocol_wire::Payment(sig));

        // Remain in same state
        return discard_event();
    }

    sc::result RequestingPieces::react(const event::InvalidPieceReceived &) {

        std::cout << "Reacting to InvalidPieceReceived event." << std::endl;

        // Stop state machine
        return terminate();
    }
}
}
