#pragma once

#include <stddef.h>
#include "op_state/base/alert.h"

class AppState;

class OperationStateAlertSignalNotLearned: public OperationStateAlert {
public:
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);
    explicit OperationStateAlertSignalNotLearned(AppState &appState, size_t irDataSlot);

protected:
    size_t writeMessage(char *dest, size_t maxWrite) const override;

private:
    size_t irDataSlot;
};
