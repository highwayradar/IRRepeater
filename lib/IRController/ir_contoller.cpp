#include <time_utils.h>
#include <errors.h>
#include "ir_contoller.h"
#include "ir_remote.h"

IRController::IRController(uint8_t receiverPin): irReceiver(receiverPin) {
    irReceiver.enableIRIn();
}

void IRController::flush() {
    irReceiver.getResults();
    irReceiver.enableIRIn();
}

void IRController::delayNextReading() {
    blockReceiveUntil = signedMillis() + int32_t(500);
}

bool IRController::capture(IRData &dest) {
    if (!irReceiver.getResults()) {
        return false;
    }
    if (blockReceiveUntil > signedMillis()) {
        irReceiver.enableIRIn();
        return false;
    }
    dest.irTimingsSize = min(IRData::MAX_SIGNAL_LENGTH, recvGlobal.recvLength);
    uint16_t *timings_buf = dest.irTimings;
    for (bufIndex_t i = 1; i < dest.irTimingsSize; i++) {
        *(timings_buf++) = recvGlobal.recvBuffer[i];
    }
    *(timings_buf++) = 1000;
    delayNextReading();
    irReceiver.enableIRIn();
    return true;
}

char IRController::parseCommand(uint32_t value) {
    if (value == 0xFFA25D) return IR_KEY_CH_MINUS;
    if (value == 0xFF629D) return IR_KEY_CH;
    if (value == 0xFFE21D) return IR_KEY_CH_PLUS;
    if (value == 0xFF22DD) return IR_KEY_REV;
    if (value == 0xFF02FD) return IR_KEY_FF;
    if (value == 0xFFC23D) return IR_KEY_PLAY;
    if (value == 0xFFE01F) return IR_KEY_MINUS;
    if (value == 0xFFA857) return IR_KEY_PLUS;
    if (value == 0xFF906F) return IR_KEY_EQ;
    if (value == 0xFF6897) return '0';
    if (value == 0xFF9867) return IR_KEY_100_PLUS;
    if (value == 0xFFB04F) return IR_KEY_200_PLUS;
    if (value == 0xFF30CF) return '1';
    if (value == 0xFF18E7) return '2';
    if (value == 0xFF7A85) return '3';
    if (value == 0xFF10EF) return '4';
    if (value == 0xFF38C7) return '5';
    if (value == 0xFF5AA5) return '6';
    if (value == 0xFF42BD) return '7';
    if (value == 0xFF4AB5) return '8';
    if (value == 0xFF52AD) return '9';
    return '\0';
}

char IRController::getCommand() {
    if (!irReceiver.getResults()) {
        return '\0';
    }
    if (blockReceiveUntil > signedMillis()) {
        irReceiver.enableIRIn();
        return '\0';
    }
    irDecoder.decode();
    char result = parseCommand(irDecoder.value);
    irReceiver.enableIRIn();
    return result;
}

void IRController::fire(const IRData &data, uint8_t carrierKhz) {
    flush();
    irReceiver.disableIRIn();
    digitalWrite(LED_BUILTIN, HIGH);
    irSender.send(
        const_cast<uint16_t *>(data.irTimings),
        data.irTimingsSize,
        carrierKhz
    );
    digitalWrite(LED_BUILTIN, LOW);
    irReceiver.enableIRIn();
}

void IRController::fire(const IRData &data, uint8_t carrierKhz, uint8_t repetitions, int32_t intervalMs) {
    while (repetitions--) {
        fire(data, carrierKhz);
        if (repetitions) {
            delay(intervalMs);
        }
    }
}
