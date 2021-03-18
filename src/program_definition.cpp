#include "op_state/all/alerts/signal_not_learned.h"
#include "op_state/all/alerts/insufficient_duration.h"
#include "program_definition.h"
#include "app_state.h"

bool ProgramCommand::validateOrAlert(AppState &appState) const {
    if (!isEnabled) {
        return true;
    }
    const auto &irSlot = appState.irData.slots[irSlotIdx];
    if (!irSlot.hasData()) {
        appState.transitionOpState(OperationStateAlertSignalNotLearned::create, irSlotIdx);
        return false;
    }
    int32_t firingDurationMs = irSlot.getFiringDurationMs(repetitions, appState.settings.irDelayMs);
    int32_t commandsDurationMs = getCommandDurationMs();
    if (firingDurationMs > commandsDurationMs) {
        int minimumDurationMsDiv10 = (firingDurationMs + 9) / 10;
        appState.transitionOpState(
            OperationStateAlertInsufficientDuration::create,
            AlertInsufficientDurationStash{irSlotIdx, minimumDurationMsDiv10}
        );
        return false;
    }
    return true;
}

bool Program::validateOrAlert(AppState &appState) const {
    size_t enabledCount = 0;
    for (size_t commandIdx = 0; commandIdx < Program::MAX_COMMANDS; ++commandIdx) {
        const auto &cmd = appState.program.commands[commandIdx];
        enabledCount += cmd.isEnabled;
        if (!cmd.validateOrAlert(appState)) {
            return false;
        }
    }
    if (enabledCount == 0) {
        appState.transitionOpState(OperationStateAlertAllCommandsDisabled::create);
        return false;
    }
    return true;
}
