#include "lcdutils.h"
#include "lcddraw.h"

void drawBackground() {
  //draw sky
  fillRectangle(0, 0, screenWidth, screenHeight * 3 / 4, COLOR_CYAN);

  //draw ground
  fillRectangle(0, screenHeight * 3 / 4, screenWidth, screenHeight / 4, COLOR_GREEN);
}
