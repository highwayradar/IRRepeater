#include <new.h>
#include <Arduino.h>
#include <display_controller.h>
#include <time_utils.h>
#include <ir_remote.h>
#include "app_state.h"
#include "constants.h"
#include "run_program.h"

OperationStateRunProgram::OperationStateRunProgram(AppState &appState)
    : BaseOperationState(appState), nextFireMs(signedMillis() + DELAY_BEFORE_PROGRAM_MS) {}

BaseOperationState *OperationStateRunProgram::create(void *dest, AppState *appState, const void *stash) {
    return new (dest) OperationStateRunProgram(*appState);
}

void OperationStateRunProgram::draw() const {
    char text[DisplayController::MAX_TEXT_LENGTH];
    int32_t toNextFireMs = nextFireMs - signedMillis();
    size_t offset = snprintf_P(
        text,
        sizeof(text),
        PSTR("%S %d.%d\n$1"),
        commandIdx >= Program::MAX_COMMANDS ? PSTR("Wait") : PSTR("Run"),
        int(toNextFireMs / 1000),
        int(toNextFireMs / 100 % 10)
    );
    for (size_t i = 0; i < Program::MAX_COMMANDS; ++i) {
        const auto &cmd = appState.program.commands[i];
        if (cmd.isEnabled) {
            offset += snprintf_P(
                text + offset,
                sizeof(text) - offset,
                PSTR("\n%c %c. %c  x%d  %2d.%02d sec"),
                i == commandIdx ? '>' : ' ',
                Program::getLetterID(i),
                IRDataSet::getLetterID(cmd.irSlotIdx),
                int(cmd.repetitions),
                int(cmd.commandDurationMsDiv10 / 100),
                int(cmd.commandDurationMsDiv10 % 100)
            );
        }
    }
    appState.display.showText(text);
}

void OperationStateRunProgram::onKeyPress(char key) {
    if (key == IR_KEY_PLAY || key == IR_KEY_BACK) {
        return appState.transitionOpState(OperationStateMenuActions::create);
    }
}

void OperationStateRunProgram::onPeriodic(int32_t tm) {
    if (nextFireMs - tm > 75) {
        return;  // Too early
    }
    if (commandIdx >= Program::MAX_COMMANDS) {
        // Special value, don't fire on this iteration
        while (nextFireMs > signedMillis());  // Wait to the next state
        moveCommandIdx();
        return;
    }
    auto &cmd = appState.program.commands[commandIdx];
    auto &irData = appState.irData.slots[cmd.irSlotIdx];
    if (!irData.isLoaded()) {
        appState.eeprom.loadIRData(irData, cmd.irSlotIdx);
    }
    while (nextFireMs > signedMillis());  // Wait to fire
    appState.ir.fire(
        irData,
        appState.settings.carrierKHz,
        cmd.repetitions,
        appState.settings.irDelayMs
    );
    nextFireMs += cmd.getCommandDurationMs();
    moveCommandIdx();
}

void OperationStateRunProgram::moveCommandIdx() {
    do {
        commandIdx = (commandIdx + 1) % Program::MAX_COMMANDS;
    } while (!appState.program.commands[commandIdx].isEnabled);
}
