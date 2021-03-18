#pragma once

#include <IRLibGlobals.h>

class EepromSequentialReader;
class EepromSequentialWriter;

// Data representing one IR signal
struct IRData {
    static const size_t MAX_SIGNAL_LENGTH = 100;

    bufIndex_t irTimingsSize = 0;

    // IR data is stored in EEPROM, and only loaded to memory when needed.
    // irTimings points to the data if it is loaded; It is nullptr otherwise.
    mutable uint16_t *irTimings = nullptr;

    inline bool hasData() const {
        return irTimingsSize > 0;
    }

    inline bool isLoaded() const {
        return irTimings != nullptr;
    }

    // This shouldn't only load/save timings data -- they're managed separately.
    void save(EepromSequentialWriter &writer) const;
    void load(EepromSequentialReader &reader);

    int32_t getFiringDurationMs(size_t repetitions, int32_t intervalMs) const;
};

// Data representing all stored IR signals
struct IRDataSet {
    static const size_t N_SLOTS = 4;
    static const char START_LETTER = 'A';

    IRData slots[N_SLOTS]{};

    static inline char getLetterID(size_t idx) {
        return char(size_t(START_LETTER) + idx);
    }

    void save(EepromSequentialWriter &writer) const;
    void load(EepromSequentialReader &reader);
};
