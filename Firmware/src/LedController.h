#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include <FastLED.h>
#include <elapsedMillis.h>

#define NUM_LEDS 125
#define RESET_DELAY 2000
#define FADE_SPEED 2

struct Colors {
    CRGB newCube = CRGB(0, 0, 255);
    CRGB cubeRemoved = CRGB(255, 0, 0);
    CRGB playing = CRGB(255, 0, 255);
    CRGB stopped = CRGB(0, 0, 0);
    CRGB buttonPressed = CRGB(0, 255, 0);
};

class LedController {
    public:
        LedController();
        void init();
        void handle();
        void flashColor(CRGB color);
        void setBaseColor(CRGB color);

    private:
        CRGB _leds[NUM_LEDS];
        CRGB _baseColor;
        bool _needsUpdate;
        int8_t _tick;
        void fadePixels();
};
