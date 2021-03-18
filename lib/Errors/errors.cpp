#include <Arduino.h>

[[noreturn]] void criticalError(int code) {
    while (true) {
        for (int i = 0; i < code; ++i) {
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
        }
        delay(1000);
    }
}
