//#include "FastLED.h"
//#define nleds 10
//CRGB leds[nleds];

void waiting_led(bool command) {
  // white light
  if(command == true){
    fill_solid(leds, nleds, /*CRGB::*/0xE1A024);
    FastLED.show();
  }
  // black color
  else {
    fill_solid(leds, nleds, CRGB::Black);
    FastLED.show();
  }
}


//void countdown_led() {
//  static int i = nleds - 1;
//  if (i == (nleds - 1))
//    fill_solid(leds, nleds, CRGB::Red);
//  if (i >= 0) {
//    EVERY_N_MILLISECONDS(1000) {
//      leds[i] = CRGB::Black;
//      FastLED.show();
////      Serial.println(i);
//      i--;
//    }
//  }
//}

void countdown_led(bool command) {
  static unsigned long timeTemp = millis();
  static int i = 0;
  if (command) {
      if (i <= nleds) {
        if ((millis() - timeTemp) > 1000)/*EVERY_N_MILLISECONDS(1000)*/ {
          leds[i] = CRGB::Black;
          leds[36 -i - 1] = CRGB::Black;
          FastLED.show();
//          Serial.println(i);
          timeTemp = millis();
          i++;
        } 
      } else if (i == 10) {
          i = 0; 
      }
  }
  if (!command) {
    fill_solid(leds, nleds, CRGB::Black);
    timeTemp = millis();
    i = 0;
  }
}

void driving_led(bool command) {
  if (command == true) {
    fill_gradient_RGB(leds, 60, CRGB::Magenta, CRGB::Yellow);
  }
}

void setLEDColor(CRGB::HTMLColorCode color) {
  fill_solid(leds, nleds, color);
  FastLED.show();
}
