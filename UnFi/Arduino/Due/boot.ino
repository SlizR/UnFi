//    UUUUUUUU     UUUUUUUU                 FFFFFFFFFFFFFFFFFFFFFF  iiii  
//    U::::::U     U::::::U                 F::::::::::::::::::::F i::::i 
//    U::::::U     U::::::U                 F::::::::::::::::::::F  iiii  
//    UU:::::U     U:::::UU                 FF::::::FFFFFFFFF::::F        
//     U:::::U     U:::::Unnnn  nnnnnnnn      F:::::F       FFFFFFiiiiiii 
//     U:::::D     D:::::Un:::nn::::::::nn    F:::::F             i:::::i 
//     U:::::D     D:::::Un::::::::::::::nn   F::::::FFFFFFFFFF    i::::i 
//     U:::::D     D:::::Unn:::::::::::::::n  F:::::::::::::::F    i::::i 
//     U:::::D     D:::::U  n:::::nnnn:::::n  F:::::::::::::::F    i::::i 
//     U:::::D     D:::::U  n::::n    n::::n  F::::::FFFFFFFFFF    i::::i 
//     U:::::D     D:::::U  n::::n    n::::n  F:::::F              i::::i 
//     U::::::U   U::::::U  n::::n    n::::n  F:::::F              i::::i 
//     U:::::::UUU:::::::U  n::::n    n::::nFF:::::::FF           i::::::i
//      UU:::::::::::::UU   n::::n    n::::nF::::::::FF           i::::::i
//        UU:::::::::UU     n::::n    n::::nF::::::::FF           i::::::i
//          UUUUUUUUU       nnnnnn    nnnnnnFFFFFFFFFFF           iiiiiiii

/*
  UnFi Bootloader / Logger by Sliz®
  Arduino Due
  Version 1.start.up
*/

#include <Arduino.h>

#define LOG Serial
bool bootCompleted = false;

#define LED_STATUS 13

void blinkLED(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_STATUS, HIGH);
    delay(delayMs);
    digitalWrite(LED_STATUS, LOW);
    delay(delayMs);
  }
}

void logBootStart() {
  LOG.println("[UnFi] Bootloader started.");
  blinkLED(2, 200);
}

void logBootEnd() {
  LOG.println("[UnFi] Bootloader completed.");
  blinkLED(3, 150);
  bootCompleted = true;
}

void logError(String msg) {
  LOG.print("[UnFi ERROR] ");
  LOG.println(msg);
  blinkLED(5, 100);
}

void checkSystem() {
  LOG.println("[UnFi] Performing system checks...");
  blinkLED(1, 300);
  LOG.println("[UnFi] System OK.");
}

// Your code here
// #include <code.h> and other

void userSetup() {
  // Your setup code here
}

void userLoop() {
  // Your loop code here
}

void setup() {
  pinMode(LED_STATUS, OUTPUT);
  Serial.begin(115200);
  while (!Serial) { ; }

  logBootStart();
  checkSystem();

  try { userSetup(); }
  catch (...) { logError("Error in user setup!"); }

  logBootEnd();
}

void loop() {
  if (!bootCompleted) return;

  try { userLoop(); }
  catch (...) { logError("Error in user loop!"); }
}
