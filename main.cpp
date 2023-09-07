#include <array>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <vector>

#include "ECS2.h"

#define WIDTH 1280
#define HEIGHT 720

// struct vec3 {
//     float x, y, z;
//     float magnitude() {
//         return std::sqrt(x*x + y*y + z*z);
//     }
// };
// 
// std::array<ECS::Entity, 10000> entities;
// 
// struct TransformComponent : public ECS::Component<TransformComponent> {
//     vec3 position;
//     vec3 rotation;
//     vec3 velocity;
//     vec3 scale;
// };
// 
// struct ImageComponent : public ECS::Component<ImageComponent> {
//     void* data;
//     const char* image_path;
// };
// 
// class RendererSystem : public ECS::System {
//     void initSystem() override {
//         auto transforms = ECS::queryComponentByName<TransformComponent>();
//         for (auto t : *transforms) {
//             float size = 0.41;
//             t->scale = {size, size, size};
//             t->position = {
//                 static_cast<float>(GetRandomValue(size, WIDTH - size)), 
//                 static_cast<float>(GetRandomValue(size, HEIGHT - size)), 0}
//             ;
//             t->velocity = {
//                 static_cast<float>(40 * GetRandomValue(-10, 10)),
//                 static_cast<float>(40 * GetRandomValue(-10, 10)),
//                 0
//             };
//             t->rotation = {0, 0, 0};
//         }
//     }
// 
//     void updateSystem(float dt) override {
//         auto transforms = ECS::queryComponentByName<TransformComponent>();
//         for (auto t : *transforms) {
//             t->position.x += t->velocity.x * dt;
//             t->position.y += t->velocity.y * dt;
//             t->position.z += t->velocity.z * dt;
// 
//             float size = t->scale.magnitude();
//             // DrawCircle(t->position.x, t->position.y, size, BLUE);
//         }
//     }
// };
// 
// RendererSystem rend;

int main() {

    // for (size_t i = 0; i < entities.size(); i++) {
    //     entities[i] = ECS::createEntity();
    //     ECS::addComponentToEntity<TransformComponent>(entities[i]);
    //     ECS::addComponentToEntity<ImageComponent>(entities[i]);
    // }

    // ECS::System::initAllSystems();

    // InitWindow(WIDTH, HEIGHT, "ECS Demonstration");

    // SetTargetFPS(60);

    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //     {
    //         //DrawCircleV(Vector2({WIDTH/2, HEIGHT/2}), 50, RED);
    //         ClearBackground(BLACK);
    //         ECS::System::updateAllSystems(GetFrameTime());
    //     }
    //     EndDrawing();
    //     SetWindowTitle(std::to_string(GetFPS()).c_str());
    // }

    // for (size_t i = 0; i < entities.size(); i++) {
    //     ECS::deleteEntity(entities[i]);
    // }

    // ECS::closeECS();

    // CloseWindow();
    
}
