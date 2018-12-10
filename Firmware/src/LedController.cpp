#include "LedController.h"

LedController::LedController()
{
    _tick = 0;
    _ledBrightness = 0;
}

void LedController::init()
{
    FastLED.addLeds<NEOPIXEL, 3>(_leds, NUM_LEDS);

    for (int i = 0; i < NUM_LEDS; i++) {
        _targetColors[i] = CRGB::Black;
    }

    FastLED.show();

    setLightState(DefaultState);
}

void LedController::handle()
{
    _tick++;

    processPixels();
    fadePixels();

    if (_lightState != DefaultState && _resetTimer > RESET_DELAY) {
        setBrightness(_ledBrightness);
    }
}

void LedController::setBrightness(byte brightness)
{
    setLightState(DefaultState);
    _ledBrightness = brightness;
}

byte LedController::getBrightness()
{
    return _ledBrightness;
}

void LedController::coolEffect()
{
    setLightState(CoolEffect);
    _resetTimer = 0;
}

void LedController::heatEffect()
{
    setLightState(HeatEffect);
    _resetTimer = 0;
}

void LedController::fadePixels()
{
    // if (_tick % FADE_SPEED == 0) {
        bool stripUpdate = false;
        for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++) {
            bool pixelUpdate = false;

            CRGB targetColor = _targetColors[ledIndex];
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
        }
    // }
}

void LedController::processPixels()
{
    if (_processedPixels < NUM_LEDS) {
        CRGB newColor;

        switch(_lightState) {
            case HeatEffect:
                newColor = CRGB(255, 0, 0);
                break;
            case CoolEffect:
                newColor = CRGB(0, 0, 255);
                break;
            default:
                newColor = CRGB(64, 0, 64);
                break;
        }

        _targetColors[_currentPixelA] = newColor;
        _processedPixels++;

        _currentPixelA++;
        if (_currentPixelA == NUM_LEDS) _currentPixelA = 0;

        _targetColors[_currentPixelB] = newColor;
        _processedPixels++;

        if (_currentPixelB == 0) _currentPixelB = NUM_LEDS;
        _currentPixelB--;
    }

}

void LedController::setLightState(LightState state)
{
    _processedPixels = 0;
    // _currentPixelA = random(1, NUM_LEDS - 1);
    _currentPixelA = 80;
    _currentPixelB = _currentPixelA - 1;
    _lightState = state;
}

int LedController::overflow(int number, int add, int max) {
    if (add > 0 && number + add > max) return number % max;
    if (add < 0 && number < abs(add)) return number + max + add;

    return number + add;
}