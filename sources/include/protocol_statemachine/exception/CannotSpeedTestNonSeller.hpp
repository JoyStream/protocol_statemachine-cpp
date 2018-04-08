/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 27 2016
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_EXCEPTION_CANNOTSPEEDTESTNONSELLER_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_EXCEPTION_CANNOTSPEEDTESTNONSELLER_HPP

#include <stdexcept>

namespace joystream {
namespace protocol_statemachine {
namespace exception {

    class CannotSpeedTestNonSeller : public std::runtime_error {

    public:
        CannotSpeedTestNonSeller();
    };

}
}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_EXCEPTION_CANNOTSPEEDTESTNONSELLER_HPP
