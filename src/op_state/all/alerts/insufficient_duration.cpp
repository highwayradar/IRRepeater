#include "insufficient_duration.h"

#include <Arduino.h>
#include <new.h>
#include "program_definition.h"

BaseOperationState *OperationStateAlertInsufficientDuration::create(void *dest, AppState *appState, const void *stash) {
    const auto *stashData = reinterpret_cast<const AlertInsufficientDurationStash *>(stash);
    return new (dest) OperationStateAlertInsufficientDuration(
        *appState,
        stashData->commandIdx,
        stashData->minimumDurationMsDiv10
    );
}

OperationStateAlertInsufficientDuration::OperationStateAlertInsufficientDuration(
    AppState &appState,
    size_t commandIdx,
    int minimumDurationMsDiv10
) : OperationStateAlert(appState),
    commandIdx(commandIdx),
    minimumDurationMsDiv10(minimumDurationMsDiv10)
{}

size_t OperationStateAlertInsufficientDuration::writeMessage(char *dest, size_t maxWrite) const {
    return snprintf_P(
        dest,
        maxWrite,
        PSTR("Error\n$1\nMinimum duration for\ncommand %c is %d.%02d.\nIncrease duration\nor reduce repetitions."),
        Program::getLetterID(commandIdx),
        minimumDurationMsDiv10 / 100,
        minimumDurationMsDiv10 % 100
    );
}
