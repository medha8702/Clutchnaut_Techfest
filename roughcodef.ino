#include <IBusBM.h>
#include <AccelStepper.h>
#include <Servo.h>

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

AccelStepper LeftBackWheel(1,-,-);   // (Type:driver, STEP, DIR) - Stepper1
AccelStepper LeftFrontWheel(1,-,-);  // Stepper2
AccelStepper RightBackWheel(1,-,-);  // Stepper3
AccelStepper RightFrontWheel(1,-,-); // Stepper4
int wheelSpeed = 1500;
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos; // Position to be updated


IBusBM ibus; // IBus object for receivig signals from transmitter/receiver
int rcCH1 = 0; 
int rcCH2 = 0; 
int rcCH3 = 0; 
int rcch5 = 0;
int rcCH5 = 0; 
int rcCH6 = 0; 
int rcch7=0;
 
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}



void setup() {
  Serial.begin(115200);
  IBus.begin(Serial1);    // iBUS connected to Serial1: 19 (RX) and 18 (TX)
  LeftFrontWheel.setMaxSpeed(3000);
  LeftBackWheel.setMaxSpeed(3000);
  RightFrontWheel.setMaxSpeed(3000);
  RightBackWheel.setMaxSpeed(3000);
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);
  servo05.attach(9);
  servo06.attach(10);
  // Move robot arm to initial position
  servo1PPos = 0;
  servo01.write(servo1PPos);
  servo2PPos = 120;
  servo02.write(servo2PPos);
  servo3PPos = 60;
  servo03.write(servo3PPos);
  servo4PPos = 0;
  servo04.write(servo4PPos);
  servo5PPos = 0;
  servo05.write(servo5PPos);
   
  


}

void loop() {
  rcCH1 = readChannel(0, -100, 100, 0);//Leftright
  rcCH2 = readChannel(1, -100, 100, 0);//servo1,servo4
  rcCH3 = readChannel(2, 0, 270, 0);//updown
  rcCH4 = readChannel(3, 0, 270, 0);//servo3,servo5
  rcCH5 = readChannel(4, 0, 270, 0);
   rcCH5 = readChannel(4, 0, 270, 0);
  rcCH7 = readSwitch(6, 0, 270, 0);

          while (rcch3!=0) {                           
            
          servo1PPos=rcch3;
           servo01.write(servo1PPos);
           delay(500);}
          
          rrch3=readChannel(2, 0, 270, 0);//servo1
          }          
      while (rcch4!=0) {                           
            
          servo2PPos=rcch4;
           servo02.write(servo2PPos);
           delay(500);
          
          rrch4=readChannel(3, 0, 270, 0);//servo1
          }        
          while (rcch5!=0) {                           
            
          servo3PPos=rcch5;
           servo03.write(servo3PPos);
           delay(500);}
          
          rrch5=readChannel(4, 0, 270, 0);//servo1
          }        
          while (rcch6!=0) {                           
            
          servo4PPos=rcch6;
           servo04.write(servo4PPos);
           delay(500);}
          
          rrch6=readChannel(5, 0, 270, 0);//servo1
          }   
         while( rcch7 ==true)
         {{if (angle!=required angle)
         servo5.write(angle++)  }}
         readSwitch(6, 0, 270, 0);   
       
                
      while (rcch1!=0) {
           wheelspeed=c*rcch1;  
          if (rrch1>0)
           moveForward();
          if (rrch4<0) 
          moveBackward();
        rcCH1 = readChannel(0, -100, 100, 0);}//servo3,servo5     
        
         while (rcch2!=0) {
          wheelspeed=c*rcch2;   
          if (rrch5>0)
          moveRight();
          if (rrch5<0)
          moveLeft();
        rcCH2 = readChannel(1, -100, 100, 0);}//servo2,servo 6
         
         if(rcch1==0)
        { wheelspeed=0;
         stopMoving();
         rcCH1 = readChannel(0, -100, 100, 0);}
         if(rcch2==0)
        { wheelspeed=0;
        stopMoving();
        rcCH2 = readChannel(1, -100, 100, 0);}
              
     
    
  
  LeftFrontWheel.runSpeed();
  LeftBackWheel.runSpeed();
  RightFrontWheel.runSpeed();
  RightBackWheel.runSpeed();
}
void moveForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveBackward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}


void moveRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelspeed);
  RightFrontWheel.setSpeed(-wheelspeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveLeft() {
  LeftFrontWheel.setSpeed(-wheelspeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelspeed);
}
void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}
