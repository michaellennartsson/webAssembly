#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten.h>

// Numbers of circles
#define NUM_CIRCLES 20

// Circle struct
struct Circle {
  int x;  // x coordinate
  int y;  // y coordinate
  int r;  // radius
  int cr; // color - red
  int cg; // color - green
  int cb; // color - blue
};

// Circle Animation Data struct
struct CircleAnimationData {
  int x;  // x coordinate
  int y;  // y coordinate
  int r;  // radius
  int vx; // velocity - x
  int vy; // velocity - y
  int dx; // x axis direction (1 = forward, 0 = backwards)
  int dy; // y axis direction (1 = forward, 0 = backwards)
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

// Random number generator
int getRandomNumber(int max) {
  return (rand() % max);
}

// Init circle data and start render -JS
int main() {
  // Seed random number generator
  srand(time(NULL));

  // Create circles
  for(int i = 0; i < NUM_CIRCLES; i++) {
    int r = getRandomNumber(50);
    int x = getRandomNumber(1000) + r;
    int y = getRandomNumber(1000) + r;

    animationData[i].r = r;
    animationData[i].x = x;
    animationData[i].y = y; 
    animationData[i].vx = getRandomNumber(10);
    animationData[i].vy = getRandomNumber(10);
    animationData[i].dx = 1;
    animationData[i].dy = 1;

    circles[i].r = r;
    circles[i].x = x;
    circles[i].y = y; 
    circles[i].cr = getRandomNumber(255);
    circles[i].cg = getRandomNumber(255);
    circles[i].cb = getRandomNumber(255);
  }

  // Start JS render function
  EM_ASM({ render($0, $1); }, NUM_CIRCLES * 6, 6);
}

struct Circle* getCircles(int canvasWidth, int canvasHeight) {
  
  // Update circle data
  for(int i = 0; i < NUM_CIRCLES; i++) {

    // Collision RIGHT - set x direction backwards 0
    if( (animationData[i].x + animationData[i].r) >= canvasWidth ) animationData[i].dx = 0;

    // Collision LEFT - set x direction forwards 1
    if( (animationData[i].x - animationData[i].r) <= 0 ) animationData[i].dx = 1;

    // Collision TOP - set y direction forwards 1
    if( (animationData[i].y - animationData[i].r) <= 0 ) animationData[i].dy = 1;

    // Collision BOTTOM - set y direction backwards 0
    if( (animationData[i].y + animationData[i].r) >= canvasHeight ) animationData[i].dy = 0;

    // Move circle in specified direction
    if( animationData[i].dx == 1 ) {
      animationData[i].x += animationData[i].vx;
    } else {
      animationData[i].x -= animationData[i].vx;
    }
    if( animationData[i].dy == 1 ) {
      animationData[i].y += animationData[i].vy;
    } else {
      animationData[i].y -= animationData[i].vy;
    }

    circles[i].x = animationData[i].x;
    circles[i].y = animationData[i].y;
  }

  return circles;  
}