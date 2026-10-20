const int irIn = D1, btnCap = D2;
volatile uint32_t t[600];
volatile int eCount = 0;
volatile bool cap = false;

void IRAM_ATTR irEdge() {
    if (cap && eCount < 600) t[eCount++] = micros();
}

void setup() {
    Serial.begin(115200);
    pinMode(irIn, INPUT);
    pinMode(btnCap, INPUT_PULLUP);

    attachInterrupt(irIn, irEdge, CHANGE);
    Serial.println("Ready for scaning.");
}

void loop() {
  if (digitalRead(btnCap) == LOW) {
      Serial.println("There is 3 second time window.");
      Serial.println("Capturing...");
      eCount = 0;
      cap = true;
      delay(3000);
      cap = false;

      Serial.print("Data: ");
      for (int i = 1; i < eCount; i++) {
          Serial.print(t[i] - t[i - 1]);
          if (i < eCount - 1) Serial.print(", ");
    }
      Serial.println();
      delay(1000);
  }
}
