#pragma once

#include "stddef.h"
#include "stdint.h"

class AppState;

// A single command from the program
struct ProgramCommand {
    bool isEnabled = false;
    size_t irSlotIdx = 0;
    uint8_t repetitions = 1;
    uint16_t commandDurationMsDiv10 = 500;

    inline int32_t getCommandDurationMs() const {
        return int32_t(commandDurationMsDiv10) * 10L;
    }

    // Check if the command can be executed.
    // Transition to alert state if it can't.
    bool validateOrAlert(AppState &appState) const;
};

// The program to be replayed
struct Program {
    static const size_t MAX_COMMANDS = 4;
    static const char START_LETTER = '1';
    ProgramCommand commands[MAX_COMMANDS];

    static inline char getLetterID(size_t idx) {
        return START_LETTER + char(idx);
    }

    // Check if the program can be executed.
    // Transition to alert state if it can't.
    bool validateOrAlert(AppState &appState) const;
};
