/*
 * muse - arm-mounted synth controller
 * for berkeley idd, autumn of 2016
 * using redbear duo, 32b ARM mcu
 *
 * by
 * payton goodrich
 * scarlett teng
 * jeremy warner
 */

#if defined(ARDUINO)
SYSTEM_MODE(SEMI_AUTOMATIC);
#endif

// analog pins
int level = A0;
int pitch = A1;
int tempo = A2;
int drums = A3;
int bends = A4;

// digital pins
int pointr = D0;
int middle = D1;
int ring   = D2;
int pinky  = D3;

void setup() {
    pinMode(level, INPUT); // digital pin setup
    pinMode(pitch, INPUT);
    pinMode(tempo, INPUT);
    pinMode(drums, INPUT);
    pinMode(bends, INPUT);

    pinMode(pointr, INPUT_PULLUP); // analog pin setup
    pinMode(middle, INPUT_PULLUP);
    pinMode(ring,   INPUT_PULLUP);
    pinMode(pinky,  INPUT_PULLUP);

    Serial.begin(9600); // begin communication
}

void readHand() {
    int note = 0; // pinky is the LSB, pointer is MSB

    if (digitalRead(pointr) == LOW) note += 8;
    if (digitalRead(middle) == LOW) note += 4;
    if (digitalRead(ring)   == LOW) note += 2;
    if (digitalRead(bends)  == LOW) note += 1;

    // 0 is the corresponding mapping for which note
    Serial.print("0,"); // can change this later

    // scale up to the same value by shifting 8
    // other pins have 12 bit ADC, only 4 bits in
    Serial.println(note << 8);

    // ^^^
    // this could potentially throw an ambiguous type error, potentially
    // explicitly type case it to be one or the other. TDB
}

void relay(int pin) {
    Serial.print(pin);
    Serial.print(',');
    Serial.println(analogRead(pin));
}

void loop() {
    readHand(); // compute and send current hand position

    relay(level);
    relay(pitch);
    relay(tempo);
    relay(drums);
    relay(bends);

    delay(100);
}

