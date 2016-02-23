#ifndef Line_h
#define Line_h
#include <Energia.h>

class Line{
 public:
  Line(byte length);
  void replace(char chr);
  
  void clear();
  String getText();
  String getActiveLine1();
  String getActiveLine2();
  
  void cursorNext();
  void cursorPrev();
  void cursorUp();
  void cursorDown();
  
  byte cursorX;
  byte cursorY;

  byte length;
  String text = "                                                                             "; 
};

#endif
