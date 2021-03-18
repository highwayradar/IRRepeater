#pragma once

#include <ir_data.h>
#include "op_state/base/simple_menu.h"

// Actions meny
class OperationStateMenuActions: public OperationStateSimpleMenu {
public:
    static constexpr size_t ITEM_START = 0;
    static constexpr size_t ITEM_RESET = 1;

    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);
    explicit OperationStateMenuActions(AppState &appState);

protected:
    size_t getItemsCount() const override;
    size_t writeTitle(char *dest, size_t maxWrite) const override;
    size_t writeItem(char *dest, size_t maxWrite, size_t idx) const override;
    void onKeyPress(char key) override;

private:
    void onEnterPress();
    void start();
};