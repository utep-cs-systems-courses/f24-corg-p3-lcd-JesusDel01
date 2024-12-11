#include "lcdutils.h"
#include "lcddraw.h"
#include "bird.h"
#include "smallBird.h"
#include <stdio.h>
#include "buzzer.h"



SmallerBird smallBird;
char lives = 3;
char score = 0;
char speed = 3;

char arrayOfNumsForY[] = {90, 40, 70, 100, 43, 72, 115, 60, 30};
char startIndex = 0;


void initSmallBird() {
  smallBird.x = screenWidth - 1;                          //start at the right edge of the screen
  smallBird.y = arrayOfNumsForY[startIndex];              //the y position is determined by the value of start index
  startIndex = (startIndex + 1) %  9;                     //cycle through values we % 9 because theyres 9 elements in the array
  smallBird.size = 4;                                     //size of the smaller bird
  smallBird.active = 1;                                   //set as active
}


void moveSmallBird() {
    if (smallBird.active) {
        fillCircle(smallBird.x, smallBird.y, smallBird.size, COLOR_CYAN); // clear old position
        smallBird.x -= speed;                                             // how fast the bird moves to the left

        // check if the bird moved off-scree
        if (smallBird.x < 0) {
	  lives -= 1;
	  char livesStr[2];                                               //buffer to store the score as a string                                                                                                             
          sprintf(livesStr, "%d", lives);                                 //convert score to a string
          drawString8x12(5, 10, livesStr, COLOR_WHITE, COLOR_BLUE);
	  
       	  initSmallBird();
	}
	
        fillCircle(smallBird.x, smallBird.y, smallBird.size, COLOR_RED);  // redraw the bird with its new position

	// we calculate our big birds beak postion by using getter methods
        short beakEdgeX = getBirdX() +getBirdSize() + 3;                  // aproximate the beaks position

        // check for collidions
        if (checkCollision(getBirdX(), getBirdY(), beakEdgeX, smallBird.x, smallBird.y)) {
	  smallBird.active = 0;                                                            // deactivate smaller bird
	  fillCircle(smallBird.x, smallBird.y, smallBird.size, COLOR_CYAN);                //clear bird    
	  score++;                                                                         // increment the score
	  char scoreStr[3];                                                                //buffer to store the score as a string
	  sprintf(scoreStr, "%d", score);                                                  //convert score to a string
	  drawString8x12(60, 11, scoreStr, COLOR_WHITE, COLOR_BLUE);
	  if (score % 3 == 0){                                                            // every three points the small bird wil move faster and faster
	    speed += 1;
	  }
	  buzzer_set_period(1000); 
	  initSmallBird();                                                                // respawn the smaller bird in a random location
        }
    }
}

int checkCollision(short birdX, short birdY, short beakEdgeX, short smallBirdX, short smallBirdY) {
  // check if the x-coordinates are approximately 12 pixels apart
  if (smallBirdX >= beakEdgeX - 12 && smallBirdX <= beakEdgeX + 12) {
    // check if the y-coordinate of the small bird is within the range of the beak's range 5 more or less than the big birds y-coordinate 
    if (smallBirdY >= birdY - 5 && smallBirdY <= birdY + 5) {
      return 1; //collision detected
    }
  }
  return 0; // no collision
}

