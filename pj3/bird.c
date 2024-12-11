#include "lcdutils.h"
#include "lcddraw.h"
#include <stdlib.h>

static short birdX = 35;          //fixed x position for the bird
static short birdY = 60;          //start y  position
static short birdSize = 6;        //size of the bird

void drawBird() {
  fillCircle(birdX, birdY, birdSize, COLOR_GOLD);

  //draws a beak
  for (short row = -2; row <= 2; row++) {                        //height of the beak
    for (short col = 0; col <= 3 - abs(row); col++) {            //width shrinks with height
      drawPixel(birdX + birdSize + col, birdY + row, COLOR_RED); //triangle
    }
  }

  //draws an eye
  fillRectangle(birdX + 2, birdY - 4, 4, 4, COLOR_WHITE);
  fillRectangle(birdX + 4, birdY - 4, 2, 2, COLOR_BLACK);

  //draws wing
  for (short row = -2; row <= 2; row++) {
    for (short col = -3; col <= 3; col++) {
      if ((row * row) + (col * col / 2) <= 6) {                   //wing shape approximation
        drawPixel(birdX - 5 + col, birdY + 1 + row, COLOR_WHITE);
      }
    }
  }
  
}
void clearBird() {
  fillCircle(birdX, birdY, birdSize, COLOR_CYAN);                 //matches the sky color

  //clears the beak
  for (short row = -2; row <= 2; row++) {                                                                                                         
    for (short col = 0; col <= 3 - abs(row); col++) {                                                                            
      drawPixel(birdX + birdSize + col, birdY + row, COLOR_CYAN);                                                            
    }
  }

  //clears the eye
  fillRectangle(birdX + 2, birdY - 4, 4, 4, COLOR_CYAN);
  fillRectangle(birdX + 4, birdY - 4, 2, 2, COLOR_CYAN);

  //clears the wing
  for (short row = -2; row <= 2; row++) {
    for (short col = -3; col <= 3; col++) {
      if ((row * row) + (col * col / 2) <= 6) { 
	drawPixel(birdX - 5 + col, birdY + 1 + row, COLOR_CYAN);
      }
    }
  }


}

void moveBird(short direction) {
  clearBird();                                              //clear the bird's previous position

  // Update y position based on direction
  if (direction > 0){
    birdY -= 5;                                             //move up
    if (birdY < birdSize +15) birdY = birdSize + 15;        //boundary check
  }
  else{
    birdY += 5;                                             //move down
    if (birdY > screenHeight - birdSize - screenHeight / 4)
      birdY = screenHeight - birdSize - screenHeight / 4;   //boundary check
  }
  
  drawBird();                                               //redraw the bird at the new position
}

// getter functions for when we check collisions
short getBirdX() {
    return birdX;
}

short getBirdY() {
    return birdY;
}

short getBirdSize() {
    return birdSize;
}
