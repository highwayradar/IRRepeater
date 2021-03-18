#pragma once

#include <Arduino.h>

// Sometimes it is easier to work with signed numbers.
// This firmware isn't supposed to work longer than several hours, so casting to signed is fine here.
static inline int32_t signedMillis() {
    return int32_t(millis());
}
