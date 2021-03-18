#pragma once

#include <stddef.h>
#include "op_state/base/alert.h"

class AppState;

struct AlertInsufficientDurationStash {
    size_t commandIdx;
    int minimumDurationMsDiv10;
};

class OperationStateAlertInsufficientDuration: public OperationStateAlert {
public:
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);
    explicit OperationStateAlertInsufficientDuration(
        AppState &appState,
        size_t commandIdx,
        int minimumDurationMsDiv10);

protected:
    size_t writeMessage(char *dest, size_t maxWrite) const override;

private:
    size_t commandIdx;
    int minimumDurationMsDiv10;
};
