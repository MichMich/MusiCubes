#include "LedController.h"

LedController::LedController()
{
    _baseColor = CRGB::Black;
    _needsUpdate = false;
}

void LedController::init()
{
    FastLED.addLeds<NEOPIXEL, 3>(_leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5,1000);

    FastLED.clear();
    FastLED.show();
}

void LedController::handle()
{
    if (_needsUpdate) {
        fadePixels();
    }
}

void LedController::flashColor(CRGB color) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        _leds[i] = color;
    }

    _needsUpdate = true;
}
void LedController::setBaseColor(CRGB color) {
    _baseColor = color;
    _needsUpdate = true;
}

void LedController::fadePixels()
{
    bool stripUpdate = false;
    for (uint8_t ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
        bool pixelUpdate = false;

        CRGB targetColor = _baseColor;
        CRGB currentColor = _leds[ledIndex];

        if (currentColor.r != targetColor.r) {
            currentColor.r += (currentColor.r < targetColor.r) ? 1 : -1;
            pixelUpdate = true;
        }
        if (currentColor.g != targetColor.g) {
            currentColor.g += (currentColor.g < targetColor.g) ? 1 : -1;
            pixelUpdate = true;
        }
        if (currentColor.b != targetColor.b) {
            currentColor.b += (currentColor.b < targetColor.b) ? 1 : -1;
            pixelUpdate = true;
        }

        if (pixelUpdate) {
            _leds[ledIndex] = currentColor;
            stripUpdate = true;
        }
    }
    if (stripUpdate) {
        FastLED.show();
    } else {
        _needsUpdate = false;
    }
}

