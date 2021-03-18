#include <new.h>
#include <Arduino.h>
#include <errors.h>
#include <ir_remote.h>
#include "app_state.h"
#include "program_definition.h"
#include "program_command.h"

BaseOperationState *OperationStateMenuProgramCommand::create(void *dest, AppState *appState, const void *stash) {
    size_t programIdx = stash == nullptr ? 0 : *reinterpret_cast<const size_t *>(stash);
    return new (dest) OperationStateMenuProgramCommand(*appState, programIdx);
}

OperationStateMenuProgramCommand::OperationStateMenuProgramCommand(AppState &appState, size_t programIdx)
    : OperationStateMenu(appState),
      programIdx(programIdx),
      vEnabled(appState, programIdx),
      vSignal(appState, programIdx),
      vDelay(appState, programIdx),
      vRepetitions(appState, programIdx) {}

size_t OperationStateMenuProgramCommand::getItemsCount() const {
    return 4;
}

size_t OperationStateMenuProgramCommand::writeTitle(char *dest, size_t maxWrite) const {
    return snprintf_P(dest, maxWrite, PSTR("Prog step %c"), Program::getLetterID(programIdx));
}

BaseOperationStateMenuItem &OperationStateMenuProgramCommand::getItem(size_t idx) {
    switch (idx) {
    case 0:
        return vEnabled;
    case 1:
        return vSignal;
    case 2:
        return vDelay;
    case 3:
        return vRepetitions;
    default:
        criticalError(ERROR_UNREACHABLE_CODE);
    }
}

const BaseOperationStateMenuItem &OperationStateMenuProgramCommand::getItem(size_t idx) const {
    switch (idx) {
    case 0:
        return vEnabled;
    case 1:
        return vSignal;
    case 2:
        return vDelay;
    case 3:
        return vRepetitions;
    default:
        criticalError(ERROR_UNREACHABLE_CODE);
    }
}

void OperationStateMenuProgramCommand::onKeyPress(char key) {
    if (key == IR_KEY_BACK) {
        appState.transitionOpState(OperationStateMenuProgram::create, programIdx);
    } else {
        OperationStateMenu::onKeyPress(key);
    }
}
