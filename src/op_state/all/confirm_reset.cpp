#include "confirm_reset.h"

#include <new.h>
#include <display_controller.h>
#include <Arduino.h>
#include <ir_remote.h>
#include <eeprom_utils.h>

#include "app_state.h"

OperationStateConfirmReset::OperationStateConfirmReset(AppState &appState)
    : BaseOperationState(appState) {}

BaseOperationState *OperationStateConfirmReset::create(void *dest, AppState *appState, const void *stash) {
    return new (dest) OperationStateConfirmReset(*appState);
}

void OperationStateConfirmReset::draw() const {
    char text[DisplayController::MAX_TEXT_LENGTH];
    snprintf_P(text, sizeof(text), PSTR("Reset?\n$1\nThis action wipes\nall saved data.\nPress Play to proceed\nPress any other\nkey to cancel"));
    appState.display.showText(text);
}

void OperationStateConfirmReset::onKeyPress(char key) {
    if (key == IR_KEY_PLAY) {
        wipeUserEeprom();
        ((void(*)())(nullptr))();  // Restart Arduino
    } else {
        appState.transitionOpState(OperationStateMenuActions::create);
    }
}

void OperationStateConfirmReset::onPeriodic(int32_t tm) {}
