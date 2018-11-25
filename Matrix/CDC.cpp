#include "CDC.h"

extern LED LED;
extern MatrixSystem Matrix;
extern MIDI Midi;

CDC::CDC()
{

}

void CDC::Poll()
{
  if (CompositeSerial.available() > 0)
  {
    int device = CompositeSerial.peek() >> 4;
    if (device == 0)
    {
      Decode();
    }
    if (device > 0 && device < 8) //Modular
    {
      Decode();
    }
    else
    {
      //ERROR checking
    }
  }
}

void CDC::Decode()
{
  if(CompositeSerial.peek() > 0x0f) //ERROR checking
  return;

  switch (CompositeSerial.read()) //TODO uint8_t TO UINT4+UINT4
  {
    case 0x00://0
    LED.Off(Matrix.XYtoIndex(CompositeSerial.read(), CompositeSerial.read()));
    break;
    case 0x01://1
    LED.SetRGB(Matrix.XYtoIndex(CompositeSerial.read(), CompositeSerial.read()), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGB
    break;
    case 0x02://2
    LED.SetWRGB(Matrix.XYtoIndex(CompositeSerial.read(), CompositeSerial.read()), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYWRGB
    break;
    case 0x03://3
    LED.SetW(Matrix.XYtoIndex(CompositeSerial.read(), CompositeSerial.read()), CompositeSerial.read()); //XYW
    break;
    case 0x04://4
    LED.On(Matrix.XYtoIndex(CompositeSerial.read(), CompositeSerial.read())); //XY
    break;
    case 0x05://5
    LED.SetPallette(Matrix.XYtoIndex(CompositeSerial.read(), CompositeSerial.read()),CompositeSerial.read(), CompositeSerial.read()); //XYP
    break;
    case 0x0D://14
    SysexSet();
    break;
    case 0x0E://14
    SysexGet();
    break;
    case 0x0F://15
    MIDI();
    break;
  }
}

void CDC::SysexSet()
{
  switch (CompositeSerial.read() & 0x0F)
  {
    case 8:
    Matrix.Reset();
    break;
    case 9:
    Matrix.EnterBootloader();
    break;
    case 10:
    Matrix.InitializeDevice();
    break;
    case 20:
    Matrix.UpdateColourPaletteRGB();
    break;
    case 21:
    Matrix.UpdateColourPaletteWRGB();
    break;
    case 22:
    Matrix.ResetColourPalette();
    break;
    case 24:
    Matrix.SetGamma((bool)CompositeSerial.read());
    case 25:
    Matrix.UpdateCustomKeyMap();
    break;
    case 26:
    Matrix.ResetCustomKeyMap();
    break;
    case 30:
    Matrix.SetBrightness(CompositeSerial.read());
    break;
    case 31:
    Matrix.SetTouchSensitive(CompositeSerial.read());
    break;
  }
}

void CDC::SysexGet()
{
  switch(CompositeSerial.read() & 0x0F)
  {
    case 0:
    Matrix.GetDeviceInfo();
    break;
    case 1:
    Matrix.GetModuleCount();
    break;
    case 2:
    Matrix.GetModuleInfo();
    break;
    case 5:
    Matrix.GetAllParameter();
    break;
    case 20:
    Matrix.GetColorPaletteRGB();
    break;
    case 21:
    Matrix.GetColorPaletteWRGB();
    break;
    case 24:
    Matrix.GetGammaState();
    break;
    case 25:
    Matrix.GetCustomKeyMap();
    break;
    case 30:
    Matrix.GetBrightness();
    break;
    case 31:
    Matrix.GetTouchSensitive();
    break;
  }
}

void CDC::MIDI()
{
  int Mode = CompositeSerial.peek() >> 4;
  int Channel = CompositeSerial.read() & 0x0F;
  int Note = CompositeSerial.read();
  int Velocity = CompositeSerial.read();
  switch (Mode) {
    case 8:
    Midi.SentNoteOff(Channel, Note, Velocity);
    case 9:
    Midi.SentNoteOn(Channel, Note, Velocity);
  }
}
