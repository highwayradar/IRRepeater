#pragma once

#include <stddef.h>
#include "op_state/base/base_state.h"

// State confirming if the user really wants to reset everything
class OperationStateConfirmReset: public BaseOperationState {
public:
    explicit OperationStateConfirmReset(AppState &appState);
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);

    void draw() const override;
    void onKeyPress(char key) override;
    void onPeriodic(int32_t tm) override;
};
