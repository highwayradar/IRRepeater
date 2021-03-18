#pragma once

#include "op_state/base/menu_items/select.h"

class MenuItemProgramEnabled: public OperationStateMenuItemSelect {
private:
    size_t commandIdx;

public:
    MenuItemProgramEnabled(AppState &appState, size_t commandIdx);

protected:
    size_t writeItem(char *dest, size_t maxWrite) const override;
    size_t getItemsCount() override;
    void onChange(size_t value) override;
    size_t getStoredValue() const override;
};