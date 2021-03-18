#include <Arduino.h>
#include <new.h>
#include "op_state/all/menu/learn_ir.h"
#include "app_state.h"
#include "op_state/state_transitions.h"
#include "recovery_mode.h"
#include "helpers.h"

DynamicContainer<AppState, sizeof(AppState)> appStateContainer;

AppState *buildInitialState(void *dest) {
    return new (dest) AppState();
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    performRecoveryMode();
    appStateContainer.putValue(buildInitialState);
    appStateContainer.getValue()->transitionOpState(OperationStateMenuLearnIR::create);
    appStateContainer.getValue()->load();
}

void loop() {
    appStateContainer.getValue()->onPeriodic();
}
