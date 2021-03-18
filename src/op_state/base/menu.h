#pragma once

#include <stddef.h>
#include <stdint.h>
#include "menu_items/base.h"
#include "simple_menu.h"

// A sophisticated menu with controllable indvidual items
class OperationStateMenu: public OperationStateSimpleMenu {
protected:
    explicit OperationStateMenu(AppState &appState, size_t initialCursorPosition = 0);

    // Get menu item by index
    virtual BaseOperationStateMenuItem &getItem(size_t idx) = 0;
    virtual const BaseOperationStateMenuItem &getItem(size_t idx) const = 0;

    // Overrides
    void onCreate() override;
    void onDestroy() override;
    void setCursorPosition(size_t nextPosition) override;
    size_t writeItem(char *dest, size_t maxWrite, size_t idx) const override;
    void onKeyPress(char key) override;

private:
    inline BaseOperationStateMenuItem &getCurrentItem() {
        return getItem(getCursorPosition());
    }

    inline const BaseOperationStateMenuItem &getCurrentItem() const {
        return getItem(getCursorPosition());
    };

};
