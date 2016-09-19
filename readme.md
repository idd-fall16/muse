# Project Muse

Video: https://www.youtube.com/watch?v=IeB_q3hdOr4

<a href="http://www.youtube.com/watch?feature=player_embedded&v=IeB_q3hdOr4
" target="_blank"><img src="http://img.youtube.com/vi/IeB_q3hdOr4/0.jpg"
alt="" width="480" height="360" border="10" /></a>

```
University of California, Berkeley
Interactive Device Design F16
Music Controller Project
```

- Payton Goodrich: Mechanical Design, Manufacturing
- Scarlett Teng: Wiring, Manufacturing
- Jeremy Warner: Schematic Design, MCU/ChucK code

## Control Scheme

We designed our system to simply use your hand for note control. Your four
fingers become switches, and control the main note being played. We used Gray
code to allow modifying the pitch, so any two adjacent notes are just a single
finger apart. There is also an armplate with five potentiometers - four
rotational and one soft. Two of the rotational pots control the pitch and gain
of a consistent background tone, which can be used to set the backdrop of your
musical creation. The other two pots control the ‘fingers’ wave gain and pulse
width. Finally, we use the softpot to bend the ‘fingers’ base frequency,
similar in effect to a whammy bar.

## Implementation

The armband was 3d printed with PLA on type A 3d printers.  A bottom plate was
designed so that polypropylene straps could be attached by hand sewing it
together, and able to close using velcro to accommodate various arm sizes.
This plate also houses the electronics and wiring, and ports for the wiring to
reach the computer (output) and musical glove (input) were included in the
design.  The electronics cavity is covered by a top plate with through holes
for mounting the four potentiometers and soft pot.

![fritzing](/schematic/breadboard.png)

The musical glove was made by 3d printing four finger caps, which were designed
based off the profile of Payton’s left index finger.  For the palm, we recycled
existing cotton gloves.  Wiring from the arm band attaches to the four fingers
and the palm of the glove and is connected by copper tape to make sure there is
good conductivity.  By cleverly assigning the palm to ground and the four
individual finger nodes as separate pull up resistors, we were able to create a
4-bit system of digital input.

![final device prototype](/enclosure/prototype.jpg)

Our electronic hardware consists of five analog sensors, and four digital
sensors. The analog sensors are used to control the gain and background levels,
while the digital sensors are used to measure how many fingers are being
pressed. There is C code on our RedBear that continuously samples and dumps the
state of selected RedBear's sensors over serial. It does this by sending each
set of information as a line, with a space separating the pin number and the
value that pin has. For example, one set of data as ‘10 1234’ means that pin 10
has value 1234. We use this format because of its ease of parsing later on in
the pipeline.

![Sijia assembling the armband](/enclosure/assembly.png)

This data is then uploaded to ChucK, an open-source synthesizer software that
has grown in popularity.  There is ChucK code that reads the serial input and
connects it to components of two different waves that generate the user’s
music. There is a background sine wave, which you can control both the gain and
base frequency of using the rotation potentiometers. There also is a variable
duty cycle pulse wave, which is triggered by touch from any of the finger
sensors.

## Difficulties

The flexibility of ChucK was less than ideal - the software did not work
correctly on Scarlett’s Windows computer. We were unable to resolve this issue,
but believe that it was linked to how the Windows version of ChucK handles
serial input. Additionally, getting a decent sounding control mechanism
interface required a fair bit of fiddling in ChucK, which was surprising given
how elementary the desired control was. There is still refinement that could be
performed to allow immediate access to the essential tone of our instrument,
but it provides a decent mechanism for playing music.

We also encountered a good deal of manufacturing dilemmas.  The final design
for the armband failed to print on two separate attempts - one from another
user cancelling it inadvertently and another from something going wrong with
the PLA wire.  The mounting plate also failed in this way.  With no time left
to print in Jacob’s before the project was due, we had to make manual
adjustments for the finished product.  Given more time, we could print these
and make the device more aesthetically pleasing.

## Reflection

Our final product worked pretty well. The overall design and look of it is
really good we think, and with more time to develop the manufacturing process
and software this could feasibly be a product for electronic music DJs,
particularly for shows where they could use this device to get away from hiding
behind their bulky control boards and interacting more directly with the crowd.

