#pragma once

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "base.h"

// Selection of predefined options. Stored as value 0..N-1
class OperationStateMenuItemSelect: public BaseOperationStateMenuItem {
private:
    size_t bufferedValue = 0;
    bool isActive = false;

protected:
    explicit OperationStateMenuItemSelect(AppState &appState);

    // Total number of values that can be selected
    virtual size_t getItemsCount() = 0;

    // Executed once during onExit phase, only if value changed.
    // The passed value is guaranteed to be valid.
    virtual void onChange(size_t value) = 0;

    // Retrieve currently saved value
    virtual size_t getStoredValue() const = 0;

    // Returns the value that must be displayed to the user
    size_t getValue() const;

public:
    void onEnter() override;
    void onExit() override;
    void onKeyPress(char key) override;
};
