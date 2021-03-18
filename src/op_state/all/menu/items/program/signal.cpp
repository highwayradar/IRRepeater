#include "signal.h"

#include <Arduino.h>
#include "app_state.h"

MenuItemProgramSignal::MenuItemProgramSignal(AppState &appState, size_t commandIdx)
    : OperationStateMenuItemSelect(appState), commandIdx(commandIdx) {}

size_t MenuItemProgramSignal::writeItem(char *dest, size_t maxWrite) const {
    return snprintf_P(dest, maxWrite, PSTR("Signal    | IR %c"), IRDataSet::getLetterID(getValue()));
}

size_t MenuItemProgramSignal::getItemsCount() {
    return IRDataSet::N_SLOTS;
}

void MenuItemProgramSignal::onChange(size_t value) {
    appState.program.commands[commandIdx].irSlotIdx = value;
    appState.save();
}

size_t MenuItemProgramSignal::getStoredValue() const {
    return appState.program.commands[commandIdx].irSlotIdx;
}
