
#include "command.h"

boolean Command::isValid()
{
  if(key > 0)
    return true;
  else
    return false;
}
  
void Command::decode(unsigned long value)
{
  switch(value) {
    case 0xFFA25D: 
    //key = "CH-";
    break;

    case 0xFF629D:
    //key = "CH";
    break;

    case 0xFFE21D:
    //key = "CH+";
    break;

    case 0xFF22DD:
    key = PREV;
    break;

    case 0xFF02FD:
    key = NEXT;
    break;

    case 0xFFC23D:
    // play
    break;

    case 0xFFE01F:
    key = DOWN;
    break;

    case 0xFFA857:
    key = UP;
    break;

    case 0xFF906F:
    //key = "EQ";
    break;

    case 0xFF9867:
    //key = "100+";
    break;

    case 0xFFB04F:
    //key = "200+";
    break;

    case 0xFF6897:
    key =   '0';
    break;

    case 0xFF30CF:
    key =   '1';
    break;

    case 0xFF18E7:
    key =   '2';
    break;
    
    case 0xFF7A85:
    key =   '3';
    break;

    case 0xFF10EF:
    key =   '4';
    break;

    case 0xFF38C7:
    key =   '5';
    break;

    case 0xFF5AA5:
    key =   '6';
    break;

    case 0xFF42BD:
    key =   '7';
    break;

    case 0xFF4AB5:
    key =   '8';
    break;

    case 0xFF52AD:
    key =   '9';
    break;
    
    default:
    key =  0;
 }
};
