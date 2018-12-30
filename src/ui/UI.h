#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include "../core/USBmidi.h"
#include "../core/KeyPad.h"
#include "../core/LED.h"
#include "../core/Timer.h"
//#include "../protocol/MIDI.h"
//#include <USBComposite.h>

// struct Animation
// {
//   u8 Mode; //0 for full array are NUM_LEDS * FPS | 1 for xy mode XY+
//   u8 AnimationFPS;
//   char* AnimationData;
// };



class UI
{
public:
  UI();
  void enterFNmenu();
  void fnMenu();
  void exitFNmenu();
  void fnKeyAction();
  void fnRender();
  void showDeviceInfo();
  void showASCII(char ascii[], u32 colour, bool ignore_gamma = false);
  void playAnimation(char animation[]);
  u8 numSelector8bit(u8 currentNum, u32 colour, bool ignore_gamma = false);
  u8 numSelector6bit(u8 currentNum, u32 colour, bool ignore_gamma = false);
  u32 numSelectorRGB(u32 currentNum, u32 colour, bool ignore_gamma = false);
  u32 numSelectorWRGB(u32 currentNum, u32 colour, bool ignore_gamma = false);
  void renderText(char ascii[], u8 xy, u32 colour, bool ignore_gamma = false);
  void renderLetter(char ascii, u8 xy, u32 colour, bool ignore_gamma = false);
  void renderHalfHeightNum(u8 num, u8 xy, u32 colour, bool ignore_gamma = false);
  void renderHalfHeightDigit(u8 num, u8 xy, u32 colour, bool ignore_gamma = false);
  u8 binary8bitInput(u8 currentNum, u8 y, u32 colour, bool ignore_gamma = false);

  void easterEgg();
private:
  Timer uiTimer;
};

#endif
