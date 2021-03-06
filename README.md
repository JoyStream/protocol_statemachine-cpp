
# ProtocolStateMachine
C++ statemachine library for the JoyStream extension protocol, as specified [here](http://#).

conan package name: `ProtocolStateMachine/0.2.0@joystream/stable`

### Dependencies

This library, has *immediate* dependencies

- [PaymentChannel](https://github.com/JoyStream/paymentchannel-cpp)
- [ProtocolWire](https://github.com/JoyStream/protocol_wire-cpp)
- [gtest](https://github.com/google/googletest/)


and they are managed using [Conan](https://conan.io), a platform and build system agnostic C++ package manager.

### Example Usage

See [Extension](https://github.com/JoyStream/extension-cpp)

## Running Unit Tests

```
sh run_tests.sh
```

## License & Copyright

JoyStream protocol_statemachine library is released under the terms of the MIT license.
See [LICENSE](LICENCE) for more information.
