
#include <IRremote.h>
#include <LiquidCrystal.h>
 
LiquidCrystal lcd(P2_7, P2_6, P1_4, P1_5, P1_6, P1_7);

int RECV_PIN = P2_1;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  //Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.begin(16,2);
  lcd.print("Kumandadan Komut");
  lcd.setCursor(1,1);
  lcd.print("Bekleniyor...");
}

void loop() {
  if (irrecv.decode(&results)) {
   // Serial.println(results.value, HEX);
     if(results.value != (int)0xFFFFFF){
        lcd.clear();
        lcd.print("IR Kodu : ");
        lcd.print(results.value,HEX);
        
        lcd.setCursor(0,1);
        lcd.print("Key : ");
        getKey();
     }
    irrecv.resume();
  }
}

void getKey()
{
  switch(results.value) {
    case 0xFFA25D: 
    lcd.print("CH-");
    break;
 
    case 0xFF629D:
    lcd.print("CH");
    break;
 
    case 0xFFE21D:
    lcd.print("CH+");
    break;
 
    case 0xFF22DD:
    lcd.print("PREV");
    break;
 
    case 0xFF02FD:
    lcd.print("NEXT");
    break;
 
    case 0xFFC23D:
    lcd.print("PLAY/PAUSE");
    break;
 
    case 0xFFE01F:
    lcd.print("VOL-");
    break;
 
    case 0xFFA857:
    lcd.print("VOL+");
    break;
 
    case 0xFF906F:
    lcd.print("EQ");
    break;
 
    case 0xFF6897:
    lcd.print("0");
    break;
 
    case 0xFF9867:
    lcd.print("100+");
    break;
 
    case 0xFFB04F:
    lcd.print("200+");
    break;
 
    case 0xFF30CF:
    lcd.print("1");
    break;
 
    case 0xFF18E7:
    lcd.print("2");
    break;
 
    case 0xFF7A85:
    lcd.print("3");
    break;
 
    case 0xFF10EF:
    lcd.print("4");
    break;
 
    case 0xFF38C7:
    lcd.print("5");
    break;
 
    case 0xFF5AA5:
    lcd.print("6");
    break;
 
    case 0xFF42BD:
    lcd.print("7");
    break;
 
    case 0xFF4AB5:
    lcd.print("8");
    break;
 
    case 0xFF52AD:
    lcd.print("9");
    break;
  }
}
