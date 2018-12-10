#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include <FastLED.h>
#include <elapsedMillis.h>

#define NUM_LEDS 125
#define RESET_DELAY 2000

enum LightState {
  DefaultState,
  HeatEffect,
  CoolEffect
};

class LedController {
    public:
        LedController();
        void init();
        void handle();
        void setBrightness(byte brightness);
        byte getBrightness();
        void coolEffect();
        void heatEffect();

    private:
        CRGB _leds[NUM_LEDS];
        CRGB _targetColors[NUM_LEDS];
        elapsedMillis _resetTimer;
        unsigned long _tick;
        byte _ledBrightness;
        LightState _lightState;
        int _processedPixels;
        int _currentPixelA;
        int _currentPixelB;

        void fadePixels();
        void processPixels();
        void setLightState(LightState state);
        int overflow(int number, int add, int max);
};
