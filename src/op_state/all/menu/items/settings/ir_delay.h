#pragma once

#include "op_state/base/menu_items/int.h"

class MenuItemSettingsIRDelay: public OperationStateMenuItemInt {
private:
    size_t commandIdx{};

public:
    explicit MenuItemSettingsIRDelay(AppState &appState);

protected:
    size_t writeItem(char *dest, size_t maxWrite) const override;
    int32_t getMinValue() override;
    int32_t getMaxValue() override;
    void onChange(int32_t value) override;
    int32_t getStoredValue() const override;
};
