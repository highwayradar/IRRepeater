#pragma once

#include "op_state/all/menu/items/program/duration.h"
#include "op_state/all/menu/items/program/enabled.h"
#include "op_state/all/menu/items/program/repetitions.h"
#include "op_state/all/menu/items/program/signal.h"
#include "op_state/base/menu.h"

// Program command (item) configuration
class OperationStateMenuProgramCommand: public OperationStateMenu {
private:
    size_t programIdx;
    MenuItemProgramEnabled vEnabled;
    MenuItemProgramSignal vSignal;
    MenuItemProgramDelay vDelay;
    MenuItemProgramRepetitions vRepetitions;

public:
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);
    OperationStateMenuProgramCommand(AppState &appState, size_t programIdx);

protected:
    size_t getItemsCount() const override;
    size_t writeTitle(char *dest, size_t maxWrite) const override;
    BaseOperationStateMenuItem &getItem(size_t idx) override;
    const BaseOperationStateMenuItem &getItem(size_t idx) const override;
    void onKeyPress(char key) override;
};