#if defined(ARDUINO)
SYSTEM_MODE(SEMI_AUTOMATIC);
#endif

int a0 = A0;
int a1 = A1;

void setup() {
  pinMode(a0, INPUT);
  pinMode(a1, INPUT);
}

void relay(int pin) {
  Serial.print(pin);
  Serial.print(',');
  Serial.println(analogRead(pin));
}

void loop() {
  relay(a0);
  relay(a1);
  delay(100);
}

