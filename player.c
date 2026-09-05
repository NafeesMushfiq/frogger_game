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
#define GRID_STEP 80

typedef struct{
  Rectangle rect;
  float speed;
  Color color;
} Obstacle;

typedef struct {
    Rectangle rect;
    Color color;
} Frog;
Frog frog;


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

//frog functions
void InitFrog();
void UpdateFrogInput();
void DrawFrog();

//collision check func
void CheckVehiclecollision(Obstacle cars[], int num_cars);
void CheckRiverLogic(Obstacle logs[], int num_logs, Obstacle turtles[], int num_turtles);

//destination check and score check func
void CheckDestinationLogic();


//score and live initialization
int score = 0;
int lives = 3;

int main(void){

  InitWindow(WIDTH,HEIGHT,"Frogger");
  SetTargetFPS(60);

  InitObstacles();
  InitFrog();

  while(!WindowShouldClose()){

    UpdateObstacles();
    UpdateFrogInput();


    CheckVehiclecollision(cars, NUM_CARS);//road collision check
    CheckRiverLogic(logs, NUM_LOGS, turtles, NUM_TURTLES);//river collision check

    CheckDestinationLogic();//box e bosche ki na and score check 


    BeginDrawing();

    ClearBackground(BLACK);

    DrawSafezone(0,HEIGHT-160);

    DrawSafezone(0,HEIGHT-8*80);
    DrawRiver(0,160);
    DrawRoad(0,8*80);
    
    DrawRectangle(0,0,WIDTH,80,GREEN);

    DrawDesBox(60,80);
    DrawObstacles();
    DrawFrog();

    DrawText(TextFormat("Score : %d", score), 40, HEIGHT-60, 35, YELLOW);
    DrawText(TextFormat("LIVES :%d",lives),WIDTH-220, HEIGHT-60, 35, RED);
        
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


void InitFrog(){
    //50X50 SIZE ER FROG BOTTOM SAFEZONE CENTER THEKE START HOBE
    float frog_width = 50.0f;
    float frog_hight =50.0f;

    frog.rect = (Rectangle){(WIDTH/2.0f)-(frog_width/2.0f),(HEIGHT-160)+15, frog_width, frog_hight};
    frog.color = LIME;
}

void UpdateFrogInput(){
    //for moving up
    if(IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W)){
        if(frog.rect.y-GRID_STEP>=0){
            frog.rect.y-= GRID_STEP;
        }
    }

    //for moving down
    if(IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)){
        if(frog.rect.y + GRID_STEP <= (HEIGHT - 160)+15){
            frog.rect.y += GRID_STEP;
        }
    }

    // for moving left
    if(IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_A)){
        if(frog.rect.x - GRID_STEP >= 0){
            frog.rect.x -= GRID_STEP;
        }
    }
    
    // for moving right
    if(IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_D)){
        if(frog.rect.x + GRID_STEP + frog.rect.width <= WIDTH){
            frog.rect.x+=GRID_STEP;
        }
    }

}

void DrawFrog(){
    DrawRectangleRec(frog.rect, frog.color);
}

//Road collision check and reset position
void CheckVehiclecollision(Obstacle cars[], int num_cars){
for (int i=0;i<num_cars; i++){
  //collision check korar jonno raylib er built in func use. jodi collision hoy taile initial position theke start hobe . 
  if (CheckCollisionRecs(frog.rect, cars[i].rect)){
      InitFrog();
      break;
  }
}
}


//River collision check: jodi log ba turtle er upr thake taile safe, na hoile mara.
void CheckRiverLogic(Obstacle logs[], int num_logs, Obstacle turtles[], int num_turtles){

 //river boundary
  float river_top = 160.0f;
  float river_bottom = 560.0f;

  //frog river er vitore ase ki na check kora 
  if(frog.rect.y >= river_top && frog.rect.y < river_bottom){
    bool on_safe_platform = false;

    //frog log er upr ase ki na check kora
    for(int i=0; i< num_logs; i++){
      if(CheckCollisionRecs(frog.rect, logs[i].rect)){
        on_safe_platform = true;

        frog.rect.x += logs[i].speed;//log er speed er sathe frog k move koranu
        break;
      }
    }

    //frog turtle er upr ase ki na check kora (jdi already kunu log e na thake)
  if(!on_safe_platform){
    for(int i=0; i< num_turtles; i++){
      if(CheckCollisionRecs(frog.rect, turtles[i].rect)){
        on_safe_platform = true;

        frog.rect.x += turtles[i].speed;//turtle er speed er sathe frog k move koranu
        break;
      }
    }
  }
  

    //boundary check: jodi log e bose frog log er sathe screen er baire chole jay taile mara
    if(frog.rect.x<0 || frog.rect.x + frog.rect.width>WIDTH){
      InitFrog();//tokhon abar prothom theke start hobe
    }

    //river e ase but log/turtle er upr nai : tibro mara
    if (!on_safe_platform){
      InitFrog();//tokhon abar prothom theke start hobe.
    }
  }
 

}

//destination reach check and score update
void CheckDestinationLogic(){
  //top destination zone y limit(y<160)
  if(frog.rect.y < 160.0f){
    bool hit_destination_box =false;


    //drawbox er 5 ti box boundary check
    for(int i=0; i<=5; i++){
      float box_x = ((2*i-1)*120)-60;
      Rectangle desBox = (Rectangle){box_x, 80, 120, 80};

      if(CheckCollisionRecs(frog.rect, desBox)){
        hit_destination_box = true;
        score += 100; //win score
        InitFrog();// abr reset hobe
        break;

      }
    }

    //green box miss hit korle (box miss korle)
    if(!hit_destination_box){
      InitFrog();//game abr suru theke reset hobe
    }
  }
}

