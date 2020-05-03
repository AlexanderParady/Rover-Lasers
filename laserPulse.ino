//Written by Andrew O'Reilly and Alexander Parady
//UCF Center for Microgravity Research | Florida Space Institute
//Last revised: 5/2/2020


#include <IRremote.h>
const int RECV_PIN = 7;
const int ledPin8 = 8;
const int ledPin9 = 9;
const int ledPin10 = 10;
const int ledPin11 = 11;
const int ledPin12 = 12;
const int ledPin6 = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;
const int SERIES = 1;
const int SYNC = 0;
int currentMode = -1;

void setup()
{
  irrecv.enableIRIn();
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (irrecv.decode(&results)) //decodes value sent my IR remote to IR sensor
  {

    irrecv.resume();   // resets the sensor and prepares for the next value
  }
  
  switch (results.value) // set mode from button press in variable currentMode
  {

    case 0xFF30CF:         //HEX value for the "1" button on remote
      currentMode = SYNC;
      break;

    case 0xFF6897:        //HEX value for the "0" value on the remote
      currentMode = SERIES;
      break;

    default:
      break;
  }

  switch (currentMode)   // control patterns based on mode
  {

    case SYNC:                    //LEDs pulse at the same time
      digitalWrite(ledPin8, HIGH);  //Send power to pin
      digitalWrite(ledPin9, HIGH);
      digitalWrite(ledPin10, HIGH);
      digitalWrite(ledPin11, HIGH);
      digitalWrite(ledPin12, HIGH);
      digitalWrite(ledPin6, HIGH);
      delay(500);                   //wait x amount of time (500 milliseconds)
      digitalWrite(ledPin8, LOW);   //Cut off power to pin
      digitalWrite(ledPin9, LOW);
      digitalWrite(ledPin10, LOW);
      digitalWrite(ledPin11, LOW);
      digitalWrite(ledPin12, LOW);
      digitalWrite(ledPin6, LOW);
      delay(500);
      break;

    case SERIES:                  //LEDs pulse in a chasing sequence
      digitalWrite(ledPin8, HIGH);  //Send power to pin
      delay(500);                   //wait x amount of time (500 milliseconds)
      digitalWrite(ledPin8, LOW);   //Cut off power to pin
      delay(500);
      digitalWrite(ledPin9, HIGH);
      delay(500);
      digitalWrite(ledPin9, LOW);
      delay(500);
      digitalWrite(ledPin10, HIGH);
      delay(500);
      digitalWrite(ledPin10, LOW);
      delay(500);
      digitalWrite(ledPin11, HIGH);
      delay(500);
      digitalWrite(ledPin11, LOW);
      delay(500);
      digitalWrite(ledPin12, HIGH);
      delay(500);
      digitalWrite(ledPin12, LOW);
      delay(500);
      digitalWrite(ledPin6, HIGH);
      delay(500);
      digitalWrite(ledPin6, LOW);
      delay(500);
      break;

    default:
      break;

  }
}
