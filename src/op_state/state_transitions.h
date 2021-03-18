#pragma once

#include "constants.h"

class AppState;
class BaseOperationState;

// Must be equal to sizeof(StashUnion). Checked with static_assert later.
constexpr size_t MAX_FACTORY_STASH = 4;

// Definition for op state factory
typedef BaseOperationState *(*FnOpStateFactory)(void *, AppState *, const void *);

class OpStateTransitionRequest {
protected:
    FnOpStateFactory factory = nullptr;
    char stash[MAX_FACTORY_STASH] = { 0 };
    size_t stashSize = 0;

    OpStateTransitionRequest();
    OpStateTransitionRequest(
        FnOpStateFactory factory_,
        const void *stash_,
        size_t stashSize_
    );

public:
    OpStateTransitionRequest(const OpStateTransitionRequest &base);
    OpStateTransitionRequest &operator = (const OpStateTransitionRequest &base);

    template<typename TValue>
    static OpStateTransitionRequest create(FnOpStateFactory factory, const TValue &value) {
        return { factory, &value, sizeof(value) };
    }

    static OpStateTransitionRequest create(FnOpStateFactory factory) {
        return { factory, nullptr, 0 };
    }

    inline bool empty() const {
        return factory == nullptr;
    }

    inline const void *nonEmptyStash() const {
        return stashSize > 0 ? stash : nullptr;
    }

    inline void reset() {
        factory = nullptr;
    }

    friend class AppState;
};
