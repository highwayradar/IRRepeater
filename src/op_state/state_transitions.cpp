#include "state_transitions.h"

#include <Arduino.h>
#include <errors.h>
#include "helpers.h"
#include "op_state/support.h"

static_assert(
    MAX_FACTORY_STASH == sizeof(StashUnion),
    "Incorrect MAX_FACTORY_STASH value"
);

OpStateTransitionRequest::OpStateTransitionRequest() : factory(nullptr) {}

OpStateTransitionRequest::OpStateTransitionRequest(
    FnOpStateFactory factory_,
    const void *stash_,
    size_t stashSize_
) : factory(factory_), stashSize(stashSize_) {
    if (stashSize_ > MAX_FACTORY_STASH) {
        criticalError(ERROR_TOO_LONG_STASH);
    }
    if (stash_ != nullptr && stashSize_ > 0) {
        memcpy(stash, stash_, stashSize_);
    }
}

OpStateTransitionRequest::OpStateTransitionRequest(const OpStateTransitionRequest &base):
    factory(base.factory),
    stashSize(base.stashSize) {
    memcpy(stash, base.stash, base.stashSize);
}

OpStateTransitionRequest &OpStateTransitionRequest::operator=(const OpStateTransitionRequest &base) {
    factory = base.factory;
    stashSize = base.stashSize;
    memcpy(stash, base.stash, base.stashSize);
    return *this;
}
