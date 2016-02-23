#include <IRremote.h>
#include <LiquidCrystal.h>

IRrecv irrecv(P2_1);
decode_results results;
LiquidCrystal lcd(P2_7, P2_6, P1_4, P1_5, P1_6, P1_7);


String amount = "00000000000000";
String formated = "00000000000000000";

String question = "________________";
char irChar;

char serialChar;

boolean isAvailable;

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn();
    lcd.begin(16,2);
    waitQuestion();
}

void loop()
{
    if(isAvailable)
      checkSerial();
    else{
        abortSerial();
        checkIR();
    }
}

void checkSerial(){
    if(Serial.available() > 0){
      serialChar = Serial.read();
      if(serialChar == 10){
        printQuestion();
      }
      else
        question += serialChar;
    }
}

void abortSerial(){
    if(Serial.available() > 0){
      serialChar = Serial.read();
      if(serialChar == 10){
       Serial.println("HATA : Onceki isteginizin sonuclanmasini bekleyin.");
      }
    }
}

void printQuestion(){
    if(question != ""){
      lcd.clear();
      lcd.print(question);
      isAvailable = false;
      printAmount();
    }
}

void checkIR(){
   if (irrecv.decode(&results)) {
       switch(results.value){
            case 0xFF6897:
              irChar =   '0';
            break;
            case 0xFF30CF:
              irChar =   '1';
            break;
            case 0xFF18E7:
              irChar =   '2';
            break;
            case 0xFF7A85:
              irChar =   '3';
            break;
            case 0xFF10EF:
              irChar =   '4';
            break;
            case 0xFF38C7:
              irChar =   '5';
            break;
            case 0xFF5AA5:
              irChar =   '6';
            break;
            case 0xFF42BD:
              irChar =   '7';
            break;
            case 0xFF4AB5:
              irChar =   '8';
            break;
            case 0xFF52AD:
              irChar =   '9';
            break;
            case 0xFFC23D:
              sendAnswer();
            break;
            case 0xFF22DD:
              amount.remove(amount.length() - 1);
              printAmount();
            default:
              irChar = 0;
            break;
       }

       if(irChar > 0){ // ir karakter gercekse
         if(amount.length() == 0 && irChar == '0'){ // kuruş haricindeki ilk deger basamagi
           // işlem yapma
         }
         else if(amount.length() < 11) {// max 10 basamak olacak sekilde ekle
             amount.concat(irChar);
         }

           printAmount();
       }
       
       irrecv.resume();
     }
}

void printAmount(){
    lcd.setCursor(0,1);
    lcd.print("             ");
    formatAmount();
    lcd.setCursor(14 - formated.length(),1);
    lcd.print(formated);
    lcd.print("TL");

}

void formatAmount(){
    formated = "";
    int size = amount.length();
    if (size < 3){
      formated += "0,";
      if(amount.charAt(0) != '\0'){
        if(amount.charAt(1) != '\0')
          formated += amount.charAt(1);
        else
          formated += "0";
        formated += amount.charAt(0);
      }
      else
        formated += "00";
    }
    else
      for(int i= 0; i < size ;i++)
        {
          if(i == (amount.length() - 2)) // kuruş
            formated += ","; 
          else if((i % 3) == (amount.length() + 1) % 3 && i) // kuruş
            formated += ".";
           
          formated += amount.charAt(i);
        }
}

void waitQuestion(){
    amount = ""; 
    question = "";
    serialChar = 10;
    irChar = 0;
    isAvailable = true;
    
    lcd.setCursor(0,0);
    lcd.print("     istek      ");
    lcd.setCursor(0,1);
    lcd.print(" bekleniyor...  ");    
}

void sendAnswer(){
      Serial.print("Girilen Tutar : ");
      formatAmount();
      Serial.print(formated);
      Serial.println(" TL");
      waitQuestion();
}
