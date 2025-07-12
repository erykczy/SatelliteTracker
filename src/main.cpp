#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <glm/glm.hpp>
#include <iostream>
constexpr int ELLIPSE_VERTICES = 100;
constexpr double EARTH_EQUATORIAL_RADIUS = 6378137.0;
constexpr double EARTH_AXIAL_TILT = 0.40910517666747085283091311613373;
constexpr double RENDER_SCALE = 1.0 / EARTH_EQUATORIAL_RADIUS;

std::vector<glm::vec3> ellipse(float semiMajorAxis, float semiMinorAxis) {
	constexpr float step{ 2 * PI / ELLIPSE_VERTICES };
	std::vector<glm::vec3> vertices{};
	vertices.reserve(ELLIPSE_VERTICES);
	float theta{ 0.0f };
	for(int i = 0; i < ELLIPSE_VERTICES; ++i) {
		vertices.emplace_back(semiMajorAxis * cosf(theta), semiMinorAxis * sinf(theta), 0);
		theta += step;
	}
	return vertices;
}

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

	float earthAngle{ 0.0f };
	while(!WindowShouldClose()) {
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		sphereModel.transform = MatrixMultiply(MatrixRotateY(earthAngle += 0.9f * GetFrameTime()), MatrixRotateZ(EARTH_AXIAL_TILT)); // raylib's wrong math
		DrawModel(sphereModel, Vector3{ 0.0f, 0.0f, 0.0f }, RENDER_SCALE * EARTH_EQUATORIAL_RADIUS, WHITE);
		DrawLine3D(Vector3{}, Vector3{ 5.0, 0.0, 0.0 }, RED);
		DrawLine3D(Vector3{}, Vector3{ 0.0, 0.0, 5.0 }, BLUE);
		DrawLine3D(Vector3{}, Vector3{ 0.0, 5.0, 0.0 }, GREEN);

		auto vertices{ ellipse(6793000 * RENDER_SCALE, 6793000 * RENDER_SCALE) };
		for(int i = 0; i < vertices.size() - 1; ++i) {
			DrawLine3D(*(Vector3*)(&vertices[i]), *(Vector3*)(&vertices[i + 1]), RED);
		}
		DrawLine3D(*(Vector3*)(&vertices[0]), *(Vector3*)(&vertices[vertices.size() - 1]), RED);

		EndMode3D();
		EndDrawing();
	}

	UnloadTexture(texture);
	UnloadModel(sphereModel);

	CloseWindow();

	return 0;
}