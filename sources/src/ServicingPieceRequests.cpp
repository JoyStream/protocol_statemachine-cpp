/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 19 2016
 */

#include <protocol_statemachine/ServicingPieceRequests.hpp>

namespace joystream {
namespace protocol_statemachine {

    ServicingPieceRequests::ServicingPieceRequests() :
      _totalRequestsReceived(0),
      _totalPiecesSent(0),
      _totalPaymentsReceived(0)
    {
        std::cout << "Entering ServicingPieceRequests state." << std::endl;
    }

    sc::result ServicingPieceRequests::react(const event::Recv<protocol_wire::RequestFullPiece> & e) {

        std::cout << "Reacting to Recv<wire::RequestFullPiece> event." << std::endl;

        _totalRequestsReceived++;

        // Check that piece requested is valid,
        int pieceIndex = e.message().pieceIndex();

        if(pieceIndex < 0 || pieceIndex > context<CBStateMachine>()._MAX_PIECE_INDEX) {

            // if not, send notification and terminate
            context<CBStateMachine>()._invalidPieceRequested();

            return terminate();
        }

        // otherwise send success notification, and
        context<CBStateMachine>()._pieceRequested(pieceIndex);
        context<CBStateMachine>()._lastRequestedPiece = pieceIndex;

        // Remain in same state
        return discard_event();
    }

    sc::result ServicingPieceRequests::react(const event::PieceLoaded & e) {

        std::cout << "Reacting to PieceLoaded event." << std::endl;

        _totalPiecesSent++;

        if (_totalPiecesSent > _totalRequestsReceived) {
          // Inform client of overflow
          context<CBStateMachine>()._localMessageOverflow();

          // Terminate the statemachine
          return terminate();
        }

        // Send piece
        context<CBStateMachine>()._sendFullPieceMessage(joystream::protocol_wire::FullPiece(e.pieceData()));

        // Remain in same state
        return discard_event();
    }

    sc::result ServicingPieceRequests::react(const event::Recv<protocol_wire::Payment> & e) {

        std::cout << "Reacting to Recv<wire::Payment>." << std::endl;

        _totalPaymentsReceived++;

        if (_totalPaymentsReceived > _totalPiecesSent) {
          // Inform client of overflow
          context<CBStateMachine>()._remoteMessageOverflow();

          // Terminate the statemachine
          return terminate();
        }

        // Get payment signature
        Coin::Signature payment = e.message().sig();

        // Check validity of payment signature, and register if valid
        bool valid = context<CBStateMachine>()._payee.registerPayment(payment);

        if(valid) {

            // Notify client about valid payment
            context<CBStateMachine>()._validPayment(payment);

            // Remain in same state
            return discard_event();
        } else {

            // Notify client about bad payment
            context<CBStateMachine>()._invalidPayment(payment);

            // Terminate machine
            return terminate();
        }
    }

}
}
