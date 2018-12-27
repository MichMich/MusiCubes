#include "LedController.h"

LedController::LedController()
{
    _baseColor = CRGB::Black;
    _needsUpdate = false;
    _effect = Sparkle;
}

void LedController::init()
{
    FastLED.addLeds<NEOPIXEL, 8>(_leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5,750);

    FastLED.clear();
    FastLED.show();
}

void LedController::handle()
{
    _tick++;

    // if (_effect == Sparkle) {
    //     sparkle();
    // }
    if (_needsUpdate) {
        if (_tick % FADE_SPEED == 0) {
            fadePixels();
        }
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

void LedController::setEffectColor(CRGB color)
{
    _effectColor = color;
    _needsUpdate = true;
}

void LedController::setEffect(Effect effect)
{
    _effect = effect;
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

        // if (currentColor.r == targetColor.r &&
        //     currentColor.g == targetColor.g &&
        //     currentColor.b == targetColor.b) {
        //     _targetColors[ledIndex] = _baseColor;
        // }
    }
    if (stripUpdate) {
        FastLED.show();
    } else {
        _needsUpdate = false;
    }
}

void LedController::sparkle()
{
    if (_tick % SPARKLE_SPEED == 0) {
        _targetColors[random(NUM_LEDS)] = _effectColor;
        _needsUpdate = true;
    }
}