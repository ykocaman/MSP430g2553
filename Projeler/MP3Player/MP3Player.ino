/*
Hazırlayan: Yusuf KOCAMAN

P1_0 -> STOP - ON/OFF       P2_0 -> sd cs_pin
P1_1 -> UART                P2_1 -> BUG
P1_2 -> UART                P2_2 -> BUG
P1_3 -> EQU                 P2_3 -> PLAY/PAUSE
P1_4 -> lcd D4              P2_4 -> NEXT
P1_5 -> lcd D5, sd SCLK     P2_5 -> PREV
P1_6 -> lcd D6, sd D0       P2_6 -> lcd en
P1_7 -> lcd D7, sd D1       P2_7 -> lcd rs

*/

#include <pfatfs.h>
#include <pffconf.h>
#include "SPI.h" 
#include <LiquidCrystal.h>

// BUTTONS
#define BTN_STOP        P1_0
#define BTN_EQU         P1_3
#define BTN_PLAY        P2_3
#define BTN_NEXT        P2_4
#define BTN_PREV        P2_5

const uint8_t buttons[] = { BTN_STOP, BTN_EQU, BTN_PLAY, BTN_NEXT, BTN_PREV };
uint8_t button = 0;

// SD CARD
#define CS_PIN      P2_0                     

char content[6];
uint8_t rc;
unsigned short int br;
DIR dir;				
FILINFO fno;
char filename[13];

// LCD
LiquidCrystal lcd(P2_7, P2_6, P1_4, P1_5, P1_6, P1_7);

// STATE
#define ST_STOP        254 // ■
#define ST_PLAY        246 // >
#define ST_PAUSE       255 // P
#define ST_PREV        187 // <<
#define ST_NEXT        188 // >>
#define ST_OFF         100 // _>
#define ST_NOSD        110 // _>

// PLAYER
uint8_t  state               = ST_STOP;
uint8_t  track               = 0;
uint8_t  list                = 0;

uint8_t  second = 0;
uint8_t  minute = 0;
char     time[6];  

#define MS_BTN_PRESS      1000
#define MS_SLIDER         1000
unsigned long ms        = 0;
unsigned long button_ms = 0;
unsigned long effect_ms = 0;
unsigned long slider_ms = 0;

uint8_t  i,j,x     = 0;
uint8_t  slider    = 0;
boolean  slider_reverse = false;
boolean  effect;

