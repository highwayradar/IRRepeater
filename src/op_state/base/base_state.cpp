#include "base_state.h"

BaseOperationState::BaseOperationState(AppState &appState): appState(appState) {}

bool BaseOperationState::disableIRCommands() const {
    // We don't need to disable IR commands for most states
    return false;
}

BaseOperationState::~BaseOperationState() = default;
