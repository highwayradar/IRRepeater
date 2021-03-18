#include <Arduino.h>
#include <ir_remote.h>
#include "int.h"

OperationStateMenuItemInt::OperationStateMenuItemInt(AppState &appState)
    : BaseOperationStateMenuItem(appState) {}

int32_t OperationStateMenuItemInt::getValue() const {
    return isActive ? bufferedValue : getStoredValue();
}

void OperationStateMenuItemInt::onEnter() {
    isActive = true;
    bufferedValue = getStoredValue();
}

void OperationStateMenuItemInt::onExit() {
    if (bufferedValue != getStoredValue()) {
        onChange(getClampedValue());
    }
    isActive = false;
}

int32_t OperationStateMenuItemInt::getClampedValue() {
    return min(max(bufferedValue, getMinValue()), getMaxValue());
}

void OperationStateMenuItemInt::onKeyPress(char key) {
    size_t digit;
    switch (key) {
    case IR_KEY_INC_VALUE:
        bufferedValue = min(getMaxValue(), bufferedValue + 1);
        break;
    case IR_KEY_DEC_VALUE:
        bufferedValue = max(getMinValue(), bufferedValue - 1);
        break;
    CASE_ANY_DIGIT:
        digit = getDigitValue(key);
        if (digit > getMaxValue()) {
            return;
        }
        if (digit < getMinValue() && getMaxValue() < 10) {
            return;
        }
        bufferedValue = bufferedValue * 10 + digit;
        while (bufferedValue > getMaxValue()) {
            // Cut the first digit
            int32_t rem = bufferedValue / 10, mod = 1;
            while (rem > 0) {
                rem /= 10;
                mod *= 10;
            }
            bufferedValue %= mod;
        }
        break;
    default:
        return;  // Don't run onChange
    }
}
