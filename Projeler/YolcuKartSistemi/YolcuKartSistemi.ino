
#include "SPI.h" 
#include "pfatfs.h"

#define cs_pin      P2_0             // chip select pin 
#define buffer_len 3             // size (in bytes) of read buffer 

  unsigned short int bw, br;//, i;
  char rbuffer[buffer_len];
  char wbuffer[buffer_len];
  char idbuffer[buffer_len];
  char idlast[buffer_len];

  int rc;
  DIR dir;				/* Directory object */
  FILINFO fno;			/* File information object */

#include <MyRealTimeClock.h>                                                                              

MyRealTimeClock myRTC(P2_0, P2_1, P2_2); // Pin assigned 

#include <LiquidCrystal.h>

LiquidCrystal lcd(P2_7, P2_6, P1_4, P1_5, P1_6, P1_7);

int amount = 0;
long unsigned int ms = 0;
int button = 0;
int type = 0;

void setup()
{
   Serial.begin(9600);
   lcd.begin(16,2);
   myRTC.setDS1302Time(00, 05, 21, 1, 11, 1, 2016);
   pinMode(P2_3,INPUT_PULLUP);
   pinMode(P2_4,INPUT_PULLUP);
   pinMode(P2_5,INPUT_PULLUP);

}

void loop()
{
  myRTC.updateTime();   

  getID();  

  FatFs.begin(cs_pin); 
  rc = FatFs.open("para.txt");  
  for (;;) {
    rc = FatFs.read(rbuffer, sizeof(rbuffer), &br);	/* Read a chunk of file */
    if (rc || !br) break;			/* Error or end of file */
  }
  
  convertAmount();
  convertText();
  
  if(amount > 0){
      if(digitalRead(P2_3) == LOW){
        if(strcmp(idbuffer,idlast) != 0){
          amount=amount - 2;
          type = 1;
        }else if(millis() - ms < 11000){
           amount=amount - 4;
           type = 3;
        }else if(millis() - ms < 46000){
           amount=amount - 1;
           type = 2;
        }else{
          amount=amount - 2;
          type = 1;
        }
        ms = millis();
        setID();
        convertText();
        writeAmount();
        
        button = 1;
      }

      if(digitalRead(P2_4) == LOW){
        if(strcmp(idbuffer,idlast) != 0){
          amount=amount - 2;
          type = 1;
        }else if(millis() - ms < 11000){
           amount=amount - 4;
           type = 3;
        }else if(millis() - ms < 46000){
           amount=amount - 1;
           type = 2;
        }else{
          amount=amount - 2;
          type = 1;
        }
        ms = millis();
        setID();
        convertText();
        writeAmount();
        
        button = 2;
      }
      
      if(digitalRead(P2_5) == LOW){
        if(strcmp(idbuffer,idlast) != 0){
          amount=amount - 2;
          type = 1;
        }else if(millis() - ms < 11000){
           amount=amount - 4;
           type = 3;
        }else if(millis() - ms < 46000){
           amount=amount - 1;
           type = 2;
        }else{
          amount=amount - 2;
          type = 1;
        }
        ms = millis();
        setID();
        convertText();
        writeAmount();
        
        button = 3;
      }
      
      if (!rc)
          printAmount();
  }
  else
    printYetersizBakiye();
  
  if(rc) die(rc);
  delay(500);
}

void convertAmount(){
    amount = (rbuffer[0] - '0') * 10 + (rbuffer[1] - '0');
}

void convertText(){
    wbuffer[0] = (amount / 10) + '0';
    wbuffer[1] = (amount % 10) + '0';
    wbuffer[2] = '\0';
}

void getID(){
  FatFs.begin(cs_pin); 
  rc = FatFs.open("id.txt");  
  for (;;) {
    rc = FatFs.read(idbuffer, sizeof(idbuffer), &br);	/* Read a chunk of file */
    if (rc || !br) break;			/* Error or end of file */
  }
}

void setID(){
  strcpy(idlast,idbuffer);
}

void printAmount(){
  lcd.clear();
  lcd.print("Bakiye: ");
  lcd.print(rbuffer);
  lcd.print(" TL");
  if(strcmp(rbuffer,wbuffer) != 0){
    lcd.setCursor(0,1);
    lcd.print("Kalan: ");
    lcd.print(wbuffer);
    lcd.print(" TL");
    serialPrint();
  }
}

void serialPrint(){
    Serial.print("Tarih : ");
    Serial.print(myRTC.dayofmonth); 
    Serial.print("/"); 
    Serial.print(myRTC.month); 
    Serial.print("/");
    Serial.print(myRTC.year + 16);
    Serial.print(" ");
    Serial.print(myRTC.hours); 
    Serial.print(":");
    Serial.print(myRTC.minutes); 
    Serial.print(":");
    Serial.print(myRTC.seconds); 
    Serial.print(" Kalan Tutar : ");
    Serial.print(wbuffer);
    Serial.print(" TL");
  
    Serial.print(" ID : ");
    Serial.print(idbuffer);
    
    Serial.print(" Button : ");
    Serial.print(button);
    
    Serial.print(" Tarife : ");
    Serial.println(type);
}

void writeAmount(){
    bw=0;
    for (uint16_t i=0;i<10;i++) {
      rc = FatFs.write(wbuffer, buffer_len, &bw);
      if (rc || !bw) break;
    }
    rc = FatFs.write(0, 0, &bw);  //Finalize write
}

void printYetersizBakiye(){
   lcd.clear();
   lcd.print("Yetersiz Bakiye");
}
void die (int pff_err)
{
   lcd.clear();
   lcd.print("Karti takiniz");
}
