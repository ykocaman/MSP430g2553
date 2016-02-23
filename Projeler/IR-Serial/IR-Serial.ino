
#include <IRremote.h>
#include <LCD.h>

int RECV_PIN = P2_1;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
      decodeKey();
      irrecv.resume();
  }
}



void decodeKey()
{
  switch(results.value) {
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
    //key = "PREV";
    if(startOfText < text.length())
            startOfText++;
    break;
 
    case 0xFF02FD:
    //key = "NEXT";
    if(startOfText > 0)
            startOfText--;
    break;
 
    case 0xFFC23D:
    //key = "PLAY";
    break;
 
    case 0xFFE01F:
    //key = "VOL-";
    break;
 
    case 0xFFA857:
    //key = "VOL+";
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
    text += '0';
    break;
 
    case 0xFF30CF:
    text += '1';
    break;
 
    case 0xFF18E7:
    text += '2';
    
    break;
 
    case 0xFF7A85:
    text += '3';
    break;
 
    case 0xFF10EF:
    text += '4';
    break;
 
    case 0xFF38C7:
    text += '5';
    break;
 
    case 0xFF5AA5:
    text += '6';
    break;
 
    case 0xFF42BD:
    text += '7';
    break;
 
    case 0xFF4AB5:
    text += '8';
    break;
 
    case 0xFF52AD:
    text += '9';
    break;
  }
}
