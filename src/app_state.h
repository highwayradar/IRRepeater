#pragma once

#include <stdint.h>
#include <display_controller.h>
#include <dynamic_container.h>
#include <ir_contoller.h>
#include <eeprom_utils.h>
#include "op_state/base/base_state.h"
#include "op_state/support.h"
#include "program_definition.h"
#include "settings_definitions.h"
#include "constants.h"
#include "op_state/state_transitions.h"


class AppState {
private:
    DynamicContainer<BaseOperationState, sizeof(OpStatesUnion)> opStateContainer;
    OpStateTransitionRequest stateTransitionRequest;
    void executePendingOpStateTransition();

public:
    DisplayController display;
    IRController ir;
    IRDataSet irData{};
    Settings settings;
    Program program{};
    EepromIRTimingsManager eeprom{};

    AppState();

    // Move to a next state
    void transitionOpState(const OpStateTransitionRequest &request);

    template<typename TValue>
    void transitionOpState(FnOpStateFactory factory, const TValue &value) {
        transitionOpState(OpStateTransitionRequest::create(factory, value));
    }

    void transitionOpState(FnOpStateFactory factory) {
        transitionOpState(OpStateTransitionRequest::create(factory));
    }

    // Perform periodic jobs
    void onPeriodic();

    // Operations with EEPROM
    void save() const;
    void load();
};
