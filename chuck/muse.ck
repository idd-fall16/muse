//******************************************************************
// Run as: chuck muse.ck: [serialport]
//******************************************************************

SerialIO.list() @=> string list[];

for(int i; i < list.cap(); i++)
    {
        chout <= i <= ": " <= list[i] <= IO.newline();
    }

// parse first argument as device number
0 => int device;
if(me.args()) {
    me.arg(0) => Std.atoi => device;
}

if(device >= list.cap()) {
    cherr <= "serial device #" <= device <= " not available\n";
    me.exit();
}

SerialIO cereal;
if(!cereal.open(device, SerialIO.B9600, SerialIO.ASCII)) {
    chout <= "unable to open serial device '" <= list[device] <= "'\n";
    me.exit();
}

// carrier
SinOsc c => dac;

// modulator
SinOsc m => blackhole;

// carrier frequency
220 => float cf;
// modulator frequency
550 => float mf => m.freq;
// index of modulation
200 => float index;

while(true) {
    cereal.onLine() => now;
    cereal.getLine() => string line;
    if(line$Object != null) {
        chout <= "line: " <= line <= IO.newline();
        StringTokenizer tok;
        tok.set(line)   ;
        Std.atoi(tok.next()) => int pos;
        Std.atoi(tok.next()) => int val;
        <<<pos>>>;
        <<<val>>>;
    }

    // FM synthesis by hand
    // modulate
    cf + (index * m.last()) => c.freq;
    // advance time by 1 samp
    1::samp => now;
}

