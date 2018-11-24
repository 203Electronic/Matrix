#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include <FastLED.h>

class LED
{
public:
  LED();
  void SetBrightness(uint8_t b);
  void Fill(uint64_t WRGB);
  void Off(uint8_t index);
  void On(uint8_t index);
  void SetW(uint8_t index, uint8_t w);
  void SetRGB(uint8_t index, uint8_t R, uint8_t G, uint8_t B);
  void SetWRGB(uint8_t index, uint8_t W, uint8_t R, uint8_t G, uint8_t B);
  void SetHEX(uint8_t index, uint64_t WRGB);
  void SetPallette(uint8_t pallette, uint8_t index, uint8_t colour);
  void Update();
  void Rainbow();
  uint64_t ApplyGamma(uint64_t WRGB);
};

#endif
