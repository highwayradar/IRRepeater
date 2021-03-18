#include <display_controller.h>
#include <ir_remote.h>
#include "helpers.h"
#include "app_state.h"
#include "simple_menu.h"

OperationStateSimpleMenu::OperationStateSimpleMenu(AppState &appState, size_t initialCursorPosition)
    : BaseOperationState(appState), _cursorPosition(initialCursorPosition) {}

void OperationStateSimpleMenu::setCursorPosition(size_t nextPosition) {
    _cursorPosition = nextPosition;
}

void OperationStateSimpleMenu::draw() const {
    char menuText[DisplayController::MAX_TEXT_LENGTH];
    size_t offset = 0;
    size_t n_items = getItemsCount();
    // Put title
    offset += writeTitle(menuText + offset, sizeof(menuText) - offset);
    menuText[offset++] = '\n';
    menuText[offset++] = '$';
    menuText[offset++] = '1';
    // Put menu items
    for (size_t idx = 0; idx < n_items; ++idx) {
        // Put new line and cursor
        menuText[offset++] = '\n';
        menuText[offset++] = (idx == _cursorPosition) ? '>' : ' ';
        menuText[offset++] = ' ';
        // Put user item
        offset += writeItem(menuText + offset, sizeof(menuText) - offset, idx);
    }
    appState.display.showText(menuText);
}

void OperationStateSimpleMenu::onKeyPress(char key) {
    switch (key) {
    case IR_KEY_NEXT_ITEM:
        setCursorPosition((_cursorPosition + 1) % getItemsCount());
        break;
    case IR_KEY_PREV_ITEM:
        setCursorPosition((_cursorPosition + getItemsCount() - 1) % getItemsCount());
        break;
    default:
        // Do nothing
        break;
    }
}

void OperationStateSimpleMenu::onPeriodic(int32_t tm) {
    // Do nothing
}
