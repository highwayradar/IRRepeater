#pragma once

#include <op_state/all/alerts/all_commands_disabled.h>
#include "op_state/all/alerts/insufficient_duration.h"
#include "op_state/all/alerts/signal_not_learned.h"
#include "op_state/all/confirm_reset.h"
#include "op_state/all/learn_ir_action.h"
#include "op_state/all/menu/actions.h"
#include "op_state/all/menu/learn_ir.h"
#include "op_state/all/menu/program_command.h"
#include "op_state/all/menu/set_program.h"
#include "op_state/all/menu/settings.h"
#include "op_state/all/run_program.h"

// A union to find the required amount of memory to store any operation state
union OpStatesUnion {
    OperationStateAlertAllCommandsDisabled _operationStateAlertAllCommandsDisabled;
    OperationStateAlertInsufficientDuration _operationStateAlertInsufficientDuration;
    OperationStateAlertSignalNotLearned _operationStateAlertSignalNotLearned;
    OperationStateLearnIRAction _operationStateLearnIRAction;
    OperationStateMenuLearnIR _operationStateMenuLearnIR;
    OperationStateMenuProgramCommand _operationStateMenuProgramCommand;
    OperationStateMenuProgram _operationStateMenuProgram;
    OperationStateMenuSettings _operationStateMenuSettings;
    OperationStateMenuActions _operationStateMenuActions;
    OperationStateRunProgram _operationStateRunProgram;
    OperationStateConfirmReset _operationStateConfirmReset;
};

// A union to find the minimum possible stash size for op state factories
union StashUnion {
    size_t _size_t;
    int _int;
    char _char;
    AlertInsufficientDurationStash _alertInsufficientDurationStash;
};
