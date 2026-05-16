#pragma once
#include <vector>
#include "Common.h"
#include "object/player.h"
#include "object/bullet .h"
#include "object/planet.h"

class GameManager {
private:
    Player player;
    std::vector<Shared<Bullet>> m_bullets;
    std::vector<Shared<Planet>> m_planets;
    Shared<dxe::Camera> camera;
    Shared<dxe::Mesh> skybox;
    float time_scale = 1.0f;

public:
    void init();
    void update(float delta_time);
    void render();
    void end();

private:
    void updateCamera();
    void checkSwingBy();
	void spawnBullet();
};