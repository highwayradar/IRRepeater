#include <Arduino.h>
#include "duration.h"
#include "app_state.h"

MenuItemProgramDelay::MenuItemProgramDelay(AppState &appState, size_t commandIdx)
    : OperationStateMenuItemInt(appState), commandIdx(commandIdx) {}

size_t MenuItemProgramDelay::writeItem(char *dest, size_t maxWrite) const {
    int32_t value = getValue();
    return snprintf_P(dest, maxWrite, PSTR("Duration  | %d.%02d s"), int(value / 100), int(value % 100));
}

int32_t MenuItemProgramDelay::getMinValue() {
    return 10;
}

int32_t MenuItemProgramDelay::getMaxValue() {
    return 9999;
}

void MenuItemProgramDelay::onChange(int32_t value) {
    appState.program.commands[commandIdx].commandDurationMsDiv10 = value;
    appState.save();
}

int32_t MenuItemProgramDelay::getStoredValue() const {
    return appState.program.commands[commandIdx].commandDurationMsDiv10;
}
