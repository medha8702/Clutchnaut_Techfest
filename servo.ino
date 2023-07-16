#include <Servo.h>
#include<IBusBM.h>

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
//Servo servo06;

int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos; // Position to be updated
IBusBM ibus; // IBus object for receivig signals from transmitter/receiver
//int rcCH1 = 0; 
int rcCH2 = 0; 
int rcCH4 = 0; 
int rcCH5 = 0;
int rcCH8 = 0; 
int rcCH6 = 0; 
//int rcch7=0;*/
 
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
// Read the channel and return a boolean value
/*bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}*/


void setup() {
  Serial.begin(115200);
  ibus.begin(Serial1); 
  servo01.attach(2);
  servo02.attach(4);
  servo03.attach(5);
  servo04.attach(6);
  servo05.attach(8);
  // Move robot arm to initial position
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 120;
  servo02.write(servo2PPos);
  servo3PPos = 90;
  servo03.write(servo3PPos);
  servo4PPos = 60;
  servo04.write(servo4PPos);
  servo5PPos = 0;
  servo05.write(servo5PPos);
   
  


}
void loop()
{
   rcCH2 = readChannel(1, -180, 180, 0);//updown
  rcCH4 = readChannel(3, -180, 180, 0);//servo3,servo5
   rcCH5 = readChannel(4, -180, 180, 0);
   rcCH6 = readChannel(5, 0, 180, 0);
  rcCH8 = readChannel(7, 0, 180, 0);

                                
            
          servo1PPos=rcCH2;
           servo01.write(servo1PPos);
           delay(50);
          
          rcCH2=readChannel(1, 0, 180, 0);//servo1
                 
                           
            
          servo2PPos=rcCH4;
           servo02.write(servo2PPos);
           delay(50);
          
          rcCH4=readChannel(3, 0, 180, 0);//servo1
                
                                
            
          servo3PPos=rcCH5;
           servo03.write(servo3PPos);
           delay(50);
          
          rcCH5=readChannel(4, 0, 180, 0);//servo1
          servo4PPos=rcCH6;
           servo04.write(servo4PPos);
           delay(50);
          
          rcCH6=readChannel(5, 0, 180, 0);     
                                  
            
          //servo5PPos=rcCH8;
          // servo05.write(servo4PPos);
          // delay(50);
          
          //rcCH8=readChannel(7, 0, 180, 0);//servo1
        
           
          
}
