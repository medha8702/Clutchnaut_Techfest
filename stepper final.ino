#include <IBusBM.h>
#include<Servo.h>
#include <AccelStepper.h>
AccelStepper LeftBackWheel(1,22,23);
//AccelStepper LeftFrontWheel(1,42,43);
//AccelStepper RightBackWheel(1,41,40);
AccelStepper RightFrontWheel(1,24,25);
int wheelspeed=0;
IBusBM ibus;
int rcCH1=0;
int rcCH3=0;
int rcCH2 = 0; 
int rcCH4 = 0; 
int rcCH5 = 0;
int rcCH8 = 0; 
int rcCH7 = 0; 
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
//Servo servo06;

int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos; // Position to be updated
 // IBus object for receivig signals from transmitter/receiver



 
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}


void setup() {
  Serial.begin(115200);
  ibus.begin(Serial1);    // iBUS connected to Serial1: 19 (RX) and 18 (TX)
   LeftBackWheel.setMaxSpeed(1500);
   //LeftFrontWheel.setMaxSpeed(1500);
   //RightBackWheel.setMaxSpeed(1500);
   RightFrontWheel.setMaxSpeed(1500);
  
  servo01.attach(2);
  servo02.attach(4);
  servo03.attach(5);
  servo04.attach(9);
  servo05.attach(8);
  // Move robot arm to initial position
  servo1PPos = 90;
  servo01.write(servo1PPos);
  servo2PPos = 30;
  servo02.write(servo2PPos);
  servo3PPos = 60;
  servo03.write(servo3PPos);
  servo4PPos = 0;
  servo04.write(servo4PPos);
  servo5PPos = 150;
  servo05.write(servo5PPos);
  
}
void loop() {
  
   rcCH2 = readChannel(1, 0, 180, 0);//updown
   rcCH4 = readChannel(3, 0, 180, 0);//servo3,servo5
   rcCH5 = readChannel(4, 0, 180, 0);
   rcCH7 = readChannel(6, 0, 180, 0);
   rcCH8 = readChannel(7, 0, 180, 0);
  rcCH1 = readChannel(0, -100, 100, 0);//Leftright
  rcCH3 = readChannel(2, -100, 100, 0);//UpDown
  

                                
            
    servo1PPos=rcCH2;
    servo01.write(servo1PPos);
    servo2PPos=rcCH4;
    servo02.write(servo2PPos);
    servo3PPos=rcCH5;
    servo03.write(servo3PPos);
    servo4PPos=rcCH7;
    servo04.write(servo4PPos);
    servo5PPos=rcCH8;
    servo05.write(servo4PPos);
    Serial.print(rcCH2);
    Serial.print(" ");
    Serial.print(rcCH4);
    Serial.print(" ");
    Serial.print(rcCH5);
    Serial.print(" ");
    Serial.print(rcCH7);
    Serial.print(" ");
    Serial.print(rcCH8);
    Serial.println("");    
    delay(100);
        
          
         
 
  
          if ((rcCH1<15||rcCH1>-15)&&(rcCH3>15||rcCH3<-15))
          {   
               wheelspeed=15*rcCH3;
               movetofro();
            }
          
          if ((rcCH3<15||rcCH3>-15)&&(rcCH1>15||rcCH1<-15))
          {    
              if(rcCH1>15)
               { 
                 moveright();
                 wheelspeed=15*rcCH1;
                }
               if(rcCH1<-15)
                { 
                   moveleft();
                   wheelspeed=-15*rcCH1;
                  }
               
              
            }
           if(rcCH3<15&&rcCH3>-15&&rcCH1<15&&rcCH1>-15)
             {
              movestop();}
            
          
         
         
        
        
   //LeftFrontWheel.runSpeed();
   LeftBackWheel.runSpeed();
   RightFrontWheel.runSpeed();
   //RightBackWheel.runSpeed();
   Serial.print(rcCH1);
   Serial.print(" ");
   Serial.print(rcCH3);
   Serial.println("");
   
   

  
   
}
void movetofro() {
  //LeftFrontWheel.setSpeed(wheelspeed);
  LeftBackWheel.setSpeed(wheelspeed);
  RightFrontWheel.setSpeed(wheelspeed);}
  //RightBackWheel.setSpeed(wheelspeed);
  
void moveleft() {
 // LeftFrontWheel.setSpeed(-wheelspeed);
  LeftBackWheel.setSpeed(-wheelspeed);
  RightFrontWheel.setSpeed(wheelspeed);}
  //RightBackWheel.setSpeed(wheelspeed);
void moveright() {
  //LeftFrontWheel.setSpeed(wheelspeed);
  LeftBackWheel.setSpeed(wheelspeed);
  
  RightFrontWheel.setSpeed(-wheelspeed);}
  //RightBackWheel.setSpeed(-wheelspeed);
        

void movestop(){
  //LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);}
  //RightBackWheel.setSpeed(0);
  