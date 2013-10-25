/* SIM900GSM.cpp - library for communicating over GSM
 * 2013-10-23: started by David Cary,
 * based on earlier work by
 * Mohammed of FabLabTulsa and
 * John Boxall of tronixstuff
 * https://github.com/carycode/SIM900GSM
 * https://github.com/Mohammed90/SIM900GSM
 * http://tronixstuff.com/2013/09/18/tutorial-arduino-sim900-gsm-modules/

Apparently (according to http://tronixstuff.com/tutorials/ )
this code is published under a
Creative Commons Attribution-Non Commercial-Share Alike v3.0 license.

Conversion to a library following the tutorial
"Writing a Library for Arduino" at
http://arduino.cc/en/Hacking/LibraryTutorial/

*/

#include "Arduino.h"
#include "SIM900GSM.h"


SIM900GSM::SIM900GSM( int RXpin, int TXpin, int button_pin )
: SoftwareSerial( RXpin, TXpin ),
_button_pin( button_pin )
{
}


// software equivalent of pressing the GSM shield "power" button
// original implemented by John Boxall of tronixstuff
void SIM900GSM::SIM900power()
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}

// originally implemented by John Boxall of tronixstuff
void SIM900GSM::callSomeone(String phoneNumber, int callLength)
{
  println("ATD + " + phoneNumber + ";");
  delay(100);
}

void SIM900GSM::hangUp(){
  println("ATH");
}

// originally implemented by John Boxall of tronixstuff
void SIM900GSM::sendSMS(String message, String phoneNumber)
{
  print("AT+CMGF=1\r");// AT command to send SMS message
  delay(100);
  println("AT + CMGS = \"" + phoneNumber + "\""); // recipient's mobile number, in international format
  delay(100);
  println(message);   // message to send
  delay(100);
  println((char)26);  // End AT command with a ^Z, ASCII code 26
  delay(100); 
  println();
  delay(5000);               // give module time to send SMS
  SIM900power();             // turn off module
}


String SIM900GSM::readSMS(int index){
  String message;
  println("AT+CMGR=" + index);
  while( (peek() != 0) and (peek() != '\n') ){
        message += read();
  }
  return message;
}
void SIM900GSM::markUnread(int index){
  String message;
  println("AT+CMGR=" + index);
  while( (peek() != 0) and (peek() != '\n') ){
   message += read();
  }
}

/*
String[] listSMS(){
  // To be implemented
}
*/

void SIM900GSM::deleteSMS(int index){
  println("AT+CMGD=" + index);
}

/* vim: set shiftwidth=4 expandtab ignorecase smartcase : */

