#include <MyRealTimeClock.h>                                                                              
#define LEDPinGood P1_0 // LED For the Output indicator 
#define LEDPinBad  P1_6 // LED For the Output indicator


MyRealTimeClock myRTC(P2_0, P2_1, P2_2); // Pin assigned 



void setup()  {      
  Serial.begin(9600);
  pinMode(LEDPinGood, OUTPUT);                  // Optional if LED Indicator is required
  pinMode(LEDPinBad, OUTPUT);                   // Optional if LED Indicator is required
  

  /* To set the current time and date in specific format 
| Second 00 | Minute 59 | Hour 10 | Day 12 |  Month 07 | Year 2015 |
*/
  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);
}


void loop()  {                                                                                            
   
// Variable for time and accessing the one by one elements          
  int timeDiff, lastRead = 0;                                                                            
  myRTC.updateTime();                                                                                     
  delay(1500);                                                                                           
  timeDiff = myRTC.seconds - lastRead;                                                                   
  if ( timeDiff < 2 )   {                                                                                
    digitalWrite(LEDPinBad, HIGH);                                                                       
    } else  {                                                                                            
      digitalWrite(LEDPinGood, HIGH);                                                                    
      }                                                                                                  
  lastRead = myRTC.seconds;                                                                              
     Serial.print(myRTC.hours);
      Serial.print(" ");
      Serial.print(myRTC.minutes);
        Serial.print(" ");
      Serial.println(myRTC.seconds);
                                                                                                
   
          
  delay( 1000 );   // Delay for 2 Seconds                                                                                      
                                                                                                         
  digitalWrite(LEDPinGood, LOW);                                                                         
  digitalWrite(LEDPinBad, LOW);                                                                          
}                                                                                                         
                                                                                                             
