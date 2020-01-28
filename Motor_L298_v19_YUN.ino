// sridel@free.fr SRIDEL ok le 3juin 2018
// this programm is intended to work on a local network wifi and need also another arduino Nano
//
// simple motor command by enabled D10 D11 D12
/* to NANO, motor commands
 * D12=0    D11=0   D10=0   Stop
 * D12=1    D11=1   D10=1   Forward
 * D12=1    D11=1   D10=0   Left
 * D12=1    D11=0   D10=1   Right
 * D12=1    D11=0   D10=0   Backward
 */

#define D10      10     // sending command to arduino NANO
#define D11      11     // sending command to arduino NANO
#define D12      12     // sending command to arduino NANO

int SonarA      = 0;     // SonarA
int SonarB      = 0;     // SonarB
int SonarCenter = 0;     // SonarCenter

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Servo.h>
int dac = 0;

Servo myServo1;
Servo myServo2;
unsigned long lastMilli = 0;         // loop timing 
unsigned long lastMilliPrint = 0;    // loop timing
String command;
int fullspeed = 80;
int halfspeed = 50;
int value;
int debug = 0;

YunServer server;

// *************************************
// *** SETUP                         ***
// *************************************
void setup() {

   analogReference(EXTERNAL);   // Current external ref is 3.3V
   if (debug) Serial.begin(115200);
myServo1.attach(A2);
myServo2.attach(A4);
myServo1.write(90);
myServo2.write(90);

/* 
 pinMode(SonarA,      INPUT_PULLUP); // sonar1 - A Side (from NANO D8 )
 pinMode(SonarCenter, INPUT_PULLUP); // sonar2 - Center (from NANO D9 )
 pinMode(SonarB,      INPUT_PULLUP); // sonar3 - B Side (from NANO D10 )
*/

//configure pin5 as an input and enable the internal pull-up resistor
 pinMode(5, INPUT_PULLUP);
 pinMode(6, INPUT_PULLUP); 
 pinMode(7, INPUT_PULLUP);

//configure 3 pin as output for motor (NANO Board)
 pinMode(D10, OUTPUT);
 pinMode(D11, OUTPUT);
 pinMode(D12, OUTPUT);
 digitalWrite(D10, LOW);
 digitalWrite(D11, LOW);
 digitalWrite(D12, LOW);
 
digitalWrite(13, LOW);
Bridge.begin();
digitalWrite(13, HIGH);
server.listenOnLocalhost();
server.begin();

//*********************
}// end setup       ***
//*********************



// *************************************
// *** LOOP                          ***
// *************************************
void loop() {

  // first, controlling sonar status (HIGH or LOW)
    SonarA      = digitalRead(5);    //read the value of D5 D6 D7 and put it in Sonar 1 2 3
    SonarCenter = digitalRead(6);
    SonarB      = digitalRead(7);

    /* to NANO, motor commands
 * D12=0    D11=0   D10=0   Stop      void MotorStop()
 * D12=1    D11=1   D10=1   Forward   void MotorFwd()
 * D12=1    D11=1   D10=0   Left      void MotorRev() 
 * D12=1    D11=0   D10=1   Right     void MotorRight()
 * D12=1    D11=0   D10=0   Backward  void MotorRev()
  */

  if (SonarCenter == HIGH)  {
      if (debug) Serial.println("SonarCenter");
      MotorStop();
      delay(200);
      MotorRev();
      delay(2000);
      MotorRight();
      delay(1000);
      MotorFwd();
      }
  if (SonarA == HIGH ) {
      if (debug) Serial.println("SonarA");
      MotorStop();
      delay(200);
      MotorLeft();
      delay(1000);
      MotorFwd();
      }
  if (SonarB == HIGH ) {
      if (debug) Serial.println("SonarB");
      MotorStop();
      delay(200);
      MotorRight();
      delay(1000);
      MotorFwd();
      }

  YunClient client = server.accept();
      if (client) {
        process(client);
        // all commands are embedded on the process "client"
        // SerialPrintInfo();  // display data on serial
        client.stop();
        }
      delay(50); 

//  ***********************************
} //*** end of loop                 ***   
//  ***********************************





// *************************************
// *** YUN CLIENT                    ***
// *************************************
void process(YunClient client) {
  String command = client.readStringUntil('/');



  
  // all these commands are receive on the web page of the yun        
      if (command == "stop") {
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        if (debug) Serial.println("Stop ");
        } // end "stop"
  
      if (command == "forward") {
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        delay(500);
        digitalWrite(D10, HIGH);
        digitalWrite(D11, HIGH);
        digitalWrite(D12, HIGH);
        if (debug) Serial.print("Forward ");
        } // end "forward"

      if (command == "left") {
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        delay(500);
        digitalWrite(D10, LOW);
        digitalWrite(D11, HIGH);
        digitalWrite(D12, HIGH);
        delay(1000);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        } // end "left"

      if (command == "right") {
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        delay(500);
        digitalWrite(D10, HIGH);
        digitalWrite(D11, LOW);
        digitalWrite(D12, HIGH);
        delay(1000);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        } // end "right"

      if (command == "backward") {
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
        delay(500);
        digitalWrite(D10, HIGH);
        digitalWrite(D11, LOW);
        digitalWrite(D12, HIGH);
        delay(3000);
        digitalWrite(D10, HIGH);
        digitalWrite(D11, HIGH);
        digitalWrite(D12, HIGH);      
        } // end "backward"

      if (command == "speed") {      //   Setup the fullspeed value of motor's PWM
        value = client.parseInt();
        if (debug) Serial.print(" Speed:");  Serial.print(value);
        fullspeed = value;
        halfspeed = fullspeed/2;
        if (debug) Serial.print(" Fullspeed :");  Serial.println(fullspeed);
        }

      if (command == "pan") {
        //front low
        panCommand(client);
        if (debug) Serial.print(" PAN:");  Serial.print(value);
        // wait for the servo to get there 
        delay(15);
        }
  
      if (command == "tilt") {
        tiltCommand(client);
        if (debug) Serial.print(" TILT:"); Serial.print(value);
        }

} // end yun client process
//***************







void panCommand(YunClient client) {
value = client.parseInt();
value = 180 - client.parseInt();
myServo1.write(value);
}

void tiltCommand(YunClient client) {
value = client.parseInt();
myServo2.write(value);
}












