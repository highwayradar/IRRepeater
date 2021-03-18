#pragma once

#include <stddef.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>

// A wrapper for the SSD1306Ascii library.
// Prevents repaints if the text hasn't changed; clears only empty areas to avoid flickering.
class DisplayController {
public:
    static const size_t MAX_TEXT_LENGTH = 120;

private:
    SSD1306AsciiAvrI2c oled;
    uint8_t display_rows = 0;

    const char *latest_ptext = nullptr;
    char latest_string[MAX_TEXT_LENGTH]{};

public:
    explicit DisplayController(uint8_t i2c_address);

    // Shows text for progmem strings
    void showText_P(const char *ptext);

    // Shows text on the screen
    // Add to the string $1 and $2 to change font size
    void showText(const char *text, bool _is_p = false);
};
