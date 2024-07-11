
#include "raylib.h"
#include<iostream>
#include<vector>
#include<time.h>
#include<cmath>
#include<stdlib.h>
#include<string>
#define fuera_rango 15.0f
#define radio 5
#define middleRect 110

// things to do
// poder agregar bolitas en tiempo de ejecucion en donde lo ponga el mouse y que cambie de color con el click izquierdo, con el scroll cambiar el radio 


//--------------------------------- STRUCTURE OF THE POINT
struct Point
{
    Vector2 cord;
    std::string type;
    Vector2 vel;
    float m;
};
//---------------------------------


bool userIn(Vector2 user, float x_min, float x_max, float y_min, float y_max)
{
    if (user.x >= x_min && user.x <= x_max && user.y >= y_min && user.y <= y_max) return true;
    else return false;
}

//------------------------------------------------------- Rules betwenn the diferents types of points
float gravity(Point p1, Point p2,float bb, float bg, float bp, float br, float gg, float gp, float gr, float rp, float rr, float pp)
{
    if (p1.type == "BLUE" && p2.type == "BLUE") return bb;
    if ((p1.type == "BLUE" && p2.type == "GREEN") || (p1.type == "GREEN" && p2.type == "BLUE")) return bg;
    if ((p1.type == "BLUE" && p2.type == "PURPLE") || (p1.type == "PURPLE" && p2.type == "BLUE")) return bp;
    if ((p1.type == "BLUE" && p2.type == "RED") || (p1.type == "RED" && p2.type == "BLUE")) return br;
    if (p1.type == "GREEN" && p2.type == "GREEN") return gg;
    if ((p1.type == "GREEN" && p2.type == "RED") || (p1.type == "RED" && p2.type == "GREEN")) return gr;
    if ((p1.type == "GREEN" && p2.type == "PURPLE") || (p1.type == "PURPLE" && p2.type == "GREEN")) return gp;
    if ((p1.type == "RED" && p2.type == "PURPLE") || (p1.type == "PURPLE" && p2.type == "RED")) return rp;
    if (p1.type == "RED" && p2.type == "RED") return rr;
    if (p1.type == "PURPLE" && p2.type == "PURPLE") return pp;
    else return 0;
}
//----------------------------------------------------------------------------------------
 
