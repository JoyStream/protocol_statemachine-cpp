/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#include <protocol_statemachine/exception/CannotSpeedTestNonSeller.hpp>

namespace joystream {
namespace protocol_statemachine {
namespace exception {

    CannotSpeedTestNonSeller::CannotSpeedTestNonSeller()
        : std::runtime_error("Cannot speed test peer not in seller mode.") {
    }

}
}
}
