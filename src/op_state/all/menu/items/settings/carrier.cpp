#include <Arduino.h>
#include "carrier.h"
#include "app_state.h"

MenuItemSettingsCarrier::MenuItemSettingsCarrier(AppState &appState)
    : OperationStateMenuItemInt(appState) {}

size_t MenuItemSettingsCarrier::writeItem(char *dest, size_t maxWrite) const {
    int value = int(getValue());
    return snprintf_P(dest, maxWrite, PSTR("IR carrier | %d kHz"), value);
}

int32_t MenuItemSettingsCarrier::getMinValue() {
    return 20;
}

int32_t MenuItemSettingsCarrier::getMaxValue() {
    return 60;
}

void MenuItemSettingsCarrier::onChange(int32_t value) {
    appState.settings.carrierKHz = uint8_t(value);
    appState.save();
}

int32_t MenuItemSettingsCarrier::getStoredValue() const {
    return appState.settings.carrierKHz;
}
