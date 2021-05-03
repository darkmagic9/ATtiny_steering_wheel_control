#include <EEPROM.h>

int led1 = 0;
int led2 = 1;
int led3 = 2;
int vr = A2;
int rom = 184;
int SW = 3;

int epvalue1, epvalue2, epvalue3;

void setup() {
  
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(SW, INPUT);

  controlLED(1, 1, 1);
  delay(3000);
  int output = readOutput(analogRead(vr));
  int statsw = digitalRead(SW);

  if (statsw == 1) {
    controlLED(1, 0, 0);
    delay(3000);
//    writeIntIntoEEPROM(10, readOutput(analogRead(vr)));    
    controlLED(0, 1, 0);
    delay(3000);
//    writeIntIntoEEPROM(20, readOutput(analogRead(vr)));
    controlLED(0, 0, 1);
    delay(3000);
//    writeIntIntoEEPROM(30, readOutput(analogRead(vr)));
    controlLED(1, 1, 1);
    delay(3000);
  }
  epvalue1 = 10;
  epvalue2 = 20;
  epvalue3 = 30;
//  epvalue1 = readIntFromEEPROM(10);
//  epvalue2 = readIntFromEEPROM(20);
//  epvalue3 = readIntFromEEPROM(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(vr);
  int output = map(val, 0, 1023, 0, 255);

  if (output >= (epvalue1 - 2) && output <= (epvalue1 + 2)) {
    controlLED(1, 0, 0);
  } else if (output >= (epvalue2 - 2) && output <= (epvalue2 + 2)) {
    controlLED(0, 1, 0);
  } else if (output >= (epvalue3 - 2) && output <= (epvalue3 + 2)) {
    controlLED(0, 0, 1);
  } else {
    controlLED(0, 0, 0);
  }
  delay(1);
}

void controlLED(int LED1, int LED2, int LED3) {
  digitalWrite(led1, LED1);
  digitalWrite(led2, LED2);
  digitalWrite(led3, LED3);
}

void writeIntIntoEEPROM(int address, int number)
{
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int readIntFromEEPROM(int address)
{
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}

int readOutput(int val) {
  int output = map(val, 0, 1023, 0, 255);  
  return output;
}
