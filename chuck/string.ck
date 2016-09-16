// this is really hacked: ConsoleInput class to be replaced soon
// simple demo for how to parse strings from the command line

// make a ConsoleInput
ConsoleInput in;
// tokenizer
StringTokenizer tok;

// loop
while( true ) {
    // prompt
    in.prompt( "enter line of text:" ) => now;

    // read
    while( in.more() ) {
        // get it
        tok.set( in.getLine() );

        // print tokens
        while( tok.more() ) {
            // print it
            <<< tok.next(), "" >>>;
        }
    }
}

