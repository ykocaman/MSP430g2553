const int ledsCount = 8;
byte leds[ledsCount] = {
  P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7};

const int digitsCount = 4;
byte digits[digitsCount] = {
  P2_0, P2_1, P2_2, P2_3};
  
const int buttonsCount = 3;
byte buttons[buttonsCount] = {
  P2_4, P2_5, P2_6};

byte patterns[11][8] = {
  {1,1,1,1,1,1,0,0},  // = 0
  {0,1,1,0,0,0,0,0},  // = 1
  {1,1,0,1,1,0,1,0},  // = 2
  {1,1,1,1,0,0,1,0},  // = 3
  {0,1,1,0,0,1,1,0},  // = 4
  {1,0,1,1,0,1,1,0},  // = 5
  {1,0,1,1,1,1,1,0},  // = 6
  {1,1,1,0,0,0,0,0},  // = 7
  {1,1,1,1,1,1,1,0},  // = 8
  {1,1,1,1,0,1,1,0},  // = 9
  {0,0,0,0,0,0,0,0}  // = 10 Null
};

int second = 0;
int minute = 0;
int hour = 0;

unsigned long ms = 0;
byte mode = 0; // 0 => çalışma, 1 => saat düzenleme, 2 => dakika düzenleme

boolean effect = false;
unsigned long effect_ms = 0;

void writeDigit(int number,int digit){
  // tüm ledleri temizle
  for(int i=0; i<digitsCount; i++){
    digitalWrite(digits[i], LOW);
  } 
  
  for(int i=0; i<ledsCount; i++){
    digitalWrite(leds[i], patterns[number][i]);
  } 
  
  if(digit == P2_1 && (!effect || mode > 0)) // çalışırken onlar basamagı ise : işareti koy
    digitalWrite(P1_7,HIGH);
  
  digitalWrite(digit, HIGH);
}

void screenRefresh(){
   if((millis() - effect_ms) > 500){
       effect_ms = millis();
       effect = !effect;
    }
    
    if(mode == 1 && effect){
      writeDigit(10,P2_0);
      writeDigit(10,P2_1);
      writeDigit(minute / 10,P2_2);
      writeDigit(minute % 10,P2_3);
    }
    else 
    if(mode == 2 && effect){
      writeDigit(hour / 10,P2_0);
      writeDigit(hour % 10,P2_1);
      writeDigit(10,P2_2);
      writeDigit(10,P2_3);
    }
    else{
      writeDigit(hour / 10,P2_0);
      writeDigit(hour % 10,P2_1);
      writeDigit(minute / 10,P2_2);
      writeDigit(minute % 10,P2_3);  
    }
}

void formatCheck(){
   if(second > 59){
      second = 0;
      minute++;
   }  
   if(minute > 59){
      minute = 0;
      if(mode == 0) // dakika ayar modunda ise saati artırmamak için
        hour++;
   }
   if(minute < 0){
     minute = 59;
   }
   if(hour > 23){
      hour = 0;
   }
   if(hour < 0){
      hour = 23;
   }
}

int buttonCheck(){
   for(int i=0; i<buttonsCount; i++){
     if(digitalRead(buttons[i]) == HIGH){
      while(digitalRead(buttons[i]) == HIGH){
          screenRefresh();
      }
       return buttons[i];
     }
  }
  return 0;  
}

void setup()
{
  // ledler
  for(int i=0; i<ledsCount; i++){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
  // basamaklar
  for(int i=0; i<digitsCount; i++){
    pinMode(digits[i], OUTPUT);
  } 
  // butonlar
  for(int i=0; i<buttonsCount; i++){
    pinMode(buttons[i], INPUT);
  } 
  ms =  millis();
  effect_ms = millis();
}

void loop()
{   
  switch(buttonCheck()){
     case P2_4:
        effect_ms = millis();
        mode++;
        if(mode > 2)
          mode = 0;
     break;
     case P2_5:
         if(mode == 1) // saat ayarı modu
           hour++;
         else
         if(mode == 2) // dakika ayarı modu
           minute++;
     break; 
     case P2_6:
         if(mode == 1) // saat ayarı modu
           hour--;
         else
         if(mode == 2) // dakika ayarı modu
           minute--;
     break; 
  }

  if(mode == 0) // çalışma modunda ise
    if((millis() - ms) > 999){
      ms = millis();
      second++;
    }
  
  formatCheck();
  screenRefresh();

}



