/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_EVENT_SENDTESTPAYLOAD_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_EVENT_SENDTESTPAYLOAD_HPP

#include <boost/statechart/event.hpp>

namespace sc = boost::statechart;

namespace joystream {
namespace protocol_statemachine {
namespace event {

    class SendTestPayload : public sc::event<SendTestPayload> {

    public:

        SendTestPayload();

    };

}
}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_EVENT_SENDTESTPAYLOAD_HPP
