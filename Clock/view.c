/* view.c -- view module for clock project (the V in MVC)
 *
 * Darren Provine, 17 July 2009
 *
 * Copyright (C) Darren Provine, 2009-2019, All Rights Reserved
 */

#include "clock.h"
#include "view.h"

/* see "view.h" for list of bits that set properties */

int view_props = 0x00; // default is 24-hour mode, plain text

// returns old properties so you can save them if needed
void set_view_properties(int viewbits)
{
    view_props = viewbits;
}

int get_view_properties()
{
    return view_props;
}


void do_test(struct tm *dateinfo)
{
    // turn display bits on and off
    digit*where = get_display_location();
    if ( dateinfo->tm_sec % 2 == 0 ) {
        for (int i =0; i < 8; i++){
            where[i] = 0xFF;
    }
    }
    else{
        for(int i = 0; i < 8; i++){
            where[i] = 0x00;
        }
    }
    display();
    fflush(stdout);
}


// make something like "12:34:56 am" or maybe "065432 pm".
char * make_timestring (struct tm *dateinfo, int dividers)
{
    static char  timestring[12]; // big enough for "12:34:56 am" + NULL
    char  divider[2] = "";       // a string, not a single char!
    int   hour;                  // for storing hour-as-printed
    char  timeformat[30] = "%02d%s%02d%s%02d %s"; // leading zeros
    char  time_tag[] = "24";

    if ( view_props & DATE_MODE ) {
        // put the right "dateinfo->" stuff into timestring
        // use "/" instead for divider
        // use "dt" instead of "am" or "pm"
        sprintf(timestring,
                timeformat,
                dateinfo->tm_mon+1,
                divider,
                dateinfo->tm_mday,
                divider,
                dateinfo->tm_year%100,
                time_tag);
    } else {
        if ( dividers ) {
            strcpy(divider, ":");
        }
        if (view_props & TEST_MODE){
            sprintf(timestring,
                    timeformat,
                    88,
                    divider,
                    88,
                    divider,
                    88,
                    time_tag);
        }
        else{
        hour=dateinfo->tm_hour;
        if ( view_props & AMPM_MODE ) {
            /* figure out am/pm */
            if ( hour > 11 ) {
                strcpy(time_tag, "pm");
            } else {
                strcpy(time_tag, "am");
            }
            hour = hour % 12;
            if(hour == 0){
                hour = 12;
            }
            if(hour < 10){
                strcpy(timeformat, "%2d%s%02d%s%02d %s");
            }
        }
        sprintf(timestring,
                timeformat,
                hour,
                divider,
                dateinfo->tm_min,
                divider,
                dateinfo->tm_sec,
                time_tag
            );
    }
    }
    return timestring;
}

/* We get a pointer to a "struct tm" object, put it in a string, and
 * then send it to the screen.
 */
void show_led(struct tm *dateinfo)
{

    digit *where = get_display_location();
    int i;
    digit  bitvalues = 0;
    int hour;
    int indicator;
    char *timestring;

    if ( view_props & TEST_MODE ) {
        do_test(dateinfo);
        return;
    }

    timestring = make_timestring(dateinfo, 0);
    for (i = 0; i < 6; i++) {
        switch ( timestring[i] ) {
            case ' ': bitvalues = 0x00; break;
            case '1': bitvalues = 0x42; break;
            case '2': bitvalues = 0x37; break;
            case '3': bitvalues = 0x67; break;
            case '4': bitvalues = 0x4B; break;
            case '5': bitvalues = 0x6D; break;
            case '6': bitvalues = 0x7D; break;
            case '7': bitvalues = 0x46; break;
            case '8': bitvalues = 0x7F; break;
            case '9': bitvalues = 0x6F; break;
            case '0': bitvalues = 0x7E; break;
        }
        where[i] = bitvalues;
    }

    // For Digit 7:
    //   0x01 = AM
    //   0x02 = PM
    //   0x04 = 24H
    //   0x08 = Date
    switch ( timestring[7] ) {
        case 'a': where[7] = 0x01; break;
        case 'p': where[7] = 0x02; break;
        case '2': where[7] = 0x04; break;       
    }

    // turn on colons if even seconds
    if ( dateinfo->tm_sec % 2 == 0 ) {
        where[7] |= 0xf0;
    }

    display();
    fflush(stdout);
}

void show_text(struct tm *dateinfo)
{
    printf("\r%s ", make_timestring(dateinfo, 1));
    fflush(stdout);
}

void show(struct tm *dateinfo)
{
    if ( view_props & LED_MODE )
        show_led(dateinfo);
    else
        show_text(dateinfo);        
}
