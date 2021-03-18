#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>
#include <time_utils.h>
#include <errors.h>
#include "app_state.h"
#include "constants.h"
#include "helpers.h"

// Magic number to identify if EEPROM data is valid
constexpr uint64_t MAGIC = 0xdeadbeefLL
    | (uint64_t(IRData::MAX_SIGNAL_LENGTH) << 32)
    | (uint64_t(IRDataSet::N_SLOTS) << 48)
    | (uint64_t(Program::MAX_COMMANDS) << 56);

AppState::AppState(): display(DISPLAY_I2C), ir(PIN_IR_IN) {}

void AppState::transitionOpState(const OpStateTransitionRequest &request) {
    stateTransitionRequest = request;
}

void AppState::onPeriodic() {
    executePendingOpStateTransition();
    auto *opState = opStateContainer.getValue();
    if (opState == nullptr) {
        return;
    }
    if (!opState->disableIRCommands()) {
        if (char key = ir.getCommand()) {
            opState->onKeyPress(key);
        }
    }
    if (!stateTransitionRequest.empty()) return;
    opState->onPeriodic(signedMillis());
    if (!stateTransitionRequest.empty()) return;
    opState->draw();
}

void AppState::executePendingOpStateTransition() {
    if (stateTransitionRequest.empty()) return;
    if (opStateContainer.getValue() != nullptr) {
        opStateContainer.getValue()->onDestroy();
    }
    opStateContainer.putValue(
        stateTransitionRequest.factory,
        this,
        stateTransitionRequest.nonEmptyStash()
    );
    stateTransitionRequest.reset();
    opStateContainer.getValue()->onCreate();
}

void AppState::save() const {
    auto writer = EepromSequentialWriter();
    writer.write(MAGIC);
    uint64_t tmp;
    eeprom_read_block(&tmp, reinterpret_cast<const void *>(800), sizeof(tmp));
    irData.save(writer);
    writer.write(settings);
    writer.write(program);
}

void AppState::load() {
    uint64_t obtainedMagic;
    auto reader = EepromSequentialReader();
    reader.read(obtainedMagic);
    if (obtainedMagic != MAGIC) {
        return;
    }
    irData.load(reader);
    reader.read(settings);
    reader.read(program);
}
