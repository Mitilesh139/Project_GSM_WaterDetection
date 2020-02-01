/*
 Make Voice Call

 This sketch, for the Arduino GSM shield, puts a voice call to
 a remote phone number that you enter through the serial monitor.
 To make it work, open the serial monitor, and when you see the
 READY message, type a phone number. Make sure the serial monitor
 is set to send a just newline when you press return.

 Circuit:
 * GSM shield
 * Voice circuit.
 With no voice circuit the call will send nor receive any sound


 created Mar 2012
 by Javier Zorzano

 This example is in the public domain.
 */
/*
// libraries
#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSMVoiceCall vcs;


GSMBand band;




String remoteNumber = "919494473959";  // the number you will call
char charbuffer[20];

void setup() {

  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


String newBand= "GSM_MODE_EGSM_DCS";// Your Band In My case That was 
  band.begin();
  Serial.println("Modem restarted.");
  String bandName = band.getBand(); // Get and print band name
  Serial.print("Current band:");
  Serial.println(bandName);
band.setBand(newBand);



  Serial.println("Make Voice Call");

  // connection state
  bool notConnected = true;
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized.");
  Serial.println("Enter phone number to call.");

}

void loop() {

  // add any incoming characters to the String:
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    // if it's a newline, that means you should make the call:
    if (inChar == '\n') {
      // make sure the phone number is not too long:
      if (remoteNumber.length() < 20) {
        // let the user know you're calling:
        Serial.print("Calling to : ");
        Serial.println(remoteNumber);
        Serial.println();

        // Call the remote number
        remoteNumber.toCharArray(charbuffer, 20);


        // Check if the receiving end has picked up the call
        if (vcs.voiceCall(charbuffer)) {
          Serial.println("Call Established. Enter line to end");
          // Wait for some input from the line
          while (Serial.read() != '\n' && (vcs.getvoiceCallStatus() == TALKING));
          // And hang up
          vcs.hangCall();
        }
        Serial.println("Call Finished");
        remoteNumber = "";
        Serial.println("Enter phone number to call.");
      } else {
        Serial.println("That's too long for a phone number. I'm forgetting it");
        remoteNumber = "";
      }
    } else {
      // add the latest character to the message to send:
      if (inChar != '\r') {
        remoteNumber += inChar;
      }
    }
  }
}*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "9494473959";
char phone[]="+919494473959";
void setup() {
  delay(7000); //delay for 7 seconds to make sure the modules get the signal
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);
  delay(1000);
}
void loop() {
  Serial.println("System inside loop...");
  callNumber();
  SendMessage();
  delay(1000);
}
void callNumber() {
  Serial.println("System inside callNumber...");
  
    sim.println("AT");delay(1000);
  _buffer = _readSerial();Serial.println (_buffer);
  
  sim.print (F("ATD"));
 /*sim.print ("ATD");*/
  sim.print (phone);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
    delay(30000);
}
void SendMessage()
{
  Serial.println ("Sending Message");
  sim.println("AT");delay(1000);
  _buffer = _readSerial();Serial.println (_buffer);
  sim.println("AT+CSCS");
  delay(1000);
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  _buffer = _readSerial();Serial.println (_buffer);
  Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Heyy Water is On;Look into it!!!!!!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
  Serial.println (SMS);
  Serial.println (_buffer);
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    Serial.println ("not in sim");
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    Serial.println ("yes in sim");
    return sim.readString();
  }
}
