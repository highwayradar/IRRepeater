#include <new.h>
#include <ir_data.h>
#include "signal_not_learned.h"

BaseOperationState *OperationStateAlertSignalNotLearned::create(void *dest, AppState *appState, const void *stash) {
    size_t irDataSlot = stash == nullptr ? 0 : *reinterpret_cast<const size_t *>(stash);
    return new (dest) OperationStateAlertSignalNotLearned(*appState, irDataSlot);
}

OperationStateAlertSignalNotLearned::OperationStateAlertSignalNotLearned(AppState &appState, size_t irDataSlot)
    : OperationStateAlert(appState), irDataSlot(irDataSlot) {}

size_t OperationStateAlertSignalNotLearned::writeMessage(char *dest, size_t maxWrite) const {
    return snprintf_P(
        dest,
        maxWrite,
        PSTR("Error\n$1\nIR signal %c\nis not learned"),
        IRDataSet::getLetterID(irDataSlot)
    );
}
