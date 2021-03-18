#pragma once

#include <stddef.h>
#include "op_state/base/base_state.h"

// State capturing data and saving it into the memory
class OperationStateLearnIRAction: public BaseOperationState {
private:
    size_t slotIdx;

public:
    OperationStateLearnIRAction(AppState &appState, size_t slotIdx);
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);

    void draw() const override;
    void onKeyPress(char key) override;
    void onPeriodic(int32_t tm) override;
    bool disableIRCommands() const override;
};
