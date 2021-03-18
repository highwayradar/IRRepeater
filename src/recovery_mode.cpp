#include <Arduino.h>
#include <stdint.h>
#include <eeprom_utils.h>
#include "recovery_mode.h"
#include "constants.h"

static constexpr size_t ADDRESS = 1023;
static constexpr uint8_t VALUE = 0x13;

void performRecoveryMode() {
    if (eeprom_read_byte(reinterpret_cast<uint8_t *>(ADDRESS)) == VALUE) {
        eeprom_write_byte(reinterpret_cast<uint8_t *>(ADDRESS), 0);
        auto wipeMillis = millis() + PRE_WIPE_DELAY_MS;
        // Blink for some time before wiping the memory. Give user a chance to cancel.
        while (millis() < wipeMillis) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(250);
            digitalWrite(LED_BUILTIN, LOW);
            delay(250);
        }
        wipeUserEeprom();
        return;
    }
    eeprom_write_byte(reinterpret_cast<uint8_t *>(ADDRESS), VALUE);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    eeprom_write_byte(reinterpret_cast<uint8_t *>(ADDRESS), 0);
}
