VIRTUAL DIGITAL CLOCK

We're building a digital clock with an LED display.  Our company has
ordered a million LED clock faces delivered to the factory.

The display manufacturer has sent us a file called "LED-layout.txt",
which explains which bits go where to turn on the LEDs.  They've also sent
us a file "LEDisplay.h", which has prototypes and declarations needed
for our compiler, and "LEDisplay.o", which has all the object code.
(They did not send us the C source files, because they consider that to
be a trade secret.)

We have to do three things to make a working final clock:

1) Figure out am/pm so our clock has more than one mode.

   This includes figuring out how to manage offsets, so we can
   test "11:59:59 am" -> "12:00:00 pm" without waiting until noon.


2) Figure out how to use the LED display instead of just having a
   text display.


3) Make the buttons work.


These are three consecutive assignments.

 *

Things To Notice:

1) "clock.h" includes "LEDisplay.h".

2) The Makefile includes LIBRARY and INCLUDE macros, for some of the
   special features needed to do full-screen display.

3) A stub "ledshow()" is in "view.c", but it's just sample code.

4) "clock.c" has variables which go with the option flags, and they are
   global, not local, because they can't be passed.

 *

For the rest, read the files "1-ampm.txt", "2-LED.txt", and "3-buttons.txt".

