/* paristime.c - what time is it in Paris?
 *
 * D Provine, 8 November 2018
 */

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// longest time zone I could find was
// "posix/America/Argentina/ComodRivadavia",
// which is 38 characters
#define MAX_ZONE_LENGTH 50

void show_time(time_t currtime)
{
    char      *time_zone;
    struct tm *result;

    time_zone = getenv("TZ");
    printf("Timezone: %s\n", time_zone);
    printf("        ctime():  ");
    fputs(ctime(&currtime), stdout);

    // localtime results
    result = localtime(&currtime);
    printf("    localtime():  ");
    printf("%d/%d/%d %02d:%02d:%02d\n\n",
           result->tm_year + 1900,
           result->tm_mon + 1,
           result->tm_mday,
           result->tm_hour,
           result->tm_min,
           result->tm_sec);
}

int main()
{
    time_t now = time( (time_t *) NULL );
    char *time_zone;
    char save_time_zone[MAX_ZONE_LENGTH];

    printf("Unix time in seconds: %ld\n", now);

    show_time(now);

    // save current time zone
    time_zone = getenv("TZ");
    strncpy(save_time_zone, time_zone, 49);

    // set to Paris
    setenv("TZ", "Europe/Paris", 1);

    show_time(now);
    
    // switch back to saved time zone
    setenv("TZ", save_time_zone, 1);

    show_time(now);
    
    return 0;
}
