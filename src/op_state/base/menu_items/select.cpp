#include <stdint.h>
#include <Arduino.h>
#include <ir_remote.h>
#include "select.h"

OperationStateMenuItemSelect::OperationStateMenuItemSelect(AppState &appState)
    : BaseOperationStateMenuItem(appState) {}

size_t OperationStateMenuItemSelect::getValue() const {
    return isActive ? bufferedValue : getStoredValue();
}

void OperationStateMenuItemSelect::onEnter() {
    isActive = true;
    bufferedValue = getStoredValue();
}

void OperationStateMenuItemSelect::onExit() {
    if (bufferedValue != getStoredValue()) {
        onChange(bufferedValue);
    }
    isActive = false;
}

void OperationStateMenuItemSelect::onKeyPress(char key) {
    size_t digit;
    size_t n_items;
    switch (key) {
    case IR_KEY_INC_VALUE:
        bufferedValue = (bufferedValue + 1) % getItemsCount();
        break;
    case IR_KEY_DEC_VALUE:
        n_items = getItemsCount();
        bufferedValue = (bufferedValue + n_items - 1) % n_items;
        break;
    CASE_ANY_DIGIT:
        digit = getDigitValue(key);
        if (1 <= digit && digit <= getItemsCount()) {
            bufferedValue = size_t(digit) - 1;
        }
        break;
    default:
        break;
    }
}
