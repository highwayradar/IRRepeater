#pragma once

#include <stddef.h>
#include "op_state/base/alert.h"

class AppState;

class OperationStateAlertAllCommandsDisabled: public OperationStateAlert {
public:
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);
    explicit OperationStateAlertAllCommandsDisabled(AppState &appState);

protected:
    size_t writeMessage(char *dest, size_t maxWrite) const override;
};
