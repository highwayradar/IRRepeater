#include <new.h>
#include <Arduino.h>
#include <errors.h>
#include <ir_remote.h>
#include "op_state/all/confirm_reset.h"
#include "actions.h"
#include "app_state.h"

BaseOperationState *OperationStateMenuActions::create(void *dest, AppState *appState, const void *stash) {
    return new (dest) OperationStateMenuActions(*appState);
}

OperationStateMenuActions::OperationStateMenuActions(AppState &appState)
    : OperationStateSimpleMenu(appState) {}

size_t OperationStateMenuActions::getItemsCount() const {
    return 2;
}

size_t OperationStateMenuActions::writeTitle(char *dest, size_t maxWrite) const {
    return snprintf_P(dest, maxWrite, PSTR("Actions"));
}

size_t OperationStateMenuActions::writeItem(char *dest, size_t maxWrite, size_t idx) const {
    switch (idx) {
    case ITEM_START:
        return snprintf_P(dest, maxWrite, PSTR("Start program"));
    case ITEM_RESET:
        return snprintf_P(dest, maxWrite, PSTR("Reset everything"));
    default:
        criticalError(ERROR_UNREACHABLE_CODE);
    }
}

void OperationStateMenuActions::onEnterPress() {
    switch (getCursorPosition()) {
    case ITEM_START:
        return start();
    case ITEM_RESET:
        return appState.transitionOpState(OperationStateConfirmReset::create);
    default:
        criticalError(ERROR_UNREACHABLE_CODE);
    }
}

void OperationStateMenuActions::onKeyPress(char key) {
    size_t digit;
    switch (key) {
    case IR_KEY_PREV_SCREEN:
        appState.transitionOpState(OperationStateMenuSettings::create);
        break;
    case IR_KEY_NEXT_SCREEN:
        appState.transitionOpState(OperationStateMenuLearnIR::create);
        break;
    case IR_KEY_PLAY:
        if (getCursorPosition() == ITEM_START) {
            start();
        }
        break;
    case IR_KEY_ENTER:
        onEnterPress();
        break;
    CASE_ANY_DIGIT:
        digit = getDigitValue(key);
        if (1 <= digit && digit <= getItemsCount()) {
            setCursorPosition(digit - 1);
        }
        break;
    default:
        OperationStateSimpleMenu::onKeyPress(key);
    }
}

void OperationStateMenuActions::start() {
    // Just in case alert gets thrown, set up the return point
    OperationStateAlert::setNextTransition(OpStateTransitionRequest::create(create, 0));
    for (size_t commandIdx = 0; commandIdx < Program::MAX_COMMANDS; ++commandIdx) {
        if (!appState.program.commands[commandIdx].validateOrAlert(appState)) {
            return;
        }
    }
    return appState.transitionOpState(OperationStateRunProgram::create);
}
