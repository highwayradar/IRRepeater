#include "ir_data.h"

#include "eeprom_utils.h"

int32_t IRData::getFiringDurationMs(size_t repetitions, int32_t intervalMs) const {
    int32_t oneRepUs = 1000L * intervalMs;
    for (size_t i = 0; i < irTimingsSize; ++i) {
        oneRepUs += irTimings[i];
    }
    return (oneRepUs * int32_t(repetitions) + 999) / 1000;
}

void IRData::save(EepromSequentialWriter &writer) const {
    writer.write(irTimingsSize);
}

void IRData::load(EepromSequentialReader &reader) {
    reader.read(irTimingsSize);
}

void IRDataSet::save(EepromSequentialWriter &writer) const {
    for (const auto &slot : slots) {
        slot.save(writer);
    }
}

void IRDataSet::load(EepromSequentialReader &reader) {
    for (auto &slot : slots) {
        slot.load(reader);
    }
}