//------------------------------------------------------------------------------------------------------------ Program main entry point
int main(void)
{
    srand(time(NULL)); // Seed to generate the ranodm values
    const int screenWidth = 1000; // width of the window
    const int screenHeight = 1000; // height of the window
    int rollVel = 4;
    float radious = 20;
    // --------------------------------------------------------Input of the user to set the amount of points
    int userV = 0;
    std::cout << "Ingresa cuantos circulos verdes quieres" << std::endl; // Ingreso cantidad verdes
    std::cin >> userV;
    int rv = 0;
    std::cout << "Ingresa su radio" << std::endl;
    std::cin >> rv;
    int userR = 0;
    std::cout << "Ingresa cuantos circulos rojos quieres" << std::endl; // Ingreso cantidad rojos
    std::cin >> userR;
    int rr = 0;
    std::cout << "Ingresa su radio" << std::endl;
    std::cin >> rr;
    int userP = 0;
    std::cout << "Ingresa cuantos circulos morados quieres" << std::endl; // Ingresos cantidad morados
    std::cin >> userP;
    int rm = 0;
    std::cout << "Ingresa su radio" << std::endl;
    std::cin >> rm;
    int userB = 0;
    std::cout << "Ingresa cuantos circulos azules quieres" << std::endl; // Ingreso cantidad verdes
    std::cin >> userB;
    int rb = 0;
    std::cout << "Ingresa su radio" << std::endl;
    std::cin >> rb;
    //------------------------------------------------------------------------------------------------------

    float rectBG = (float)middleRect;
    float rectBR = (float)middleRect;
    float rectBP = (float)middleRect;
    float rectBB = (float)middleRect;
    float rectGR = (float)middleRect;
    float rectGP = (float)middleRect;
    float rectGG = (float)middleRect;
    float rectRP = (float)middleRect;
    float rectRR = (float)middleRect;
    float rectPP = (float)middleRect;
    float gravBG = (float)middleRect/200;
    float gravBR = (float)middleRect/200;
    float gravBP = (float)middleRect/200;
    float gravBB = (float)middleRect/200;
    float gravGR = (float)middleRect/200;
    float gravGP = (float)middleRect/200;
    float gravGG = (float)middleRect/200;
    float gravRP = (float)middleRect/200;
    float gravRR = (float)middleRect/200;
    float gravPP = (float)middleRect/200;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input"); // Init of the window

    //------------------------------------------ Creation of the points
    std::vector<Point> agents;
    for (size_t i = 0; i < userV; i++)
    {
        Point a;
        a.cord = { (float)(rand() % screenWidth), (float)(rand() % screenHeight) };
        a.type = "GREEN";
        a.vel = { 0.0f,0.0f };
        a.m = rv;
        agents.push_back(a);
    }
    for (size_t t = 0; t < userR; t++)
    {
        Point a;
        a.cord = { (float)(rand() % screenWidth), (float)(rand() % screenHeight) };
        a.type = "RED";
        a.vel = { 0.0f,0.0f };
        a.m = rr;
        agents.push_back(a);
    }
    for (size_t p = 0; p < userP; p++)
    {
        Point a;
        a.cord = { (float)(rand() % screenWidth), (float)(rand() % screenHeight) };
        a.type = "PURPLE";
        a.vel = { 0.0f,0.0f };
        a.m = rm;
        agents.push_back(a);
    }
    for (size_t b = 0; b < userB; b++)
    {
        Point a;
        a.cord = { (float)(rand() % screenWidth), (float)(rand() % screenHeight) };
        a.type = "BLUE";
        a.vel = { 0.0f,0.0f };
        a.m = rb;
        agents.push_back(a);
    }
    //-----------------------------------------------------------------
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    bool show = false;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK); // set the color background
        DrawText("Life of game with forces", 10, 10, 20, DARKGRAY);
        Vector2 user = GetMousePosition();
        radious += (GetMouseWheelMove() * rollVel);
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            show = !show;
        }
        std::cout << "x: " << user.x << " y: " << user.y << std::endl;
        if (show)//user.x + 20 >= 0 && user.x <= 260 && user.y + 20 >= 0 && user.y <= 260
        {
            int state = GetGestureDetected();
            // Drawing the container rectangule
            DrawRectangleGradientH(20, 30, 200, 400, GRAY, GOLD);
            DrawText("Modo configuracion", 20, 20, 20, YELLOW);
            DrawRectangleGradientH(225, 33, 40, 20, MAGENTA, LIME);
            DrawText("Random", 225, 35, 10, PINK);
            //------------------------------------------------------
            DrawRectangleGradientH(30, 40, 170, 20, BLUE, GREEN);
            if (userIn(user, 225, 225 + 40, 33, 33 + 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                std::cout << "RANDOM" << std::endl;
                rectBG = 30 + rand() % 171;
                rectBR = 30 + rand() % 171;
                rectBP = 30 + rand() % 171;
                rectBB = 30 + rand() % 171;
                rectGR = 30 + rand() % 171;
                rectGP = 30 + rand() % 171;
                rectGG = 30 + rand() % 171;
                rectRP = 30 + rand() % 171;
                rectRR = 30 + rand() % 171;
                rectPP = 30 + rand() % 171;
                gravBG = (((rectBG / 200) * 10) - 5.0f);
                gravBR = (((rectBR / 200) * 10) - 5.0f);
                gravBP = (((rectBP / 200) * 10) - 5.0f);
                gravBB = (((rectBB / 200) * 10) - 5.0f);
                gravGR = (((rectGR / 200) * 10) - 5.0f);
                gravGP = (((rectGP / 200) * 10) - 5.0f);
                gravGG = (((rectGG / 200) * 10) - 5.0f);
                gravRP = (((rectRP / 200) * 10) - 5.0f);
                gravRR = (((rectRR / 200) * 10) - 5.0f);
                gravPP = (((rectPP / 200) * 10) - 5.0f);

            }
            if (userIn(user, 30, 200, 40, 60) && state == 8)
            {
                rectBG = user.x;
                gravBG = (((rectBG)/200)*10)-5.5f;
            }
            DrawRectangle(rectBG, 35, 5, 30, BLACK);

            DrawRectangleGradientH(30, 80, 170, 20, BLUE, RED);
            if (userIn(user, 30, 200, 80, 100) && state == 8) 
            {
                rectBR = user.x;
                gravBR = (((rectBR) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectBR, 75, 5, 30, BLACK);

            DrawRectangleGradientH(30, 120, 170, 20, BLUE, PURPLE);
            if (userIn(user, 30, 200, 120, 140) && state == 8)
            {
                rectBP = user.x;
                gravBP = (((rectBP) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectBP, 115, 5, 30, BLACK);

            DrawRectangleGradientH(30, 160, 170, 20, BLUE, BLUE);
            if (userIn(user, 30, 200, 160, 180) && state == 8) 
            {
                rectBB = user.x;
                gravBB = (((rectBB) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectBB, 155, 5, 30, BLACK);

            DrawRectangleGradientH(30, 200, 170, 20, GREEN, RED);
            if (userIn(user, 30, 200, 200, 220) && state == 8)
            {
                rectGR = user.x;
                gravGR = (((rectGR) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectGR, 195, 5, 30, BLACK);

            DrawRectangleGradientH(30, 240, 170, 20, GREEN, PURPLE);
            if (userIn(user, 30, 200, 240, 260) && state == 8) 
            {
                rectGP = user.x;
                gravGP = (((rectGP) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectGP, 235, 5, 30, BLACK);

            DrawRectangleGradientH(30, 280, 170, 20, GREEN, GREEN);
            if (userIn(user, 30, 200, 280, 300) && state == 8)
            {
                rectGG = user.x;
                gravGG = (((rectGG) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectGG, 275, 5, 30, BLACK);

            DrawRectangleGradientH(30, 320, 170, 20, RED, PURPLE);
            if (userIn(user, 30, 200, 320, 340) && state == 8)
            {
                rectRP = user.x;
                gravRP = (((rectRP) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectRP, 315, 5, 30, BLACK);

            DrawRectangleGradientH(30, 360, 170, 20, RED, RED);
            if (userIn(user, 30, 200, 360, 380) && state == 8)
            {
                rectRR = user.x;
                gravRR = (((rectRR) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectRR, 355, 5, 30, BLACK);

            DrawRectangleGradientH(30, 400, 170, 20, PURPLE, PURPLE);
            if (userIn(user, 30, 200, 400, 420) && state == 8)
            {
                rectPP = user.x;
                gravPP = (((rectPP) / 200) * 10) - 5.5f;
            }
            DrawRectangle(rectPP, 395, 5, 30, BLACK);
        }
        else
        {
            DrawCircleV(user, radious , WHITE);
        }
        //----------------------------------------------- Update of the positions
        for (int i = 0; i < agents.size(); i++)
        {
            float fx = 0;
            float fy = 0;
            if (agents[i].type == "GREEN")  DrawCircleV(agents[i].cord, agents[i].m, GREEN);
            if (agents[i].type == "RED")    DrawCircleV(agents[i].cord, agents[i].m, RED);
            if (agents[i].type == "PURPLE") DrawCircleV(agents[i].cord, agents[i].m, PURPLE);
            if (agents[i].type == "BLUE")   DrawCircleV(agents[i].cord, agents[i].m, BLUE);
            for (int j = 0; j < agents.size(); j++)
            {
                float dx = agents[i].cord.x - agents[j].cord.x;
                float dy = agents[i].cord.y - agents[j].cord.y;
                float d = std::sqrt((dx * dx) + (dy * dy));
                if (d > 0.0f)
                {
                    float g = gravity(agents[i], agents[j], gravBB,gravBG,gravBP,gravBR,gravGG,gravGP,gravGR,gravRP,gravRR,gravPP);
                    float f = (g * ((1) / d));
                    fx += (f * dx);
                    fy += (f * dy);
                }
                agents[i].vel.x = (agents[i].vel.x + fx)*0.05;
                agents[i].vel.y = (agents[i].vel.y + fy)*0.05;
                agents[i].cord.x += agents[i].vel.x;
                agents[i].cord.y += agents[i].vel.y;
                if (agents[i].cord.y <= 0)
                {
                    agents[i].vel.y *= -1.5;
                    agents[i].cord.y = 5;
                }
                if (agents[i].cord.y > screenHeight)
                {
                    agents[i].vel.y *= -1.5;
                    agents[i].cord.y = screenHeight - 5;
                }
                if (agents[i].cord.x <= 0)
                {
                    agents[i].vel.x *= -1.5;
                    agents[i].cord.x = 5;
                }
                if (agents[i].cord.x > screenHeight)
                {
                    agents[i].vel.x *= -1.5;
                    agents[i].cord.x = screenHeight - 5;
                }
            }
        }
        //-------------------------------------------------------------------------------------------------------
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
//---------------------------------------------------------------------------------------------------------------------------