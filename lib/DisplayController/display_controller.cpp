#include "display_controller.h"

DisplayController::DisplayController(uint8_t i2c_address) {
    oled.begin(&Adafruit128x64, i2c_address);
    oled.clear();
    oled.setFont(Adafruit5x7);
}

void DisplayController::showText_P(const char *ptext) {
    if (ptext == latest_ptext) {
        return;
    }
    latest_ptext = ptext;
    char buf[MAX_TEXT_LENGTH];
    strncpy_P(buf, ptext, sizeof(buf));
    showText(buf, true);
}

void DisplayController::showText(const char *text, bool _is_p) {
    if (strncmp(text, latest_string, sizeof(latest_string)) == 0) {
        return;
    }
    if (!_is_p) {
        latest_ptext = nullptr;
    }
    strncpy(latest_string, text, sizeof(latest_string));
    oled.set2X();
    oled.setCol(0);
    oled.setRow(0);
    for (const char *ch = text; *ch; ++ch) {
        if (*ch == '$') {
            ++ch;
            if (*ch == '1') {
                oled.set1X();
            } else if (*ch == '2') {
                oled.set2X();
            }
            continue;
        }
        if (*ch == '\n') {
            oled.clearToEOL();
        }
        oled.print(*ch);
    }
    uint8_t currentRow = oled.row();
    if (oled.col() != 0) {
        oled.clearToEOL();
        oled.println();
        ++currentRow;
    }
    if (currentRow < display_rows) {
        oled.clear(0, oled.displayWidth(), oled.row(), display_rows);
    }
    display_rows = currentRow;
}
