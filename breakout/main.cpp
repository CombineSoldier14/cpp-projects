#include "raylib.h"
#include <vector>

std::vector<Rectangle> getRow(float y, float rectangleWidth, float rectangleHeight) {
    std::vector<Rectangle> recs;
    float x = 1;
    for(int i = 0; i < 14; i++) {
        Rectangle rec = { x, y, rectangleWidth, rectangleHeight };
        recs.push_back(rec);
        x += rectangleWidth;
    }
    return recs;
}

int main(void) {
    int screenWidth = 632;
    int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "Breakout");
    float rectangleWidth = 45;
    float rectangleHeight = 20;
    const float RADIUS = 5;
    std::vector row1recs = getRow(1, rectangleWidth, rectangleHeight);
    std::vector row2recs = getRow(rectangleHeight, rectangleWidth, rectangleHeight);
    std::vector row3recs = getRow(rectangleHeight * 2, rectangleWidth, rectangleHeight);
    std::vector row4recs = getRow(rectangleHeight * 3, rectangleWidth, rectangleHeight);
    std::vector row5recs = getRow(rectangleHeight * 4, rectangleWidth, rectangleHeight);
    std::vector<std::vector<Rectangle>> allRecs = {row1recs, row2recs, row3recs, row4recs, row5recs};
    Rectangle plate = { (float)(screenWidth / 2), 465, 100, 10 };
    Vector2 ball = { (float)(screenWidth / 2), 280 };
    bool ballXUp = true;
    bool ballYUp = false;
    bool lose = false;
    float ballSpeed = 2.5f;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (!lose) {
            if(ball.x > (screenWidth - RADIUS) || ball.x < RADIUS) {
                ballXUp = !ballXUp;
            }
            if(ball.y < RADIUS) {
                ballYUp = true;
            }
            if(ball.y > (screenHeight - RADIUS)) {
            lose = true;
            }
            if (ballXUp) {
                ball.x += ballSpeed;
            } else {
                ball.x -= ballSpeed;
            }
            if (ballYUp) {
                ball.y += ballSpeed;
            } else {
                ball.y -= ballSpeed;
            }
            if(CheckCollisionCircleRec(ball, RADIUS, plate)) {
                float plateCenter = plate.x + plate.width / 2;
                ballYUp = false;
                if(ball.x < plateCenter) {
                    ballXUp = false;
                } else {
                    ballXUp = true;
                }
            }
            for(auto& i2 : allRecs) {
                for(int i1 = 0; i1 < i2.size(); i1++) {
                    if(CheckCollisionCircleRec(ball, RADIUS, i2[i1])) {
                        ballYUp = !ballYUp;
                        float rectangleCenter = i2[i1].x + i2[i1].width / 2;
                        if(ball.x < rectangleCenter) {
                            ballXUp = true;
                        } else {
                            ballXUp = false;
                        }
                        i2.erase(i2.begin() + i1);
                        i1--;
                    }
                }
            }
            float mousePosX = GetMousePosition().x;
            if(mousePosX < 0) {
                plate.x = 1;
            } else if (mousePosX > (screenWidth - plate.width)) {
                plate.x = (screenWidth - plate.width);
            } else {
                plate.x = mousePosX;
            }
        }

        BeginDrawing();

            ClearBackground(BLACK);

            DrawCircleV(ball, RADIUS, RAYWHITE);

            for(int i = 0; i < allRecs.size(); i++) {
                Color rowColor;
                switch(i) {
                    case 0: rowColor = RED; break;         // First row -> RED
                    case 1: rowColor = ORANGE; break;      // Second row -> ORANGE
                    case 2: rowColor = GREEN; break;       // Third row -> GREEN
                    case 3: rowColor = YELLOW; break;      // Fourth row -> YELLOW
                    case 4: rowColor = BLUE; break;        // Fifth row -> BLUE
                    default: rowColor = WHITE; break;      // Default color
                }
                for(auto& rec : allRecs[i]) {
                    DrawRectangleRec(rec, rowColor); // Draw the block with the row-specific color
                }
            }
            DrawRectangleRec(plate, SKYBLUE);
            if(lose) {
                DrawRectangle((screenWidth / 2) - 100, (screenHeight / 2) - 50, 200, 100, RAYWHITE);
                DrawText("You lose!", (screenWidth / 2) - 70, (screenHeight / 2) - 15, 30, BLACK);
            }

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
