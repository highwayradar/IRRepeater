#include "all_commands_disabled.h"

#include <new.h>
#include "app_state.h"

BaseOperationState *OperationStateAlertAllCommandsDisabled::create(void *dest, AppState *appState, const void *stash) {
    return new (dest) OperationStateAlertAllCommandsDisabled(*appState);
}

OperationStateAlertAllCommandsDisabled::OperationStateAlertAllCommandsDisabled(AppState &appState)
    : OperationStateAlert(appState) {}

size_t OperationStateAlertAllCommandsDisabled::writeMessage(char *dest, size_t maxWrite) const {
    return snprintf_P(
        dest,
        maxWrite,
        PSTR("Error\n$1\nAll program commands\nare disabled.")
    );
}
