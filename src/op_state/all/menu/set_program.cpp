#include "set_program.h"

#include <new.h>
#include <Arduino.h>
#include <app_state.h>
#include <ir_data.h>
#include <constants.h>
#include <ir_remote.h>
#include "op_state/all/alerts/signal_not_learned.h"
#include "op_state/all/alerts/insufficient_duration.h"
#include "helpers.h"
#include "program_definition.h"

BaseOperationState *OperationStateMenuProgram::create(void *dest, AppState *appState, const void *stash) {
    size_t initialCursorPos = stash == nullptr ? 0 : *reinterpret_cast<const size_t *>(stash);
    return new (dest) OperationStateMenuProgram(*appState, initialCursorPos);
}

OperationStateMenuProgram::OperationStateMenuProgram(AppState &appState, size_t initialCursorPos)
    : OperationStateSimpleMenu(appState, initialCursorPos) {}

size_t OperationStateMenuProgram::getItemsCount() const {
    return Program::MAX_COMMANDS;
}

size_t OperationStateMenuProgram::writeTitle(char *dest, size_t maxWrite) const {
    return snprintf_P(dest, maxWrite, PSTR("Program"));
}

size_t OperationStateMenuProgram::writeItem(char *dest, size_t maxWrite, size_t idx) const {
    auto &cmd = appState.program.commands[idx];
    if (!cmd.isEnabled) {
        return snprintf_P(
            dest,
            maxWrite,
            PSTR("%c. Disabled"),
            Program::getLetterID(idx)
        );
    }
    if (idx == nowFiring) {
        return snprintf_P(
            dest,
            maxWrite,
            PSTR("%c. FIRE"),
            Program::getLetterID(idx)
        );
    }
    return snprintf_P(
        dest,
        maxWrite,
        PSTR("%c. %c  x%d  %2d.%02d sec"),
        Program::getLetterID(idx),
        IRDataSet::getLetterID(cmd.irSlotIdx),
        int(cmd.repetitions),
        int(cmd.commandDurationMsDiv10 / 100),
        int(cmd.commandDurationMsDiv10 % 100)
    );
}

void OperationStateMenuProgram::onKeyPress(char key) {
    size_t digit;
    switch (key) {
    case IR_KEY_PREV_SCREEN:
        return appState.transitionOpState(OperationStateMenuLearnIR::create);
    case IR_KEY_NEXT_SCREEN:
        return appState.transitionOpState(OperationStateMenuSettings::create);
    case IR_KEY_ENTER:
        return appState.transitionOpState(OperationStateMenuProgramCommand::create, getCursorPosition());
    case IR_KEY_PLAY:
        return testFire();
    CASE_ANY_DIGIT:
        digit = getDigitValue(key);
        if (1 <= digit && digit <= getItemsCount()) {
            setCursorPosition(digit - 1);
        }
        break;
    default:
        OperationStateSimpleMenu::onKeyPress(key);
    }
}


void OperationStateMenuProgram::testFire() {
    size_t cursorPos = getCursorPosition();
    const auto &cmd = appState.program.commands[cursorPos];
    if (!cmd.isEnabled) {
        return;
    }
    nowFiring = cursorPos;
    const auto &irSlot = appState.irData.slots[cmd.irSlotIdx];
    if (!irSlot.hasData()) {
        OperationStateAlert::setNextTransition(OpStateTransitionRequest::create(
            OperationStateMenuProgram::create,
            getCursorPosition()
        ));
        return appState.transitionOpState(
            OperationStateAlertSignalNotLearned::create,
            cmd.irSlotIdx
        );
    }
    int32_t firingDurationMs = irSlot.getFiringDurationMs(cmd.repetitions, appState.settings.irDelayMs);
    int32_t commandsDurationMs = cmd.getCommandDurationMs();
    if (firingDurationMs > commandsDurationMs) {
        OperationStateAlert::setNextTransition(OpStateTransitionRequest::create(
            OperationStateMenuProgram::create,
            getCursorPosition()
        ));
        int minimumDurationMsDiv10 = (firingDurationMs + 9) / 10;
        return appState.transitionOpState(
            OperationStateAlertInsufficientDuration::create,
            AlertInsufficientDurationStash { cursorPos, minimumDurationMsDiv10 }
        );
    }
    draw();
    if (!irSlot.isLoaded()) {
        appState.eeprom.loadIRData(irSlot, cmd.irSlotIdx);
    }
    delay(500);
    appState.ir.fire(irSlot, appState.settings.carrierKHz, cmd.repetitions, appState.settings.irDelayMs);
    delay(50);
    nowFiring = Program::MAX_COMMANDS;
}
