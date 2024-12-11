#ifndef SMALLBIRD_H
#define SMALLBIRD_H

typedef struct {
    short x;       // x position
    short y;       // y position
    short size;    // size 
    char active;   // 1 = visible, 0 = not visible
} SmallerBird;

extern SmallerBird smallBird;


void initSmallBird(); //initialize the smaller bird
void moveSmallBird(); //move the smaller bird
int checkCollision(short birdX, short birdY, short beakEdgeX, short smallBirdX, short smallBirdY);

#endif // SMALLBIRD_H
