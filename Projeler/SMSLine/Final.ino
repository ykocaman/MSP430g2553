#include <IRremote.h>
#include <LiquidCrystal.h>
#include "line.h"
#include "command.h"

IRrecv irrecv(P2_1);
decode_results results;
Command command;
LiquidCrystal lcd(P2_7, P2_6, P1_4, P1_5, P1_6, P1_7);
Line line(16); 

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn();
    lcd.begin(16,2);
    lcd.blink();
    refreshLCD();
}

void loop()
{
   if (irrecv.decode(&results)) {
      command.decode(results.value);
      if(command.isValid()){
        
          switch(command.key){
          case PREV:
            line.cursorPrev();
          break;
          case NEXT:
            line.cursorNext();
          break;
          case UP:
            line.cursorUp();
          break;
          case DOWN:
            line.cursorDown();
          break;
          default:
            line.replace(command.key);
          }

        Serial.println(line.getActiveLine1());
         Serial.println(line.getActiveLine2());
          refreshLCD();
      }
      irrecv.resume();
  }
}

void refreshLCD(){
    lcd.clear();
   // if(line.getActiveLine1() == "")
   //   lcd.print("Mesajiniz :");
   // else
      lcd.print(line.getActiveLine1());
      
    lcd.setCursor(0,1);
    lcd.print(line.getActiveLine2()); 
    lcd.setCursor(line.cursorX,1);
}
