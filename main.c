
#include "raylib.h"
#include<stdio.h>

#define WIDTH 1200
#define HEIGHT 1200
#define SZ_WIDTH WIDTH //safezone_width
#define SZ_HEIGHT 80 //safezone_height
#define RIVER_WIDTH WIDTH
#define RIVER_HEIGHT 400
#define ROAD_WIDTH WIDTH
#define ROAD_HEIGHT 400

void DrawRoad(int X,int Y);
void DrawSafezone(int X,int Y);
void DrawRiver(int X,int Y);
void DrawDestination(int X,int Y);
void DrawDesBox(int X,int Y);

int main(void){

  InitWindow(WIDTH,HEIGHT,"Frogger");
  SetTargetFPS(60);

  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);

    DrawSafezone(0,HEIGHT-160);

    DrawSafezone(0,HEIGHT-8*80);
    DrawRiver(0,160);
    DrawRoad(0,8*80);
    
    DrawRectangle(0,0,WIDTH,80,GREEN);

    DrawDesBox(60,80);
        
    EndDrawing();

  }

  CloseWindow();
  return 0;



}

void DrawRoad(int X,int Y){

  DrawRectangle(X,Y,ROAD_WIDTH,ROAD_HEIGHT,BLACK);

}
void DrawSafezone(int X,int Y){

  DrawRectangle(X,Y,SZ_WIDTH,SZ_HEIGHT,PURPLE);

}

void DrawRiver(int X,int Y){

  DrawRectangle(X,Y,RIVER_WIDTH,RIVER_HEIGHT,DARKBLUE);

}

void DrawDestination(int X, int Y){

  DrawRectangle(X,Y,WIDTH,160,GREEN);
}

void DrawDesBox(int X,int Y){

  for(int i=1;i<=5;i++){
    DrawRectangle(((2*i-1)*120)-X,Y,120,80,GREEN);
  }
}


