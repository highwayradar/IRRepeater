#include "enabled.h"

#include <Arduino.h>
#include "app_state.h"

// 0 - Yes, 1 - No

MenuItemProgramEnabled::MenuItemProgramEnabled(AppState &appState, size_t commandIdx)
    : OperationStateMenuItemSelect(appState), commandIdx(commandIdx) {}

size_t MenuItemProgramEnabled::writeItem(char *dest, size_t maxWrite) const {
    switch (getValue()) {
    case 0:
        return snprintf_P(dest, maxWrite, PSTR("Enabled   | Yes"));
    case 1:
        return snprintf_P(dest, maxWrite, PSTR("Enabled   | No"));
    default:
        return 0;
    }
}

size_t MenuItemProgramEnabled::getItemsCount() {
    return 2;
}

void MenuItemProgramEnabled::onChange(size_t value) {
    appState.program.commands[commandIdx].isEnabled = !bool(value);
    appState.save();
}

size_t MenuItemProgramEnabled::getStoredValue() const {
    return int(!appState.program.commands[commandIdx].isEnabled);
}
