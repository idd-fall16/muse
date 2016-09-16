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
int level = A0; // pin 10
int scale = A1; // pin 11
int tempo = A2; // pin 12
int drums = A3; // pin 13
int bends = A4; // pin 14
// pin 15 is for note/pitch

// digital pins
int pointr = D0;
int middle = D1;
int ring   = D2;
int pinky  = D3;

void setup() {
    pinMode(level, INPUT); // digital pin setup
    pinMode(scale, INPUT);
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
    if (digitalRead(pinky)  == LOW) note += 1;

    // 0 is the corresponding mapping for which note
    Serial.print("15 "); // can change this later

    int gray;
    switch (note) {
        case  1: gray = 1;  break;
        case  2: gray = 3;  break;
        case  3: gray = 2;  break;
        case  4: gray = 7;  break;
        case  5: gray = 6;  break;
        case  6: gray = 4;  break;
        case  7: gray = 5;  break;
        case  8: gray = 15; break;
        case  9: gray = 14; break;
        case 10: gray = 12; break;
        case 11: gray = 13; break;
        case 12: gray = 8;  break;
        case 13: gray = 9;  break;
        case 14: gray = 11; break;
        case 15: gray = 10; break;
        default: gray = 0;  break;
    }

    // print gray scale version
    Serial.println(gray);
}

void relay(int pin) {
    Serial.print(pin);
    Serial.print(' ');
    Serial.println(analogRead(pin));
}

void loop() {
    relay(level);
    relay(scale);
    relay(tempo);
    relay(drums);
    relay(bends);

    readHand(); // compute and send current hand position

    delay(50); // don't clog up serial port
}

