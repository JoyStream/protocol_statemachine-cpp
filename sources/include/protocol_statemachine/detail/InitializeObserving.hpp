/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, March 21 2016
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_DETAIL_INITIALIZEOBSERVING_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_DETAIL_INITIALIZEOBSERVING_HPP

#include <boost/statechart/event.hpp>

namespace sc = boost::statechart;

namespace joystream {
namespace protocol_statemachine {
namespace detail {

    class InitializeObserving : public sc::event<InitializeObserving> {
    };
}
}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_DETAIL_INITIALIZEOBSERVING_HPP
