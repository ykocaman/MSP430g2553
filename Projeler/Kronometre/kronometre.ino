const int ledsCount = 8;
byte leds[ledsCount] = {
  P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7};

const int digitsCount = 4;
byte digits[digitsCount] = {
  P2_0, P2_1, P2_2, P2_3};
  
const int buttonsCount = 2;
byte buttons[buttonsCount] = {
  P2_4, P2_5};

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

int counter = 0;
unsigned long ms = 0;
boolean running = true;

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
  
  if(digit == P2_2 && !effect) // onlar basamagı ise . işareti koy
    digitalWrite(P1_7,HIGH);
  
  digitalWrite(digit, HIGH);
}

void writeNumber(int number){
   if((millis() - effect_ms) > 500){
       effect_ms = millis();
       effect = !effect;
    }
    if(!running && effect){
      writeDigit(10,P2_0);
      writeDigit(10,P2_1);
      writeDigit(10,P2_2);
      writeDigit(10,P2_3);
    }else{
      writeDigit((number / 1000)  % 10,P2_0);
      writeDigit((number / 100) % 10,P2_1);
      writeDigit((number  / 10) % 10,P2_2);
      writeDigit(number % 10,P2_3); 
    }
}

int buttonCheck(){
   for(int i=0; i<buttonsCount; i++){
     if(digitalRead(buttons[i]) == HIGH){
      while(digitalRead(buttons[i]) == HIGH){
          writeNumber(counter);
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
       running = !running;
     break;
     case P2_5:
       counter = 0;
     break; 
  }

  writeNumber(counter);

  if(running){
    if(counter > 9999){
      counter = 0;
    }
    if((millis() - ms) > 100){
      ms = millis();
      counter++;
    }
  }
}



