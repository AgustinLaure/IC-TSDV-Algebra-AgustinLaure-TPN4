#include <vector>
#include <iostream>

#include "raylib.h"

#include "Figure.h"
#include "Frustum.h"

void cameraMove(Camera3D& camera, frustum::Frustum& frustum, bool& isCursorOn, float delta);
void drawWorldLines(Vector3 origin);
void figuresUpdate(std::vector<figure::Figure*> figures, int maxFigures);
void figuresDraw(std::vector<figure::Figure*> figures, int maxFigures);

int main()
{
	const float cameraDistance = 5.0f;
	const float rotationAngle = 0.05f;

	InitWindow(1280, 720, "TP_04");

	int maxFigures = 0;
	std::vector<figure::Figure*> figures;

	figures.push_back(new figure::Figure("Cube", "res/models/cube.obj", { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f, 0.0f }, 0.05f * RAD2DEG, WHITE));
	maxFigures++;

	figures.push_back(new figure::Figure("Deca", "res/models/decahedron.obj", { 3.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f, 0.0f }, 0.05f * RAD2DEG, WHITE));
	maxFigures++;

	figures.push_back(new figure::Figure("Octa", "res/models/octahedron.obj", { -3.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f, 0.0f }, 0.05f * RAD2DEG, WHITE));
	maxFigures++;

	Vector3 origin = { 0,0,0 };
	Camera3D camera = { 0 };

	camera.position = { cameraDistance, cameraDistance, cameraDistance };  // Camera position
	camera.target = origin;						// Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	frustum::Frustum frustum = frustum::Frustum(camera, 1920.0f, 1080.0f, 60.0f * DEG2RAD, 0.1f, 50.f);

	DisableCursor();

	bool isCursorOn = false;
	float delta = 0.0f;

	while (!WindowShouldClose())
	{
		//Update
		delta = GetFrameTime();
		cameraMove(camera, frustum, isCursorOn, delta);
		figuresUpdate(figures, maxFigures);
		frustum.updatePos(camera);
		frustum.update(figures, maxFigures);

		//Draw
		BeginDrawing();
		BeginMode3D(camera);
		ClearBackground(BLACK);

		drawWorldLines(origin);
		figuresDraw(figures, maxFigures);
		frustum.draw(camera);

		EndMode3D();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}

void cameraMove(Camera3D& camera, frustum::Frustum& frustum, bool& isCursorOn, float delta)
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
		frustum.updatePos(camera);
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
		if (figures[i]->isDrawable)
		{
			figures[i]->draw();
		}
	}
}