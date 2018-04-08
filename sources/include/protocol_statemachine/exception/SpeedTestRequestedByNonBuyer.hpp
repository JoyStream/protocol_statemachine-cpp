/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_SPEEDTESTREQUESTEDBYNONBUYER_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_SPEEDTESTREQUESTEDBYNONBUYER_HPP

#include <protocol_statemachine/AnnouncedModeAndTerms.hpp>
#include <stdexcept>

namespace joystream {
namespace protocol_statemachine {

    enum class ModeAnnounced;

    namespace exception {

        class SpeedTestRequestedByNonBuyer : public std::runtime_error {

        public:

            enum class NonBuyModeAnnounced {
                None,
                Sell,
                Observe
            };

            static NonBuyModeAnnounced toNonBuyMode(ModeAnnounced mode);

            SpeedTestRequestedByNonBuyer(NonBuyModeAnnounced mode);
            SpeedTestRequestedByNonBuyer(ModeAnnounced mode);

            // Getters and setters
            NonBuyModeAnnounced peerMode() const;
            void setPeerMode(NonBuyModeAnnounced peerMode);

        private:

            // The actual mode the peer was in
            NonBuyModeAnnounced _peerMode;
        };
    }
}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_SPEEDTESTREQUESTEDBYNONBUYER_HPP
