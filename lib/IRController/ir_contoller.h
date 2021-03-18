#pragma once

#include <Arduino.h>

#include <IRLibDecodeBase.h>
#include <IRLibSendBase.h>
#include <IRLib_P01_NEC.h>
#include <IRLib_HashRaw.h>
#include <IRLibCombo.h>
#include <IRLibRecvPCI.h>

#include "ir_data.h"

class IRController {
    IRsendRaw irSender;
    IRrecvPCI irReceiver;
    IRdecode irDecoder;

    int32_t blockReceiveUntil = 0;

    // Parse control command from a remote
    static char parseCommand(uint32_t value);

public:
    IRController(IRController &) = delete;
    IRController &operator = (IRController &) = delete;

    explicit IRController(uint8_t receiverPin);

    // Drop any stored reading
    void flush();

    // Don't accept new IR signals for 500ms
    void delayNextReading();

    // Capture and save next IR signal
    bool capture(IRData &dest);

    // Get IR command from remote if available. Returns '\0' if no command received.
    char getCommand();

    void fire(
        const IRData &data,
        uint8_t carrierKhz);

    void fire(
        const IRData &data,
        uint8_t carrierKhz,
        uint8_t repetitions,
        int32_t intervalMs);
};
