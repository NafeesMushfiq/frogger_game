
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

#define NUM_CARS 15
#define NUM_LOGS 9
#define NUM_TURTLES 8

typedef struct{
  Rectangle rect;
  float speed;
  Color color;
} Obstacle;

Obstacle cars[NUM_CARS];
Obstacle logs[NUM_LOGS];
Obstacle turtles[NUM_TURTLES];

void DrawRoad(int X,int Y);
void DrawSafezone(int X,int Y);
void DrawRiver(int X,int Y);
void DrawDestination(int X,int Y);
void DrawDesBox(int X,int Y);

void InitObstacles();
void DrawObstacles();
void UpdateObstacles();

int main(void){

  InitWindow(WIDTH,HEIGHT,"Frogger");
  SetTargetFPS(60);

  InitObstacles();


  while(!WindowShouldClose()){

    UpdateObstacles();

    BeginDrawing();

    ClearBackground(BLACK);

    DrawSafezone(0,HEIGHT-160);

    DrawSafezone(0,HEIGHT-8*80);
    DrawRiver(0,160);
    DrawRoad(0,8*80);
    
    DrawRectangle(0,0,WIDTH,80,GREEN);

    DrawDesBox(60,80);
    DrawObstacles();
        
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

void InitObstacles(){
    
        //CARS INITIALIZATION START//
    
    
    int car_index=0;
    for(int lane=0;lane<5;lane++){

        int lane_Y=640+(lane*80)+15;

        float car_speed=(lane%2) ? 2.5f : -2.2F;
        // Even len --->left direction jabe, Odd len--> right e jabe

        for(int i=0;i<3;i++){
            int car_X=50+(i*400);

            cars[car_index]= (Obstacle){(Rectangle){car_X, lane_Y,100,50},car_speed,RED};

            car_index++;
        }
    }
        //CARS INITIALIZATION END//

    //LOGS INITIALIZATION STARTS//
    float log_speed=2.5f; // log movement---> right direction

    int log_index=0;

    int lane_1_Y=415;
    for(int i=0;i<3;i++){

      int log_x=50+(i*400);

      logs[log_index]=(Obstacle){(Rectangle){log_x,lane_1_Y,200,50},log_speed,BROWN};
      log_index++;

    }

    int lane_2_Y=415-80;
    for(int i=0;i<3;i++){
      int log_x=50+(i*650);
      logs[log_index]=(Obstacle){(Rectangle){log_x,lane_2_Y,200.0*1.5*1.5,50},log_speed,BROWN};
      log_index++;

    }

    int lane_3_Y=415-80*3;

    for(int i=0;i<3;i++){
      int log_x=50+(i*500);
      logs[log_index]=(Obstacle){(Rectangle){log_x,lane_3_Y,200*1.5,50},log_speed,BROWN};

      log_index++;
    }

    //LOGS INITIALIZATION ENDS//

    //Turtles initialization Starts//
    float turtle_speed=-3.0f; // left direction
    int turtle_index=0;

    int lane_t_1_Y=415+80;

    for(int i=0;i<4;i++){

      int turtle_x=50+(i*300);
      turtles[turtle_index]=(Obstacle){(Rectangle){turtle_x,lane_t_1_Y,200,50},turtle_speed,DARKGREEN};
      turtle_index++;
    }

    int lane_t_2_Y=415-80*2;

    for(int i=0;i<4;i++){

      int turtle_x=50+(i*275);
      turtles[turtle_index]=(Obstacle){(Rectangle){turtle_x,lane_t_2_Y,200*(2.0/3),50},turtle_speed,DARKGREEN};
      turtle_index++;
    }

    //Turtles INITIALIZATION ENDS//


}

void DrawObstacles(){

    for(int i=0;i<NUM_CARS;i++){
        DrawRectangleRec(cars[i].rect,cars[i].color);
    }

    for(int i=0;i<NUM_LOGS;i++){
       DrawRectangleRec(logs[i].rect,logs[i].color);
    }
    
    for(int i=0;i<NUM_TURTLES;i++){
      DrawRectangleRec(turtles[i].rect,turtles[i].color);
    }
}

void UpdateObstacles(){


  // Cars movement 
  float car_lane_speed[15]={-0.5,-0.5,-0.5,0,0,0,-0.5,-0.5,-0.5,0,0,0,0,0,0};
 
  for(int i=0;i<NUM_CARS;i++){

    cars[i].rect.x+=cars[i].speed+car_lane_speed[i];

    if(cars[i].speed>0 && cars[i].rect.x>WIDTH+300){ //right side e screen er baire gele abr left side e car width poriman baire theke start hbe abr
      cars[i].rect.x=-cars[i].rect.width;      
    }

    if(cars[i].speed<0 && cars[i].rect.x<-cars[i].rect.width-300){ //left side e screen er baire car width poriman gele right side theke shuru hbe
      cars[i].rect.x=WIDTH;
    }

    
  }

  //Logs movement

  float log_lane_speed[9]={0,0,0,1,1,1,0.5,0.5,0.5};
  float log_extra_space[9]={300,300,300,675,675,675,425,425,425}; //monitor er baire gele pore reappear er somoy extra space create hoi sejnne
  

  for(int i=0;i<NUM_LOGS;i++){

    logs[i].rect.x+=logs[i].speed+log_lane_speed[i];

    if(logs[i].speed>0 && logs[i].rect.x>WIDTH+300){
      
      logs[i].rect.x=-logs[i].rect.width;

    }
  }

  // Turtles Movement
  
  for(int i=0;i<NUM_TURTLES;i++){

    turtles[i].rect.x+=turtles[i].speed;

    if(turtles[i].speed<0 && turtles[i].rect.x<-turtles[i].rect.width){

      turtles[i].rect.x=WIDTH;
    }

  }
  
}

