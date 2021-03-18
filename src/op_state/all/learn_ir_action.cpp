#include "learn_ir_action.h"

#include <new.h>
#include <Arduino.h>
#include <app_state.h>
#include <errors.h>

BaseOperationState *OperationStateLearnIRAction::create(void *dest, AppState *appState, const void *stash) {
    size_t slotIdx = *reinterpret_cast<const size_t *>(stash);
    return new (dest) OperationStateLearnIRAction(*appState, slotIdx);
}

OperationStateLearnIRAction::OperationStateLearnIRAction(AppState &appState, size_t slotIdx)
    : BaseOperationState(appState), slotIdx(slotIdx) {
    appState.ir.delayNextReading();
    appState.eeprom.putEmptyIRData(appState.irData.slots[slotIdx]);
}

void OperationStateLearnIRAction::draw() const {
    char text[DisplayController::MAX_TEXT_LENGTH];
    snprintf_P(text, sizeof(text), PSTR("Learn IR\n$1\n$2Slot %c\n$1\nAwaiting signal..."), IRDataSet::getLetterID(slotIdx));
    appState.display.showText(text);
}

void OperationStateLearnIRAction::onKeyPress(char key) {
    // IR blocked, should never reach here
    criticalError(ERROR_UNREACHABLE_CODE);
}

void OperationStateLearnIRAction::onPeriodic(int32_t tm) {
    if (!appState.ir.capture(appState.irData.slots[slotIdx])) {
        delay(50);
        return;
    }
    appState.eeprom.saveIRData(appState.irData.slots[slotIdx], slotIdx);
    appState.save();
    return appState.transitionOpState(OperationStateMenuLearnIR::create, slotIdx);
}

bool OperationStateLearnIRAction::disableIRCommands() const {
    return true;
}
