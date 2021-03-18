#include "eeprom_utils.h"

// Storage schema: [irTimings_A][irTimings_B][irTimings_C][irTimings_D][Magic+AppState]
// For IT timings storing the full buffer

static constexpr size_t APP_STATE_DATA_START = sizeof(uint16_t) * IRData::MAX_SIGNAL_LENGTH * IRDataSet::N_SLOTS;

EepromSequentialReader::EepromSequentialReader() : offset(APP_STATE_DATA_START) {}

EepromSequentialWriter::EepromSequentialWriter() : offset(APP_STATE_DATA_START) {}

void EepromIRTimingsManager::loadIRData(const IRData &dest, size_t slotIdx) {
    putEmptyIRData(dest);
    size_t address = slotIdx * sizeof(irTimingsBuf);
    readObject(address, irTimingsBuf);
}

void EepromIRTimingsManager::saveIRData(const IRData &irData, size_t slotIdx) {
    size_t address = slotIdx * sizeof(irTimingsBuf);
    writeObject(address, irTimingsBuf);
}

void EepromIRTimingsManager::putEmptyIRData(const IRData &dest) {
    if (currentIRData != nullptr) {
        // Mark timings offloaded
        currentIRData->irTimings = nullptr;
    }
    dest.irTimings = irTimingsBuf;
    currentIRData = &dest;
}

void wipeUserEeprom() {
    // Remove magic
    eeprom_write_dword(reinterpret_cast<uint32_t *>(APP_STATE_DATA_START), 0);
}
