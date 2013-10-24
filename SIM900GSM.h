
/* SIM900GSM.h - library for communicating over GSM
 * 2013-10-23: started by David Cary,
 * based on earlier work by
 * Mohammed of FabLabTulsa and
 * John Boxall of tronixstuff
 * https://github.com/Mohammed90/SIM900GSM
 * https://github.com/carycode/SIM900GSM
 * http://tronixstuff.com/2013/09/18/tutorial-arduino-sim900-gsm-modules/

Apparently (according to http://tronixstuff.com/tutorials/ )
this code is published under a
Creative Commons Attribution-Non Commercial-Share Alike v3.0 license.

*/
#ifndef SIM900GSM_h
#define SIM900GSM_h

#include "Arduino.h"
#include <SoftwareSerial.h>

// is ": public SoftwareSerial" really the right thing to do here?
class SIM900GSM: public SoftwareSerial {
    public:
        SIM900GSM( int RXpin, int TXpin, int button_pin );
        // software equivalent of pressing the GSM shield "power" button
        void SIM900power();
        void callSomeone(String phoneNumber, int callLength);
        void hangUp();
        void sendSMS(String message, String phoneNumber);
        String readSMS(int index);
        void markUnread(int index);
        // String[] listSMS();
        void deleteSMS(int index);

    private:
        int _RXpin;
        int _TXpin;
        int _button_pin;
};

/* vim: set shiftwidth=4 expandtab ignorecase smartcase : */

#endif

