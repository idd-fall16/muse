//******************************************************************
// Run as: chuck muse.ck:[serialport]
//******************************************************************


// Setting up the carrier
SinOsc c => dac;

// Getting the serial device
SerialIO.list() @=> string list[];
for (int i; i < list.cap(); i++) {
    chout <= i <= ": " <= list[i] <= IO.newline();
}

// parse first argument as device number
0 => int device;
if (me.args())
    me.arg(0) => Std.atoi => device;
if (device >= list.cap()) {
    cherr <= "serial device #" <= device <= " not available\n";
    me.exit();
}

SerialIO cereal;
if (!cereal.open(device, SerialIO.B9600, SerialIO.ASCII)) {
    chout <= "unable to open serial device '" <= list[device] <= "'\n";
    me.exit();
}


// Connecting serial input to chuck controls. Most values are in between 0 and
// 2^12 (4096) because of the 12 bit ADC on the redbear duo, but the pitch level
// coming is discrete and depends on which fingers are being pressed. This value
// ranges from 0 and 15 (2^4 fingers). The data is piped in from the arduino
// based on which pin it was read from, and then applied relevantly.
while (true) {
    cereal.onLine() => now;
    cereal.getLine() => string line;
    if(line$Object != null) {
        //chout <= "line: " <= line <= IO.newline();
        StringTokenizer tok; tok.set(line);
        Std.atoi(tok.next()) => int pin;
        Std.atoi(tok.next()) => int val;

        if (pin == 10)
            level(val);
        if (pin == 11)
            scale(val);
        if (pin == 12)
            tempo(val);
        if (pin == 13)
            drums(val);
        if (pin == 14)
            bend(val);
        if (pin == 15)
            pitch(val);
    }
}


// change the gain level
fun void level( int l )
{
    l/4096 => c.gain;
}

fun void scale( int s )
{
}

fun void tempo( int t )
{
}

fun void drums( int d )
{
}

fun void bend( int b )
{
}

// Multiple the root pitch by the fundamental frequency (ff) however many steps
// were given based on the amount of switches thrown down from the arduino
// only make main pitch noise when there is some input signal being played
// http://ptolemy.eecs.berkeley.edu/eecs20/week8/scale.html
// 1.0595 => float ff; // scale of any adjacent two notes
// scratch that, can use whole notes w/ chuck library
// cf * Math.pow(ff, p) => c.freq;
fun void pitch( int p )
{
    if (p > 0)
        Std.mtof(p + 40) => c.freq;
    else
        55 => c.freq;
}

