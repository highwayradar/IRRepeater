#pragma once

#include <stdint.h>
#include <stddef.h>
#include <constants.h>
#include "op_state/base/base_state.h"
#include "op_state/state_transitions.h"


// State displaying a message to user. After a predefined period of time or
// once user presses a button on the remote, transitions state to the next requested.
class OperationStateAlert: public BaseOperationState {
private:
    static const int32_t ALERT_DURATION_MS = 10000;
    int32_t returnMillis;

protected:
    void transitionBack();

    // Append the message contents to the dest C-string.
    // Should never write more than maxWrite bytes.
    virtual size_t writeMessage(char *dest, size_t maxWrite) const = 0;

public:
    // We can't include the next transition request into the request for this alert (due to memory constrains).
    // So, before firing an alert, the next transition should be set using this method.
    static void setNextTransition(const OpStateTransitionRequest &nextTransition_);

    explicit OperationStateAlert(AppState &appState);

    void draw() const override;
    void onKeyPress(char key) override;
    void onPeriodic(int32_t tm) override;
};
