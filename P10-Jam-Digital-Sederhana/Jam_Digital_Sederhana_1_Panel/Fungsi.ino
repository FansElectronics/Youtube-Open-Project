//-----------------------------------------
void RunText(String rt) {
  DateTime now = rtc.now();
  int p = rt.length() + 1;
  char textBuff[p];
  rt.toCharArray(textBuff, p);
  dmdFont(2);
  dmd.drawMarquee(textBuff, p, 32, 8);
  unsigned long timer = millis();
  bool ret = false;
  while (!ret) {
    if ((timer + textSpeed) < millis()) {
      now = rtc.now();
      dmdFont(2);
      ret = dmd.stepSplitMarquee(8, 15);
      TinyTime(now.hour(), now.minute(), 1);
      timer = millis();
    }
  }
}
//-----------------------------------------
void TinyTime(byte h, byte m, byte dot) {
  dmdFont(3);
  if (dot == 1) {
    TinyDot = true;
    BigDot = false;
  } else {
    TinyDot = false;
    dmd.drawChar( 15, 0, ':', 0 );
  }
  // Display JAM
  dmdText(1, 0, duaDigit(h));
  // Display MENIT
  dmdText(18, 0, duaDigit(m));
}
//-----------------------------------------
void BigTime(byte h, byte m, byte dot) {
  dmdFont(1);
  if (dot == 1) {
    BigDot = true;
    TinyDot = false;
  } else {
    BigDot = false;
    dmd.drawFilledBox( 15, 4, 16, 5, GRAPHICS_OR );
    dmd.drawFilledBox( 15, 10, 16, 11, GRAPHICS_OR );
  }
  // Display JAM
  dmdText(1, 0, duaDigit(h));
  // Display MENIT
  dmdText(18, 0, duaDigit(m));
}
//-----------------------------------------
void dmdFont(byte f) {
  switch (f) {
    case 1: dmd.selectFont(Number6x12); break;
    case 2: dmd.selectFont(System4x7); break;
    case 3: dmd.selectFont(System6x7); break;
  }
}
//-----------------------------------------
void dmdCenterText(int x, int y, String text) {
  int len = text.length() + 1;
  char dmdBuff[len];
  text.toCharArray(dmdBuff, len);
  dmd.drawStringCenter(DMD_WIDTH, x + 1, y, dmdBuff, len, 0);
}
//-----------------------------------------
void dmdCenterText(int dim, int x, int y, String text) {
  int len = text.length() + 1;
  char dmdBuff[len];
  text.toCharArray(dmdBuff, len);
  dmd.drawStringCenter(dim, x + 1, y, dmdBuff, len, 0);
}
//-----------------------------------------
void dmdText(int x, int y, String text) {
  int len = text.length() + 1;
  char dmdBuff[len];
  text.toCharArray(dmdBuff, len);
  dmd.drawString(x, y, dmdBuff, len, 0);
}

//-----------------------------------------
String duaDigit(int n) {
  if (n < 10) return "0" + String(n);
  else return String(n);
}
