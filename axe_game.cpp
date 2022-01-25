#include "raylib.h"
#include <math.h>
#include <iostream> 
#include <string> 

int main()
{
    int width = 1000;
    int height = 600;

    /*
    int circle_x{width/2};
    int circle_y{height/2};
    */

    int circle_x{width/5};
    int circle_y{height/2};
    int circle_radius = 25;

    // circle's edge

    /*
    |---l_circle_x      |--r_circle_x
    v                   V
    -------------------------------------------------------------
    |                   |<--u_circle_y
    |                   |
    |                   |
    -------------------------------------------------------------
    ^                   ^
    |----               |----b_circle_y
    */


    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};   


    int axe_x{400};
    int axe_y{0};
    int axe_length = 50;

    // axe's edge
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_length};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_length};   

    int direction{10};

    bool collision_with_axe{false};

    InitWindow(width, height,  "Hello!");

    int level = 1;
    int move_speed = 10;
    int dead_count{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Level: ",(width-width)+50, (height-height)+50, 20, BLUE);
        DrawText(std::to_string(level).c_str(),(width-width)+110, (height-height)+50, 20, BLUE);
        DrawText("Speed: ",(width-width)+50, (height-height)+80, 20, GREEN);
        DrawText(std::to_string(move_speed).c_str(),(width-width)+120, (height-height)+80, 20, GREEN);
        DrawText("Dead count: ",(width-width)+50, (height-height)+110, 20, RED);
        DrawText(std::to_string(dead_count).c_str(),(width-width)+180, (height-height)+110, 20, RED);


        if(collision_with_axe){
            DrawText("Game Over!",width-645, height/2, 40, RED);
            DrawText("Press [spacebar] to play again!",width-740, (height/2)+50, 30, BLUE);
            if(IsKeyDown(KEY_SPACE)){

                circle_x = width/5;
                circle_y = height/2;

                axe_x = 400;
                axe_y = 0;

                level = 1;
                direction = abs(direction);
                direction = 10;
                move_speed = 10;
                dead_count++;
                collision_with_axe  = false;
            }
            }else{
            // begin game logic


            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;   



            collision_with_axe = (b_axe_y >= u_circle_y) &&
                                 (u_axe_y <= b_circle_y) &&
                                 (r_axe_x >= l_circle_x) &&
                                 (l_axe_x <= r_circle_x);


            DrawCircle(circle_x, circle_y, circle_radius,  BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // move the axe
            axe_y += direction;
            
            /*
            * silly's way *
            if(axe_y > (height)){
                direction = -direction;
            }

            if(axe_y < ((height-height) - 50)){
                direction = abs(direction);
            }        
            */

            if(axe_y > height || axe_y < ((height-height) - 50)){
                direction = -direction;
            }

            if(IsKeyDown(KEY_D) && circle_x < width)
            {
                circle_x += move_speed;
            }

            if(IsKeyDown(KEY_A) && circle_x > (width-width))
            {
                circle_x -= move_speed;
            }        


            if(!collision_with_axe && (circle_x >= width) ){
            DrawText("Winner!",width-645, height/2, 40, BLUE);

                circle_x = width/5;
                circle_y = height/2;

                axe_x = 400;
                axe_y = 0;               
                level++;
                if(level%5 == 0){
                    move_speed+=5;
                }
                direction = abs(direction);
                direction+=3;
            }

            // end game logic
        }

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}