byte equChar[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// MAIN SETUP
void setup()
{
    Serial.begin(9600);   
    lcd.begin(16,2); 
    // butonlar
    for(button=0; button<sizeof(buttons); button++){
      pinMode(buttons[button], INPUT_PULLUP);
    } 
    // equlazier
    for(i=0;i<8;i++){
       equChar[8-i] = 0b1111111;
       lcd.createChar(i, equChar);
    }
    effect = false;
}
      
// MAIN LOOP   
void loop()
{   
  checkButton();
  checkState();
  refreshLCD();
}


void checkState(){
  switch(state){
     case ST_PLAY:
     case ST_PAUSE:
     case ST_STOP:
     case ST_NOSD:
         list = readSD(); 
     break;
     case ST_OFF:

     break;
  }
}

void checkButton(){
   for(button=0; button<sizeof(buttons); button++){
       if(digitalRead(buttons[button]) == LOW){
         button_ms = millis();
         while(digitalRead(buttons[button]) == LOW){
             refreshLCD();
             // 1 saniyeden fazla basili tutunca
             if(millis() - button_ms > MS_BTN_PRESS)
                switch(buttons[button]){
                case BTN_NEXT:
                  state = ST_NEXT;
                break; 
                case BTN_PREV:
                  state = ST_PREV;
                break;
                }
         }
        // tek tik butonlar
            switch(buttons[button]){
               case BTN_PLAY:
                  if(state  != ST_PLAY)
                    state = ST_PLAY;
                  else
                    state = ST_PAUSE; 
               break; 
               case BTN_NEXT:
                 if(state == ST_NEXT){ // ileri sarmayi iptal et
                   if(millis() - button_ms < MS_BTN_PRESS)
                      state = ST_PLAY;
                 }else{ // bir parca ileri git
                      nextTrack();
                 }
               break; 
               case BTN_PREV:
                 if(state == ST_PREV){ // geri sarmayi iptal et
                    if(millis() - button_ms < MS_BTN_PRESS)
                       state = ST_PLAY;
                 }else{ // bir parca geri gel
                       prevTrack();
                 }
               break;
               case BTN_STOP:
                  resetTimer();
                  
                  if(state  == ST_STOP){
                    state = ST_OFF; 
                    track  = 0;
                  }
                  else
                    state = ST_STOP;
               break;
               case BTN_EQU:
                  effect = !effect;
               break;
            }
        // end switch
       }
   }
}

uint8_t readSD(){
    FatFs.begin(CS_PIN); 
    rc = FatFs.opendir(&dir, "");
    if (!rc){
      i = 0;
      for (;;i++) {
        rc = FatFs.readdir(&dir, &fno);
        if (rc || !fno.fname[0]) break;
        if (fno.fattrib & AM_DIR) {
            // ana dizin
        }else if(i == track)
        {
          readFile();
          strcpy(filename,fno.fname);
          filename[strlen(fno.fname)] = ' ';
          filename[strlen(fno.fname) + 1] = '\0';
        }
      }
    }
    
    if (rc) 
      state = ST_NOSD;
    else if(state == ST_NOSD)
      state = ST_STOP;
      
    FatFs.close();
    return i;
}


void readFile(){
   rc = FatFs.open(fno.fname);
   
   if(!rc){
     for (;;) {
       rc = FatFs.read(content, sizeof(content), &br);
       if (rc || !br) break;
     } 
     content[5] = '\0';
   }
}

void refreshLCD(){
    switch(state){
         case ST_PLAY:
         case ST_NEXT:
         case ST_PREV:
              checkTimer();
         case ST_PAUSE:
         case ST_STOP:
             lcd.setCursor(0,0);
             if(effect && state == ST_PLAY){ // Equ acik ise
                if(millis() - effect_ms > random(50,150)){
                  effect_ms = millis();
                  for(i=0;i<16;i++){
                     lcd.print(char(random(8)));
                  }
                }
             }else{
               lcd.print(char(state));
               lcd.print(' ');
               // baslangıcta toplam sureyi goster diger kosullarda anlik sureyi goster
               if(minute == 0 && second == 0){
                 lcd.print(content);
               }else{
                 lcd.print(time);
               }
               lcd.print(' ');
               lcd.print(track + 1);
               lcd.print('/');
               lcd.print(list);
               lcd.print("        ");
             }

             
             // dosya adidini yaz
             lcd.setCursor(0,1);
             for(j=0;j<5;j++)
               for(i=0;i<strlen(filename);i++){
                 x = j*strlen(filename) + i;
                  if(x >= slider && x <= slider + 16)
                    lcd.print(filename[i]);
               }
           
             if(millis() - slider_ms > MS_SLIDER){
               slider_ms = millis();
               
               if(!slider_reverse){
                   slider++;
                  if(slider > strlen(filename) + (15 - strlen(filename)))
                     slider_reverse = true;
               }else{
                   slider--;
                   if(slider == 0)
                     slider_reverse = false;
               }                    
             }
         break;
         case ST_OFF:
             lcd.clear();
         break;
         case ST_NOSD:
             lcd.setCursor(0,0);
             lcd.print(" Hafiza Kartini ");
             lcd.setCursor(0,1);
             lcd.print("   Takiniz    ");
         break;
      }
}

void nextTrack(){
    resetTimer();
    if(track  == list - 1)
      track = 0;
    else
      track++; 
}

void prevTrack(){
    resetTimer();
    if(track == 0)
      track = list - 1;
    else
      track--; 
}

void checkTimer(){
    if(state == ST_PREV && (millis() - ms) > 99){
      decTimer();
    }else {
      if(state == ST_NEXT  && (millis() - ms) > 99)
        incTimer();
      else if ((millis() - ms) > 999)
        incTimer();
    }
    generateTimer();
}

void incTimer(){
   ms = millis(); 
   second++;
   
   if(strcmp(time,content) == 0){
      state = ST_PLAY;
      nextTrack();
   }else{
     if(second > 59){
       second = 0;
       minute++;
     }
   }
}

void decTimer(){
   ms = millis(); 
   second--;
   if(second == 0){
     if(minute == 0){
        resetTimer();
        state = ST_STOP;
     }else{
       second = 59;
       minute--;
     }
   }   
}

void resetTimer(){
   ms = millis(); 
   second = 0;
   minute = 0; 
   slider_ms = millis();
   slider = 0;
   slider_reverse = false;
}

void generateTimer(){
     time[0] = (minute / 10) + '0';
     time[1] = (minute % 10) + '0';
     time[2] = ':';
     time[3] = (second / 10) + '0';
     time[4] = (second % 10) + '0';
     time[5] = '\0';
}

