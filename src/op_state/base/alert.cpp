#include <display_controller.h>
#include <time_utils.h>
#include "alert.h"
#include "app_state.h"
#include "helpers.h"

// Storage for the next state transition
static OpStateTransitionRequest nextTransition = OpStateTransitionRequest::create(nullptr);

void OperationStateAlert::setNextTransition(const OpStateTransitionRequest &nextTransition_) {
    nextTransition = nextTransition_;
}

OperationStateAlert::OperationStateAlert(AppState &appState) :
    BaseOperationState(appState),
    returnMillis(signedMillis() + ALERT_DURATION_MS)
{}

void OperationStateAlert::draw() const {
    char text[DisplayController::MAX_TEXT_LENGTH];
    writeMessage(text, sizeof(text));
    appState.display.showText(text);
}

void OperationStateAlert::onKeyPress(char key) {
    transitionBack();
}

void OperationStateAlert::transitionBack() {
    appState.transitionOpState(nextTransition);
}

void OperationStateAlert::onPeriodic(int32_t tm) {
    if (tm > returnMillis) {
        transitionBack();
    }
}
