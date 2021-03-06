/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 10 2016
 */

#include <protocol_statemachine/event/BuyModeStarted.hpp>

namespace joystream {
namespace protocol_statemachine {
namespace event {

    BuyModeStarted::BuyModeStarted() {
    }

    BuyModeStarted::BuyModeStarted(const joystream::protocol_wire::BuyerTerms & terms)
        : _terms(terms) {
    }

    joystream::protocol_wire::BuyerTerms BuyModeStarted::terms() const {
        return _terms;
    }

    void BuyModeStarted::setTerms(const joystream::protocol_wire::BuyerTerms & terms) {
        _terms = terms;
    }

}
}
}
