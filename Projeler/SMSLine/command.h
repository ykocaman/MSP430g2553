#ifndef Command_h
#define Command_h
#include <Energia.h>

#define PREV 1
#define NEXT 2
#define UP 3
#define DOWN 4

class Command{
 public:
  void decode(unsigned long value);
  boolean isValid();
  char key;
};

#endif
