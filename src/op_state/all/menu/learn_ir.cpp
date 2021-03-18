#include <new.h>
#include <Arduino.h>
#include <ir_data.h>
#include "op_state/all/learn_ir_action.h"
#include <ir_remote.h>
#include "learn_ir.h"
#include "app_state.h"

BaseOperationState *OperationStateMenuLearnIR::create(void *dest, AppState *appState, const void *stash) {
    size_t initialCursorPos = stash == nullptr ? 0 : *reinterpret_cast<const size_t *>(stash);
    return new (dest) OperationStateMenuLearnIR(*appState, initialCursorPos);
}

OperationStateMenuLearnIR::OperationStateMenuLearnIR(AppState &appState, size_t initialCursorPos)
    : OperationStateSimpleMenu(appState, initialCursorPos) {}

size_t OperationStateMenuLearnIR::getItemsCount() const {
    return IRDataSet::N_SLOTS;
}

size_t OperationStateMenuLearnIR::writeTitle(char *dest, size_t maxWrite) const {
    return snprintf_P(dest, maxWrite, PSTR("Learn IR"));
}

size_t OperationStateMenuLearnIR::writeItem(char *dest, size_t maxWrite, size_t idx) const {
    return snprintf_P(
        dest,
        maxWrite,
        PSTR("IR %c | %S"),
        IRDataSet::getLetterID(idx),
        idx == nowFiring
            ? PSTR("FIRE")
            : appState.irData.slots[idx].hasData()
                ? PSTR("Learned")
                : PSTR("--")
    );
}

void OperationStateMenuLearnIR::testFire() {
    auto &data = appState.irData.slots[getCursorPosition()];
    if (!data.hasData()) {
        return;
    }
    nowFiring = getCursorPosition();
    draw();
    if (!data.isLoaded()) {
        appState.eeprom.loadIRData(data, nowFiring);
    }
    delay(500);
    appState.ir.fire(data, appState.settings.carrierKHz);
    delay(50);
    nowFiring = IRDataSet::N_SLOTS;
}

void OperationStateMenuLearnIR::onKeyPress(char key) {
    size_t digit;
    switch (key) {
    case IR_KEY_PREV_SCREEN:
        return appState.transitionOpState(OperationStateMenuActions::create);
    case IR_KEY_NEXT_SCREEN:
        return appState.transitionOpState(OperationStateMenuProgram::create);
    case IR_KEY_ENTER:
        return appState.transitionOpState(OperationStateLearnIRAction::create, getCursorPosition());
    case IR_KEY_PLAY:
        return testFire();
    CASE_ANY_DIGIT:
        digit = getDigitValue(key);
        if (1 <= digit && digit <= getItemsCount()) {
            setCursorPosition(digit - 1);
        }
        break;
    default:
        OperationStateSimpleMenu::onKeyPress(key);
    }
}
