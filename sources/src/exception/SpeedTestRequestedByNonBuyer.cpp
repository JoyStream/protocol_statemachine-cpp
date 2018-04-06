/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#include <protocol_statemachine/exception/SpeedTestRequestedByNonBuyer.hpp>

namespace joystream {
namespace protocol_statemachine {
namespace exception {

    SpeedTestRequestedByNonBuyer::NonBuyModeAnnounced SpeedTestRequestedByNonBuyer::toNonBuyMode(ModeAnnounced mode) {

        switch(mode) {
            case ModeAnnounced::none: return NonBuyModeAnnounced::None; break;
            case ModeAnnounced::observe: return NonBuyModeAnnounced::Observe; break;
            case ModeAnnounced::sell: return NonBuyModeAnnounced::Sell; break;

            default: // ModeAnnounced::Buy
                throw std::runtime_error("ModeAnnounced cannot be Buy.");
        }
    }

    SpeedTestRequestedByNonBuyer::SpeedTestRequestedByNonBuyer(NonBuyModeAnnounced mode)
        : std::runtime_error("JoinContract message arrived from peer not in buy mode, spesifically: x")
        , _peerMode(mode) {
    }

    SpeedTestRequestedByNonBuyer::SpeedTestRequestedByNonBuyer(ModeAnnounced mode)
        : SpeedTestRequestedByNonBuyer(toNonBuyMode(mode)) {
    }

    SpeedTestRequestedByNonBuyer::NonBuyModeAnnounced SpeedTestRequestedByNonBuyer::peerMode() const {
        return _peerMode;
    }

    void SpeedTestRequestedByNonBuyer::setPeerMode(NonBuyModeAnnounced peerMode) {
        _peerMode = peerMode;
    }
}
}
}
