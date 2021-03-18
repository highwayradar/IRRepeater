#pragma once

#include "op_state/all/menu/items/settings/ir_delay.h"
#include "op_state/all/menu/items/settings/carrier.h"
#include "op_state/base/menu.h"

// Settings menu
class OperationStateMenuSettings: public OperationStateMenu {
private:
    MenuItemSettingsCarrier vCarrier;
    MenuItemSettingsIRDelay vDelay;

public:
    explicit OperationStateMenuSettings(AppState &appState);
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);

protected:
    size_t getItemsCount() const override;
    size_t writeTitle(char *dest, size_t maxWrite) const override;
    BaseOperationStateMenuItem &getItem(size_t idx) override;
    const BaseOperationStateMenuItem &getItem(size_t idx) const override;
    void onKeyPress(char key) override;
};
