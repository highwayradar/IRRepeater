#pragma once

#include <stddef.h>
#include <stdint.h>
#include "base_state.h"

// Represents a title and several rows of information.
// Logic is to be implemented by a child class.
class OperationStateSimpleMenu: public BaseOperationState {
private:
    size_t _cursorPosition;

protected:
    explicit OperationStateSimpleMenu(AppState &appState, size_t initialCursorPosition = 0);

    virtual void setCursorPosition(size_t nextPosition);

    inline size_t getCursorPosition() const {
        return _cursorPosition;
    }

    // Number of items in the menu
    virtual size_t getItemsCount() const = 0;

    // Append the title to the dest C-string.
    // Should never write more than maxWrite bytes.
    virtual size_t writeTitle(char *dest, size_t maxWrite) const = 0;

    // Append the menu item (row) #idx contents to the dest C-string.
    // Should never write more than maxWrite bytes.
    virtual size_t writeItem(char *dest, size_t maxWrite, size_t idx) const = 0;

public:
    // Overrides
    void draw() const override;
    void onKeyPress(char key) override;
    void onPeriodic(int32_t tm) override;
};
