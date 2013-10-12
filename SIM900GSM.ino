#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // RX, TX

// software equivalent of pressing the GSM shield "power" button
// original implemented by John Boxall of tronixstuff
void SIM900power()
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}

// originally implemented by John Boxall of tronixstuff
void callSomeone(String phoneNumber, int callLength)
{
  SIM900.println("ATD + " + phoneNumber + ";");
  delay(100);
}

void hangUp(){
  SIM900.println("ATH");
}

// originally implemented by John Boxall of tronixstuff
void sendSMS(String message, String phoneNumber)
{
  SIM900.print("AT+CMGF=1\r");// AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"" + phoneNumber + "\""); // recipient's mobile number, in international format
  delay(100);
  SIM900.println(message);   // message to send
  delay(100);
  SIM900.println((char)26);  // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);               // give module time to send SMS
  SIM900power();             // turn off module
}


String readSMS(int index){
  String message;
  SIM900.println("AT+CMGR=" + index);
  while(SIM900.peek() != null and SIM900.peek() != '\n'){
   message += SIM900.read();
  }
  return message;
}
void markUnread(int index){
  String message;
  SIM900.println("AT+CMGR=" + index);
  while(SIM900.peek() != null and SIM900.peek() != '\n'){
   message += SIM900.read();
  }
}

String[] listSMS(){
  // To be implemented
}

void deleteSMS(int index){
  SIM900.println("AT+CMGD=" + index);
}

