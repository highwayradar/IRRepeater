#pragma once

#include <stddef.h>
#include "op_state/base/base_state.h"

// State performing the program execution
class OperationStateRunProgram: public BaseOperationState {
public:
    explicit OperationStateRunProgram(AppState &appState);
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);

    void draw() const override;
    void onKeyPress(char key) override;
    void onPeriodic(int32_t tm) override;

private:
    // Settings to special value - don't display, but start with the first after initial countdown
    size_t commandIdx = 2 * Program::MAX_COMMANDS - 1;
    int32_t nextFireMs;

    // Move the the next active (non-disabled) command
    void moveCommandIdx();
};
