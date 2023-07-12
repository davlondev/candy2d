#pragma once

#include "../stdafx.h"

#include "BaseScene.h" 

#include "../Utils/GameMath.h"
#include "../GameClasses/EntityManager.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimatorComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/EnemyAIComponent.h"
#include "../Components/TilemapComponent.h"


// example scene
// inspired by vampire survivors 
// https://store.steampowered.com/app/1794680/Vampire_Survivors/


class MainScene : public Scene {
private:

    EntityManager *_entityManager;
    // pointer to tilemap manager

public:
    MainScene(EntityManager* entityManager) : _entityManager(entityManager) {
        std::cout << "Main scene created" << std::endl;
    }

    ~MainScene() {
        std::cout << "Main scene cleanup." << std::endl;
        _entityManager->RemoveAllEntities(); 
    }

    void Init() {
        PrepareTilemap();
        PrepareEntities();
    }

    void PrepareEntities() {
        // init entities?

        // create player
        // wizard_m_run 192 164 16 28 4
        _entityManager->CreateEntity(
            new PlayerComponent(),
            new TransformComponent(glm::vec2(-384.0f, -190.0f), glm::vec2(8.0f, 24.0f)),
            new SpriteComponent(SDL_Rect{ 192, 164, 16, 28 }),
            new AnimatorComponent(new Animation(SDL_Rect{192, 164, 16, 28}, 0.09f, 4)),
            // new HealthComponent(100),
            new ColliderComponent(glm::vec4(3.0f, 14.0f, 10.0f, 13.0f), false, false)
        );

        // create enemies
        for (int i = 0; i < 3; i++)
            _entityManager->CreateEntity(
                new TransformComponent(glm::vec2(-300.0f + 25.0f * -i, -100.0f), glm::vec2(8, 19)),
                new SpriteComponent(SDL_Rect{ 368, 369, 16, 23 }, SPRITE_LAYER_YSORT),
                new AnimatorComponent(new Animation(SDL_Rect{368, 369, 16, 23}, 0.03f, 4)),
                // new HealthComponent(100),
                new EnemyAIComponent(),
                new ColliderComponent(glm::vec4(3.0f, 12.0f, 10.0f, 10.0f), false, false)
            );

        // crate 288 298 16 22
        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(-400.0f, -150.0f), glm::vec2(8.0f, 19.0f)),
            new SpriteComponent(SDL_Rect{288, 408, 16, 24}),
            new ColliderComponent(glm::vec4(1.0f, 5.0f, 14.0f, 17.0f), false, false)
        );

        // chest_empty_open_anim 304 288 16 16 3
        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(-350.0f, -150.0f), glm::vec2(8.0f, 13.0f)),
            new SpriteComponent(SDL_Rect{304, 400, 16, 16}),
            new AnimatorComponent(new Animation(SDL_Rect{304, 400, 16, 16}, 0.1f, 3)),
            new ColliderComponent(glm::vec4(1.0f, 5.0f, 14.0f, 11.0f), false, true)
        );

        // add idle ogre
        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(-330.0f, -200.0f), glm::vec2(16.0f, 29.0f)),
            new SpriteComponent(SDL_Rect{16, 380, 32, 36}, SPRITE_LAYER_YSORT),
            new AnimatorComponent(new Animation(SDL_Rect{16, 380, 32, 36}, 0.2f, 4)),
            new ColliderComponent(glm::vec4(6.0f, 16.f, 20.0f, 14.0f), false, true)
        );

        // map colliders
        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(0.0f, 0.0f)),
            new ColliderComponent(glm::vec4(0.0f, 0.0f, 770, 70), false, true)
        );

        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(0.0f, -365.0f)),
            new ColliderComponent(glm::vec4(0.0f, 0.0f, 770, 32), false, true)
        );

        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(19.0f, 0.0f)),
            new ColliderComponent(glm::vec4(0.0f, 0.0f, 39, 365), false, true)
        );
        
        _entityManager->CreateEntity(
            new TransformComponent(glm::vec2(-748.0f, 0.0f)),
            new ColliderComponent(glm::vec4(0.0f, 0.0f, 32, 365), false, true)
        );
    }

    void PrepareTilemap() {
        std::vector<SDL_Rect> tileRects = {
            // floor tiles (0 - 8)
            {16, 64, 16, 16},
            {32, 64, 16, 16},
            {48, 64, 16, 16},
            {16, 80, 16, 16},
            {32, 80, 16, 16},
            {48, 80, 16, 16},
            {16, 96, 16, 16},
            {32, 96, 16, 16},

            // top wall tiles

            {32, 0, 16, 16},   // wall very top (index 8)

            {32, 16, 16, 16}, // top wall (index 9)
            {16, 16, 16, 16}, // top wall (index 10)
            {48, 32, 16, 16}, // top wall hole 1 (index 11)
            {48, 48, 16, 16}, // top wall hole 2 (index 12)
            {31, 120, 16, 16}, // top left corner (13)
            {0, 152, 16, 16}, // wall left (14)
            {0, 136, 16, 16}, // wall bottom (15)
            {32, 168, 16, 16}, // bottom left corner (16)
            {0, 136, 16, 16}, // top left corner (17)
            {16, 152, 16, 16}, // right wall (18)
            {16, 136, 16, 16}, // top right corner (19)
            {64, 152, 16, 16}, // wall edge bottom right (20)
        };

        int cleans[3] = {3, 5, 7};
        int dirtys[4] = {0, 1, 2, 4};
        const int gridWidth = 48;
        const int gridHeight = 24;

        // tilemap data
        std::vector<std::vector<int>> data(gridHeight, std::vector<int>(gridWidth));

        for (int y = 0; y < gridHeight; y++) {
            for (int x = 0; x < gridWidth; x++) {

                int id = 0;
                // very top wall edge
                if (y == 0) {
                    data[y][x] = 8; // wall top
                    continue;
                }

                // wall left
                if (x == 0) {
                    id = 14;
                    data[y][x] = id;
                    continue;
                }

                // wall top
                if (y == gridHeight - 1) {
                    id = 9;
                    data[y][x] = id;
                    continue;
                }

                // wall right
                if (x == gridWidth - 1)  {
                    id = 18;
                    data[y][x] = id;
                    continue;
                }

                // wall main (randomized tiles)
                if (y >= 1 && y <= 4) {
                    int r = rand() % 100;
                    if (r < 60) {
                    id = 9;
                    }
                    else if (r >= 60 && r < 70) {
                        id = 12;
                    }
                    else if (r >= 70 && r <= 85) {
                        id = 10;
                    }
                    else {
                        id = 11;
                    }
                    data[y][x] = id;
                    continue;
                }

                int idx = rand() % 100;
                int idx2 = 0;

                if (idx < 75) {
                    idx2 = cleans[rand() % 3]; // 75% chance to draw clean tile
                }
                else if (idx >= 75 && idx <= 95) {
                    idx2 = 6; // 15% chance of drawing medium clean tile
                }
                else {
                    idx2 = dirtys[rand() % 4]; // 10% chance of drawing dirty tile
                }

                data[y][x] = 7 - idx2;
            }
        }

        // corners
        // y, x
        data[0][0] = 17;
        data[0][gridWidth - 1] = 19;
        data[gridHeight - 1][gridWidth - 1] = 18;

        //Tilemap* tilemap = new Tilemap(_renderer, &camera, _tileSet, glm::ivec2(0, 0), glm::ivec2(16, 16));
        // tilemap->GenerateTexture(data, tileRects);

        _entityManager->AddTilemap(new TilemapComponent(tileRects, data, glm::ivec2(0, 0), glm::ivec2(16, 16)));
    }
};