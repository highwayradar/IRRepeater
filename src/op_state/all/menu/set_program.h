#pragma once

#include "op_state/base/simple_menu.h"
#include "program_definition.h"

// Program menu
class OperationStateMenuProgram: public OperationStateSimpleMenu {
public:
    static BaseOperationState *create(void *dest, AppState *appState, const void *stash);
    explicit OperationStateMenuProgram(AppState &appState, size_t initialCursorPos = 0);

protected:
    size_t getItemsCount() const override;
    size_t writeTitle(char *dest, size_t maxWrite) const override;
    size_t writeItem(char *dest, size_t maxWrite, size_t idx) const override;
    void onKeyPress(char key) override;

private:
    size_t nowFiring = Program::MAX_COMMANDS;
    void testFire();
};