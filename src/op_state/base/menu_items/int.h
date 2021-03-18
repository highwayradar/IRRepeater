#pragma once

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "base.h"

// Integer input
class OperationStateMenuItemInt: public BaseOperationStateMenuItem {
private:
    int32_t bufferedValue = 0;
    bool isActive = false;

protected:
    explicit OperationStateMenuItemInt(AppState &appState);

    // Allowed boundaries
    virtual int32_t getMinValue() = 0;
    virtual int32_t getMaxValue() = 0;

    // Executed once during onExit phase, only if value changed.
    // The passed value is guaranteed to be valid.
    virtual void onChange(int32_t value) = 0;

    // Retrieve currently saved value
    virtual int32_t getStoredValue() const = 0;

    // Returns the value that must be displayed to the user
    int32_t getValue() const;

public:
    void onEnter() override;
    void onExit() override;
    void onKeyPress(char key) override;

private:
    inline int32_t getClampedValue();
};
