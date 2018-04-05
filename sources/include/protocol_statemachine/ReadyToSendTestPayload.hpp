/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOSENDTESTPAYLOAD_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOSENDTESTPAYLOAD_HPP

#include <protocol_statemachine/Buying.hpp>
#include <protocol_statemachine/event/SendTestPayload.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    class ReadyToSendTestPayload : public sc::simple_state<ReadyToSendTestPayload, Selling> {

    public:

      typedef boost::mpl::list<
                              sc::custom_reaction<event::SendTestPayload>
                              > reactions;

      ReadyToSendTestPayload();

      // Event handlers
      sc::result react(const event::SendTestPayload &);

    };

}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOSENDTESTPAYLOAD_HPP
