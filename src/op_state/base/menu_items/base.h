#pragma once

#include <stddef.h>
#include <stdint.h>

class AppState;

// Base class for menu items (see OperationStateMenu)
class BaseOperationStateMenuItem {
protected:
    AppState &appState;
    explicit BaseOperationStateMenuItem(AppState &appState);

public:
    // Append the current menu item contents to the dest C-string.
    // Should never write more than maxWrite bytes.
    virtual size_t writeItem(char *dest, size_t maxWrite) const = 0;

    // The handler is only fired when this item is selected.
    virtual void onKeyPress(char key) = 0;

    // User selected the item or user just opened the menu and this item is the first
    // to be selected
    virtual void onEnter() = 0;

    // User deselected the item or switched to another screen
    virtual void onExit() = 0;
};
