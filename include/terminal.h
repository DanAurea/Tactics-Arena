typedef enum{fblack = 30, fred, fgreen, fyellow, fblue, fmagenta, fcyan, fwhite}fterminal; /**< Font color */
typedef enum{sblack = 40, sred, syellow, sgreen, sblue, smagenta, scyan, swhite}sterminal; /**< Screen color */
typedef enum{blink = 5, invertColor= 7}screen; /**< Set screen action */

void color(int color);
void clearScreen();