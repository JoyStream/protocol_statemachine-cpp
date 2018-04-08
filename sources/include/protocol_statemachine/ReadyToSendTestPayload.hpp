/**
 * Copyright (C) JoyStream - All Rights Reserved
 */

#ifndef JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOSENDTESTPAYLOAD_HPP
#define JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOSENDTESTPAYLOAD_HPP

#include <protocol_statemachine/Buying.hpp>
#include <protocol_statemachine/event/SendTestPayload.hpp>
#include <protocol_statemachine/event/Recv.hpp>
#include <protocol_wire/protocol_wire.hpp>

namespace joystream {
namespace protocol_statemachine {

    class ReadyToSendTestPayload : public sc::simple_state<ReadyToSendTestPayload, Selling> {

    public:

      typedef boost::mpl::list<
                              sc::custom_reaction<event::SendTestPayload>,
                              sc::custom_reaction<event::Recv<protocol_wire::Buy>>,
                              sc::custom_reaction<event::UpdateTerms<protocol_wire::SellerTerms>>
                              > reactions;

      ReadyToSendTestPayload();

      // Event handlers
      sc::result react(const event::SendTestPayload &);
      sc::result react(const event::Recv<protocol_wire::Buy> &);
      sc::result react(const event::UpdateTerms<protocol_wire::SellerTerms> &);

    };

}
}

#endif // JOYSTREAM_PROTOCOLSTATEMACHINE_READYTOSENDTESTPAYLOAD_HPP
