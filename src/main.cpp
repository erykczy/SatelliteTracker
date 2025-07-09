#include <raylib.h>
#include <iostream>

int main() {
	InitWindow(800, 450, "Window");
	
	Camera camera{};
	camera.position = { 0.0f, 0.0f, 10.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Image image = LoadImage("res/earth.jpg");
	Texture2D texture = LoadTextureFromImage(image);

	Model sphereModel = LoadModel("res/models/earth.obj");
	sphereModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	DisableCursor();

	while(!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		DrawModel(sphereModel, Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
		DrawLine3D(Vector3{}, Vector3{ 5.0, 0.0, 0.0 }, RED);
		DrawLine3D(Vector3{}, Vector3{ 0.0, 0.0, 5.0 }, BLUE);

		EndMode3D();
		EndDrawing();
	}

	UnloadTexture(texture);
	UnloadModel(sphereModel);

	CloseWindow();

	return 0;
}