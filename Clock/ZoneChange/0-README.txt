Thu Nov  8 09:36:26 EST 2018

The program "paristime.c" shows how to get the current timezone
information and save it to a string, change the timezone to something
else, and then put it back.

This might be useful if you are making your clock show the time in
another city.

A list of timezones you can use is on Elvis in the folder

    /usr/share/zoneinfo/

For Paris, there was a folder "Europe", and inside that a file "Paris",
so I went with "Europe/Paris".

If you wanted to go with US Pacific time, you should prefer one of the
longer ones, such as "America/Los_Angeles", instead of using the file
"US/Pacific" or the shorter "PST8PDT".  The longer name makes more
sense, and the shorter ones may not be entirely portable to other
machines.


