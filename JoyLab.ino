/*
  PicoGamepad

  Turn a Raspberry Pico 2040 into an HID gamepad

  Supports:
  128 Buttons
  8 Analog axes
  4 Hat switches

  created 28 June 2021
  by Jake Wilkinson (RealRobots)

  This example code is in the public domain.

  https://www.gitlab.com/realrobots/PicoGamepad
*/

#include <PicoGamepad.h>
#define gumbJ 0
#define gumb1 21
#define gumb2 20
#define gumb3 19
#define gumb4 16

#define gumbZ 11
#define gObrni 9
#define gKalibriraj 8
#define gumbQ 10
PicoGamepad gamepad;

// 16 bit integer for holding input values
int val;
//spremenljivke
int vrednostX;
int vrednostY;
int vrednostA;
int aKoncna;
int aMax;
int aKalib;

bool obrniVklop = 0;
bool kalibracijaVklop = 0;
bool kalibriranjeVklopljeno = 0;
bool obracanjeVklopljeno=0;
bool stanjeMotorja = 0;
void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  // X Potentiometer on pin 26
  pinMode(26, INPUT);
  // Y Potentiometer on pin 27
  pinMode(27, INPUT);

  // Button on pin
  pinMode(gumbJ, INPUT_PULLUP);
  pinMode(gumb1, INPUT_PULLUP);
  pinMode(gumb2, INPUT_PULLUP);
  pinMode(gumb3, INPUT_PULLUP);
  pinMode(gumb4, INPUT_PULLUP);

  //gumb za motorcek
  pinMode(gumbZ, INPUT_PULLUP);

  //gumba za kalibriranj in obracanje
  pinMode(gKalibriraj, INPUT_PULLUP);
  pinMode(gObrni, INPUT_PULLUP);
  pinMode(gumbQ, INPUT_PULLUP);


  //ledica
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);


  //motorcek
  pinMode(15, OUTPUT);

}

void loop() {


  stanjeMotorja = digitalRead(11);
  if (stanjeMotorja == LOW) {

    digitalWrite(15, HIGH);
  }
  else {
    digitalWrite(15, LOW);

  }

  vrednostX = analogRead(A0);
  vrednostA = analogRead(A2);
  vrednostY = analogRead(A1);
  Serial.println("vrendostBrez;");
  Serial.println(vrednostA);
  kalibracijaVklop = digitalRead(gKalibriraj);
  if (kalibracijaVklop == LOW) {
    int trenutnaA = analogRead(A2);
    kalibriranjeVklopljeno = HIGH;
    if (trenutnaA > aMax) {
      aMax = trenutnaA;
    }
  }
  if(!digitalRead(gumbZ)){
    kalibriranjeVklopljeno=LOW;
    obracanjeVklopljeno=LOW;
    }
    if(!digitalRead(gObrni)){
      obracanjeVklopljeno=HIGH;
    }
  if(!obracanjeVklopljeno){
  aKalib = map(vrednostA, 0, aMax, 0, 1023);
  Serial.println("AKalib;");
  Serial.println(aKalib);
  
  if (kalibriranjeVklopljeno) {
    aKoncna = map(aKalib, 0, 1023, 0, 255);
  } else {
    aKoncna = map(vrednostA, 0, 1023, 0, 255);
  }

  // Repeat with Y pin
    val = analogRead(28);
    val = map(aKoncna, 0, 255, -32767, 32767);
    gamepad.SetY(val);
  }
  else{
    
    aKalib = map(vrednostA, 0, aMax, 0, 1023);
    
  Serial.println("AKalib;");
  Serial.println(aKalib);
    
    if (kalibriranjeVklopljeno) {
    aKoncna = map(aKalib, 0, 1023, 255, 0);
  } else {
    aKoncna = map(vrednostA, 0, 1023, 255, 0);
  }
  // Repeat with Y pin
    val = analogRead(28);
    val = map(aKoncna, 255, 0, -32767, 32767);
    gamepad.SetY(val);
    
    }
  Serial.println("aKoncna;");
  Serial.println(aKoncna);
  
  analogWrite(20, aKoncna);
  digitalWrite(19, LOW);
  digitalWrite(21, LOW);




  /* // Get input value from Pico analog pin
    val = analogRead(26);

    // Map analog 0-1023 value from pin to max HID range -32767 - 32767
    val = map(val, 0, 1023, -32767, 32767);

    // Send value to HID object
    gamepad.SetX(val);

    // Repeat with Y pin
    val = analogRead(28);
    val = map(val, 0, 1023, -32767, 32767);
    gamepad.SetY(val);

    // Repeat with Z pin
    val = analogRead(28);
    val = map(val, 0, 1023, -32767, 32767);
    gamepad.SetZ(val);
  */

  //  gamepad.SetZ(val);
  //  gamepad.SetRx(val);
  //  gamepad.SetRy(val);
  //  gamepad.SetRz(val);
  //  gamepad.SetS0(val);
  //  gamepad.SetS1(val);

  // Set button 0 of 128 by reading button on digital pin 28
  gamepad.SetButton(0, !digitalRead(gumbJ));
  gamepad.SetButton(1, !digitalRead(gumb1));
  gamepad.SetButton(2, !digitalRead(gumb2));
  gamepad.SetButton(3, !digitalRead(gumb3));
  gamepad.SetButton(4, !digitalRead(gumb4));


  // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER
  // gamepad.SetHat(0, 8);


  // Send all inputs via HID
  // Nothing is send to your computer until this is called.
  gamepad.send_update();

  // Flash the LED just for fun
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(100);
}

void kalibriraj() {



}

void obrni() {

}
