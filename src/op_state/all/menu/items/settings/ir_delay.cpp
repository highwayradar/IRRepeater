#include <Arduino.h>
#include "ir_delay.h"
#include "app_state.h"

MenuItemSettingsIRDelay::MenuItemSettingsIRDelay(AppState &appState)
    : OperationStateMenuItemInt(appState) {}

size_t MenuItemSettingsIRDelay::writeItem(char *dest, size_t maxWrite) const {
    int value = int(getValue());
    return snprintf_P(dest, maxWrite, PSTR("IR min gap | %d ms"), value);
}

int32_t MenuItemSettingsIRDelay::getMinValue() {
    return 10;
}

int32_t MenuItemSettingsIRDelay::getMaxValue() {
    return 100;
}

void MenuItemSettingsIRDelay::onChange(int32_t value) {
    appState.settings.irDelayMs = uint16_t(value);
    appState.save();
}

int32_t MenuItemSettingsIRDelay::getStoredValue() const {
    return appState.settings.irDelayMs;
}
