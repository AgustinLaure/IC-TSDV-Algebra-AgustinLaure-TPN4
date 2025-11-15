#include <vector>

#include "raylib.h"

#include "Figure.h"

void cameraMove(Camera3D& camera, bool& isCursorOn, float delta);
void drawWorldLines(Vector3 origin);
void figuresUpdate(std::vector<figure::Figure*> figures, int maxFigures);
void figuresDraw(std::vector<figure::Figure*> figures, int maxFigures);

int main()
{
    const float cameraSpeed = 25.0f;

    InitWindow(1280, 720, "TP_04");

    int maxFigures = 0;
    std::vector<figure::Figure*> figures;

    figures.push_back(new figure::Figure("Cube", "res/models/cube.obj", { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f },  { 0.0f,0.0f, 0.0f }, 0.05f * RAD2DEG, WHITE));
    maxFigures++;

    figures.push_back(new figure::Figure("Deca", "res/models/decahedron.obj", { 3.0f,0.0f,0.0f } , { 1.0f,1.0f,1.0f },  { 0.0f,0.0f, 0.0f }, 0.05f * RAD2DEG, WHITE));
    maxFigures++;

    figures.push_back(new figure::Figure("Octa", "res/models/octahedron.obj", { -3.0f,0.0f,0.0f } , { 1.0f,1.0f,1.0f },  { 0.0f,0.0f, 0.0f }, 0.05f * RAD2DEG, WHITE));
    maxFigures++;

    Vector3 origin = { 0,0,0 };
    Camera3D camera = { 0 };
    const float cameraDistance = 5.0f;
    const float rotationAngle = 0.05f;
    camera.position = { cameraDistance, cameraDistance, cameraDistance };  // Camera position
    camera.target = origin;						// Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    DisableCursor();

    bool isCursorOn = false;
    float delta = 0.0f;

    while (!WindowShouldClose())    
    {
        //Update
        delta = GetFrameTime();
        cameraMove(camera, isCursorOn, delta);
        figuresUpdate(figures,maxFigures);

        //Draw
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(BLACK);

        drawWorldLines(origin);
        figuresDraw(figures, maxFigures);

        EndMode3D();
        EndDrawing();
    }
    CloseWindow();        
  
    return 0;
}

void cameraMove(Camera3D& camera, bool& isCursorOn, float delta)
{
    if (IsKeyPressed(KEY_TAB))
    {
        isCursorOn = !isCursorOn;

        if (isCursorOn)
        {
            EnableCursor();
        }
        else
        {
            DisableCursor();
        }
    }

    if (!isCursorOn)
    {
        UpdateCamera(&camera, CAMERA_FREE);
    }
}

void drawWorldLines(Vector3 origin)
{
    DrawGrid(100, 5);
    DrawLine3D(origin, { 10,0,0 }, RED);
    DrawLine3D(origin, { 0,10,0 }, GREEN);
    DrawLine3D(origin, { 0,0,10 }, BLUE);
}

void figuresUpdate(std::vector<figure::Figure*> figures, int maxFigures)
{
    for (int i = 0; i < maxFigures; i++)
    {
       
    }
}

void figuresDraw(std::vector<figure::Figure*> figures, int maxFigures)
{
    for (int i = 0; i < maxFigures; i++)
    {
        figures[i]->draw();
    }
}