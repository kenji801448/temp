#define BLYNK_TEMPLATE_ID "TMPLjMYYFXqW"
#define BLYNK_DEVICE_NAME "ESP 8266 sha"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define PIXEL_PIN 12
#define PIXEL_COUNT 8
#define BUTTON_PIN 14
#define COLOR_STEP 50

#include "BlynkEdgent.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
boolean oldState = HIGH;
BlynkTimer timer;
int virtualPin;
int r = 0, g = 0, b = 0;
int zebra_r = 0, zebra_g = 0, zebra_b = 0;

int isButtonHolded() {

  boolean result = false;
  boolean newState = digitalRead(BUTTON_PIN);
  if (virtualPin || newState == HIGH) {
    Serial.printf("holded, virtualPin=%d\n", virtualPin);
    result = true;
  }
  oldState = newState;
  return result;
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {

  for (int i = 0; i < 20; i++) {
    int firstPixelHue = 0;     // First pixel starts at red (hue 0)
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void colorWrap(uint32_t color) {

  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
  delay(50);
}

void myTimerEvent() {

  if (isButtonHolded()) {
    theaterChaseRainbow(50);
    return ;
  }
  b += COLOR_STEP;
  if (b > 255) {
    b -= 256;
    g += COLOR_STEP;
    if (g > 255) {
      g -= 256;
      r += COLOR_STEP;
      if (r > 255) {
        r -= 256;
      }
    }
  }
  colorWrap(strip.Color(r, g, b));
}

void setup()
{
  BlynkEdgent.begin();
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
  timer.setInterval(1000L, myTimerEvent);
}

BLYNK_WRITE(V0) {

  virtualPin = param.asInt();
}

BLYNK_WRITE(V1) {

  zebra_r = param.asInt();
  colorWrap(strip.Color(zebra_r, zebra_g, zebra_b));
}

BLYNK_WRITE(V2) {

  zebra_g = param.asInt();
  colorWrap(strip.Color(zebra_r, zebra_g, zebra_b));
}

BLYNK_WRITE(V3) {

  zebra_b = param.asInt();
  colorWrap(strip.Color(zebra_r, zebra_g, zebra_b));
}

void loop() {

  BlynkEdgent.run();
  timer.run();
}
