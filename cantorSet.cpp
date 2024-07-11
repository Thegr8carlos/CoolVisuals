#include "raylib.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 1000;
    int derivations = 0;
    std::cout << "Type the number of derivations: ";
    std::cin >> derivations;

    float vertical_space = screenHeight / derivations;

    // Diccionary of rules
    std::map<char, std::string> rules;
    rules['A'] = "ABA";
    rules['B'] = "BBB";

    char axiom = 'A';
    std::string actual_string = std::string(1, axiom);
    std::string buffer_string = "";
    std::vector<std::string> history;
    //history.push_back(actual_string);
    std::vector<float> number_symbols;
    float pincel_x = 0;
    float pincel_y = 0;
    for (int i = 0; i < derivations; i++)
    {
        for (auto c : actual_string)
        {
            buffer_string.append(rules[c]);
        }
        std::cout << "String generated: " << buffer_string << std::endl;
        number_symbols.push_back(buffer_string.size());
        actual_string = buffer_string;
        history.push_back(actual_string);
        buffer_string = "";
    }

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // 

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        pincel_y = 0; // Reset pincel_y for drawing each frame
        for (int i = 0; i < derivations; i++)
        {
            pincel_x = 0; // Reset pincel_x for each row
            float space = screenWidth / number_symbols[i];
            for (int j = 0; j < number_symbols[i]; j++)
            {
                if (history[i][j] == 'A')
                {
                    DrawRectangle(pincel_x, pincel_y, space, vertical_space-10, GREEN);
                }
                else if (history[i][j] == 'B')
                {
                    //DrawRectangle(pincel_x, pincel_y, space, vertical_space - 10, DARKPURPLE);
                }
                pincel_x += space;
            }
            pincel_y += vertical_space;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
