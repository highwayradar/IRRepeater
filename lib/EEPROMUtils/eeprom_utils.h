#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <ir_data.h>

// Removes magic from EEPROM, so the data shouldn't be loaded any more
void wipeUserEeprom();

// Similar to Arduino's EEPROM.put
template<typename T>
void writeObject(size_t address, const T& obj) {
    eeprom_write_block(&obj, reinterpret_cast<void *>(address), sizeof(obj));
}

// Similar to Arduino's EEPROM.get
template<typename T>
void readObject(size_t address, T& dest) {
    eeprom_read_block(&dest, reinterpret_cast<const void *>(address), sizeof(dest));
}

// Helper for saving the app state without using additional buffer memory
class EepromSequentialReader {
public:
    EepromSequentialReader();

    template<typename T>
    void read(T &dest) {
        readObject(offset, dest);
        offset += sizeof(dest);
    }

private:
    size_t offset;
};

// Helper for loading the app state without using additional buffer memory
class EepromSequentialWriter {
public:
    EepromSequentialWriter();

    template<typename T>
    void write(const T &data) {
        writeObject(offset, data);
        offset += sizeof(data);
    }

private:
    size_t offset;
};


// Class for managing IR timings (loading / saving)
class EepromIRTimingsManager {
private:
    uint16_t irTimingsBuf[IRData::MAX_SIGNAL_LENGTH]{};
    const IRData *currentIRData = nullptr;

public:
    void loadIRData(const IRData &dest, size_t slotIdx);
    void saveIRData(const IRData &irData, size_t slotIdx);
    void putEmptyIRData(const IRData &dest);
};
