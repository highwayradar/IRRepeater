#include <stdint.h>
#include <ir_remote.h>
#include "menu.h"

OperationStateMenu::OperationStateMenu(AppState &appState, size_t initialCursorPosition)
    : OperationStateSimpleMenu(appState, initialCursorPosition) {}

void OperationStateMenu::onCreate() {
    OperationStateSimpleMenu::onCreate();
    getCurrentItem().onEnter();
}

void OperationStateMenu::onDestroy() {
    getCurrentItem().onExit();
    OperationStateSimpleMenu::onDestroy();
}

void OperationStateMenu::setCursorPosition(size_t nextPosition) {
    getCurrentItem().onExit();
    OperationStateSimpleMenu::setCursorPosition(nextPosition);
    getCurrentItem().onEnter();
}

size_t OperationStateMenu::writeItem(char *dest, size_t maxWrite, size_t idx) const {
    return getItem(idx).writeItem(dest, maxWrite);
}

void OperationStateMenu::onKeyPress(char key) {
    switch (key) {
    case IR_KEY_INC_VALUE:
    case IR_KEY_DEC_VALUE:
    case IR_KEY_ENTER:
    case IR_KEY_PLAY:
    CASE_ANY_DIGIT:
        getCurrentItem().onKeyPress(key);
        break;
    default:
        OperationStateSimpleMenu::onKeyPress(key);
    }
}
