#include "GameManager.h"

void GameManager::init() {
    camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);
    player.init();

    // スケッチにあった「加速スター」を配置
    planets.push_back(std::make_shared<Planet>(tnl::Vector3(0, 0, 0), 3000.0f));

    skybox = dxe::Mesh::CreateCubeMV(80000, 10, 10);
    skybox->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/skybox/skybox_a.png"));
}

void GameManager::update(float delta_time) {
    checkSwingBy();

    float target_scale = (player.state == PlayerState::SWINGBY) ? SLOW_TIME_SCALE : 1.0f;
    time_scale = MyLerp(time_scale, target_scale, 0.1f);

    player.update(delta_time, time_scale);
    updateCamera();
}

void GameManager::render() {
    if (skybox) skybox->render(camera);
    for (auto& p : planets) p->render(camera);
    player.render(camera);

    // スケッチにあったUI（HPやエネルギー）を表示
    DrawFormatString(10, 10, GetColor(255, 255, 255), "ENERGY: %.1f", player.energy);
}


void GameManager::updateCamera() {
    // 1. 本来あるべき理想のカメラ位置（自機の後ろ）を計算
    float cam_dist = (player.state == PlayerState::SWINGBY) ? -350.0f : -200.0f;
    float cam_height = 55.0f;

    tnl::Quaternion rot = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, player.m_senkai) * tnl::Quaternion::RotationAxis({ 1, 0, 0 }, -player.m_unazuki);

    // 理想の位置（目標地点）
    tnl::Vector3 target_pos = player.m_positon + tnl::Vector3::TransformCoord({ 0, cam_height, cam_dist }, rot);

    // 2. 現在のカメラ位置から、目標地点へ「じわっと」近づける
    tnl::Vector3 current_pos = camera->getPosition();
    float follow_speed = 0.12f; // これがカメラの「遊び」。0.1〜0.2くらいで調整

    tnl::Vector3 next_pos;
    next_pos.x = MyLerp(current_pos.x, target_pos.x, follow_speed);
    next_pos.y = MyLerp(current_pos.y, target_pos.y, follow_speed);
    next_pos.z = MyLerp(current_pos.z, target_pos.z, follow_speed);

    camera->setPosition(next_pos);

    // 3. 注視点（カメラの向き）も自機の少し先を見るようにして躍動感を出す
    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot);
    camera->setTarget(player.m_positon + forward * 400.0f);

    camera->update();
}

void GameManager::checkSwingBy() {
    Shared<Planet> near_planet = nullptr;
    for (auto& p : planets) {
        float dist = (p->pos - player.m_positon).length();
        // 星の重力圏（gravity_range）に入っているかチェック
        if (dist < p->gravity_range) {
            near_planet = p;
            break;
        }
    }

    // Shiftキー判定と状態切り替え
    if (near_planet && tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {
        player.state = PlayerState::SWINGBY;
        player.applySwingBy(near_planet->pos); // 星に引き寄せられる力を計算
    }
    else {
        if (player.state == PlayerState::SWINGBY) {
            player.state = PlayerState::BOOST;
            player.releaseSwingBy(); // 溜めたエネルギーで加速放出
        }
        else if (player.state == PlayerState::BOOST) {
            // ブーストが終わったら通常飛行に戻る
            if (player.m_velocity.length() <= player.m_max_speed) {
                player.state = PlayerState::FLIGHT;
            }
        }
        else {
            player.state = PlayerState::FLIGHT;
        }
    }
}

void GameManager::end() {
    planets.clear();
    skybox = nullptr;
    camera = nullptr;
}