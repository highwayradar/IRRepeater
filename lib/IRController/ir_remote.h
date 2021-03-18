#pragma once

#include <stddef.h>

// IR remote keys definitions

constexpr char IR_KEY_CH_MINUS = 'D';
constexpr char IR_KEY_CH = 'C';
constexpr char IR_KEY_CH_PLUS = 'U';
constexpr char IR_KEY_REV = 'R';
constexpr char IR_KEY_FF = 'F';
constexpr char IR_KEY_PLAY = 'P';
constexpr char IR_KEY_MINUS = '-';
constexpr char IR_KEY_PLUS = '+';
constexpr char IR_KEY_EQ = 'E';
constexpr char IR_KEY_100_PLUS = 'H';
constexpr char IR_KEY_200_PLUS = 'T';

constexpr char IR_KEY_PREV_SCREEN = IR_KEY_CH_MINUS;
constexpr char IR_KEY_NEXT_SCREEN = IR_KEY_CH_PLUS;
constexpr char IR_KEY_BACK = IR_KEY_CH;
constexpr char IR_KEY_PREV_ITEM = IR_KEY_REV;
constexpr char IR_KEY_NEXT_ITEM = IR_KEY_FF;
constexpr char IR_KEY_DEC_VALUE = IR_KEY_MINUS;
constexpr char IR_KEY_INC_VALUE = IR_KEY_PLUS;
constexpr char IR_KEY_ENTER = IR_KEY_EQ;

inline bool isDigit(char signalValue) {
    return '0' <= signalValue && signalValue <= '9';
}

inline size_t getDigitValue(char signalValue) {
    return size_t(signalValue - '0');
}

#define CASE_ANY_DIGIT \
case '0': \
case '1': \
case '2': \
case '3': \
case '4': \
case '5': \
case '6': \
case '7': \
case '8': \
case '9'
