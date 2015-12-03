typedef enum{black, red, green, yellow, blue, magenta, cyan, white}terminal; /**< Colors */
typedef enum{blink = 5, invertColor= 7}screen; /**< Set screen action */

void color(int color, char type[]);
void fontColor(int color);
void clearScreen();