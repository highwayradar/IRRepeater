#include <new.h>
#include <Arduino.h>
#include <errors.h>
#include <ir_remote.h>
#include "app_state.h"
#include "settings.h"

BaseOperationState *OperationStateMenuSettings::create(void *dest, AppState *appState, const void *stash) {
    return new (dest) OperationStateMenuSettings(*appState);
}

OperationStateMenuSettings::OperationStateMenuSettings(AppState &appState)
    : OperationStateMenu(appState),
      vCarrier(appState),
      vDelay(appState)
{}

size_t OperationStateMenuSettings::getItemsCount() const {
    return 2;
}

size_t OperationStateMenuSettings::writeTitle(char *dest, size_t maxWrite) const {
    return snprintf_P(dest, maxWrite, PSTR("Settings"));
}

BaseOperationStateMenuItem &OperationStateMenuSettings::getItem(size_t idx) {
    switch (idx) {
    case 0:
        return vCarrier;
    case 1:
        return vDelay;
    default:
        criticalError(ERROR_UNREACHABLE_CODE);
    }
}

const BaseOperationStateMenuItem &OperationStateMenuSettings::getItem(size_t idx) const {
    switch (idx) {
    case 0:
        return vCarrier;
    case 1:
        return vDelay;
    default:
        criticalError(ERROR_UNREACHABLE_CODE);
    }
}

void OperationStateMenuSettings::onKeyPress(char key) {
    switch (key) {
    case IR_KEY_PREV_SCREEN:
        return appState.transitionOpState(OperationStateMenuProgram::create);
    case IR_KEY_NEXT_SCREEN:
        return appState.transitionOpState(OperationStateMenuActions::create);
    default:
        OperationStateMenu::onKeyPress(key);
    }
}
