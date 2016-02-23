#include "line.h"

Line::Line(byte length){
   length = length;
   clear();   
};

String Line::getText(){
   return text; 
}

void Line::clear(){
   cursorX = 0;
   cursorY = 0; 
   text = ""; 
}

String Line::getActiveLine1(){
   if(cursorY ==0) return "";
   return text.substring((cursorY - 1) *  length,((cursorY - 1) * length) + length); 
}

String Line::getActiveLine2(){
   return text.substring((cursorY - 1) * length + length,((cursorY - 1) * length) + 2 * length);  
}

void Line::cursorNext(){
    if(cursorX >= length - 1)
      cursorX++;
    else{
      cursorX = 0;
      cursorUp();
    }
}

void Line::cursorPrev(){
    if(cursorX > 0)
      cursorX--;
    else{
      cursorX = length;
      cursorDown();
    }
}

void Line::cursorDown(){
    if(cursorY > 0)
    {
      cursorY--;
    }
}

void Line::cursorUp(){
    if(cursorY < text.length() / length)
    {
      cursorY++;
    }
}


void Line::replace(char chr){
  switch(chr){
    case 13:
        for(;cursorX < length;cursorX++){
          text.setCharAt((cursorY * cursorX) + cursorX,(char)32);
        }
        cursorX = 0;
        cursorUp();
    break;
    default:
      //cursorNext();
      text += chr;
      //text.setCharAt((cursorY * cursorX) + cursorX - 1,chr);
    break;
  };
};

