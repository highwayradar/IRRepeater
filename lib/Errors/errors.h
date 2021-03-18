#pragma once

static const int ERROR_UNREACHABLE_CODE = 2;
static const int ERROR_TOO_LONG_STASH = 3;

[[noreturn]] void criticalError(int code);
