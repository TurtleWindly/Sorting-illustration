#include "include/raylib.h"
#include <array>
#include <algorithm>

const int arraySize {50};
using Array_type = std::array<int, arraySize>;

void bubbleSort(std::array<int, arraySize>& arr)
{
   int i, j;
   bool swapped;
   for (i = 0; i < arraySize-1; i++)
   {
     swapped = false;
     for (j = 0; j < arraySize-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
            std::swap(arr[j], arr[j+1]);
           swapped = true;
        }
     }

     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
   }
}

void shuffleArray(Array_type& arr)
{
    Array_type numbers {};
    numbers.fill(-1);
    int random {};
    for (int iii {0}; iii < static_cast<int>(numbers.size()); iii++)
    {
        random = GetRandomValue(0, static_cast<int>(numbers.size()));
        auto found {std::find(numbers.begin(), numbers.end(), random)};
        if (found != numbers.end())
            iii--;
        else numbers[iii] = random;
    }

    arr.fill(-1);

    for (int iii {0}; iii < static_cast<int>(arr.size()); iii++)
    {
        auto found {std::find(arr.begin(), arr.end(), numbers[iii])};

        if (found != arr.end())
            iii--;
        else arr[iii] = numbers[iii];
    }

}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    std::array<int, arraySize> arr {};
    shuffleArray(arr);

    float boxWidth {static_cast<float>(screenWidth) / arraySize};
    float boxHeight {};
    auto boxSizeOnScreen {screenHeight / static_cast<float>(arraySize)};

    // Buble sort
    int loopTimes {0};
    int sortedTimes {0};
    bool swapped {false};
    bool isSort {true};

    InitWindow(screenWidth, screenHeight, "Raylib Window Template");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_S))
        {
            bubbleSort(arr);
        }
        if (IsKeyPressed(KEY_R))
        {
            shuffleArray(arr);
        }
        if (IsKeyDown(KEY_D))
        {
            isSort = true;
            loopTimes = 0;
            sortedTimes = 0;
        }

        // Buble sort
        if (isSort)
        {
            if (loopTimes < arraySize - 1)
            {
                if (sortedTimes < arraySize -loopTimes- 1)
                {
                    if (arr[sortedTimes] > arr[sortedTimes+1])
                    {
                        std::swap(arr[sortedTimes], arr[sortedTimes+1]);
                        swapped = true;
                    }
                    sortedTimes++;
                } else {
                    if (!swapped) isSort = false;
                    swapped = false;
                    sortedTimes = 0;
                    loopTimes++;
                }
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            for (int iii {0}; iii < arraySize; iii++)
            {
                boxHeight = boxSizeOnScreen * arr[iii];
                DrawRectangle(iii * boxWidth, screenHeight - static_cast<int>(boxHeight), boxWidth, boxHeight, WHITE);
            }

            DrawText(TextFormat("Loop Times: %i", loopTimes), 20, 20, 10, GREEN);
            DrawText(TextFormat("Sorted Times: %i", sortedTimes), 20, 50, 10, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
