#pragma once

#include <stdint.h>

class AppState;

class BaseOperationState {
protected:
    AppState &appState;

    explicit BaseOperationState(AppState &appState);

public:
    virtual ~BaseOperationState();

    // Refresh screen contents
    virtual void draw() const = 0;

    // IR remote key press handler
    virtual void onKeyPress(char key) = 0;

    // Periodic jobs handler
    virtual void onPeriodic(int32_t tm) = 0;

    // Called right after constructor
    virtual void onCreate() {};

    // Called right before destructor
    virtual void onDestroy() {};

    // Whether IR commands handling should be disabled by app state
    virtual bool disableIRCommands() const;
};
