#ifndef COULEURS
#define COULEURS

#include <stdio.h>

#define clrscr() printf("\033[H\033[2J")

// Color selection
#define colors(param) printf("\033[%sm", param)
/*   param must be a const char *, empty (equivalent to "0") or composed
   of one or more values separated by ; among
       0  reset                    1  high intensity (of characters)
       5  blinking                 7  reverse video
       30, 31, 32, 33, 34, 35, 36, 37 text color
       40, 41, 42, 43, 44, 45, 46, 47 background color
        the colors, following the RGB logic, being respectively
         black, red, green, yellow, blue, magenta, cyan, and white */

#endif