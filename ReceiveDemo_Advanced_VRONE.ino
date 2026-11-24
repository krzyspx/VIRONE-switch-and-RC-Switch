#include "RC.h"

#define PIN_ODBIORNIKA 0

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(PIN_ODBIORNIKA, INPUT);
  mySwitch.enableReceive(digitalPinToInterrupt(PIN_ODBIORNIKA));
  Serial.println("Nasluch RF 433 MHz (ESP32-C3) gotowy...");
}

void loop() {
  if (mySwitch.available()) {
    unsigned long kod = mySwitch.getReceivedValue();
    unsigned int bity = mySwitch.getReceivedBitlength();
    unsigned int impuls = mySwitch.getReceivedDelay();
    unsigned int protokol = mySwitch.getReceivedProtocol();
    const unsigned int* surowe = mySwitch.getReceivedRawdata();

    if (kod == 0) {
      Serial.println("Nieznany kod / zaklocenia (0)");
    } else {
      Serial.print("Odebrano: ");
      Serial.print(kod);
      Serial.print(" | Bity: ");
      Serial.print(bity);
      Serial.print(" | Impuls: ");
      Serial.print(impuls);
      Serial.print(" us | Protokol: ");
      Serial.println(protokol);

      Serial.print("Raw: ");
      for (unsigned int i = 0; i <= bity * 2; i++) {
        Serial.print(surowe[i]);
        Serial.print(" ");
      }
      Serial.println();
    }

    mySwitch.resetAvailable();
  }
}
