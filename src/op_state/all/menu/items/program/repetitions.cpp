#include <Arduino.h>
#include "repetitions.h"
#include "app_state.h"

MenuItemProgramRepetitions::MenuItemProgramRepetitions(AppState &appState, size_t commandIdx)
    : OperationStateMenuItemInt(appState), commandIdx(commandIdx) {}

size_t MenuItemProgramRepetitions::writeItem(char *dest, size_t maxWrite) const {
    int value = int(getValue());
    switch (value) {
    case 1:
        return snprintf_P(dest, maxWrite, PSTR("Repeat IR | once"), value);
    case 2:
        return snprintf_P(dest, maxWrite, PSTR("Repeat IR | twice"), value);
    default:
        return snprintf_P(dest, maxWrite, PSTR("Repeat IR | %d times"), value);
    }
}

int32_t MenuItemProgramRepetitions::getMinValue() {
    return 1;
}

int32_t MenuItemProgramRepetitions::getMaxValue() {
    return 5;
}

void MenuItemProgramRepetitions::onChange(int32_t value) {
    appState.program.commands[commandIdx].repetitions = value;
    appState.save();
}

int32_t MenuItemProgramRepetitions::getStoredValue() const {
    return appState.program.commands[commandIdx].repetitions;
}
