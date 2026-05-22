#include "GameManager.h"

void GameManager::init() {

    // 1. まずメインライトを「平行光源」に切り替える（これでライトが初期化される）
    ChangeLightTypeDir(VGet(0.0f, -1.0f, 1.0f));

    // 2. 切り替わったメインライト（0番）の光の強さを最大（白）に上書きする！
    SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

    // 3. 最後にグローバルアンビエントライト（環境光）を最大にして、影を完全に消し去る！
    SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));



    camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);
    player.init();

    // 最初から大きめの星を配置
    m_planets.push_back(std::make_shared<Planet>(tnl::Vector3(0, 0, 0), 3000.0f));

    //skybox = dxe::Mesh::CreateCubeMV(80000, 10, 10);
   // skybox->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/skybox/skybox_a.png"));
}

void GameManager::update(float delta_time) {

    // 1. スイングバイの判定と突入・離脱を一括管理
    checkSwingBy();

    // 時間の流れ（タイムスケール）の調整
    float target_scale = (player.state == PlayerState::SWINGBY) ? SLOW_TIME_SCALE : 1.0f;
    time_scale = MyLerp(time_scale, target_scale, 0.1f);

    // 2. プレイヤーの更新
    player.update(delta_time, time_scale);
    updateCamera();


    // --- 【ここから：エネミーの自動生成（無双モード）】 ---
    m_enemy_spawn_timer += delta_time * time_scale;
    if (m_enemy_spawn_timer >= 0.3f) { // 0.3秒ごとにドバドバ湧かせるぜ！
        m_enemy_spawn_timer = 0.0f;

        auto new_enemy = std::make_shared<Enemy>();
        new_enemy->init();

        // プレイヤーの周囲のランダムな位置（少し画面外の遠く）にスポーン
        float spawn_radius = 4000.0f;
        
        //角度をrandomにしてる
        float angle = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159f;

        new_enemy->m_position = player.m_position + tnl::Vector3(cos(angle), 0, sin(angle)) * spawn_radius;

        // 50%の確率で星か自分か選ぶ
        if ((rand() % 10) > 5) {
           
            float random_speed = 12.0f + (static_cast<float>(rand()) / RAND_MAX) * 6.0f;
            new_enemy->switchTarget(EnemyState::TARGET_PLAYER, random_speed);
        }
        else {
           
            float random_speed = 8.0f + (static_cast<float>(rand()) / RAND_MAX) * 4.0f;
            new_enemy->switchTarget(EnemyState::TARGET_PLANET, random_speed);
        }

        m_enemies.push_back(new_enemy);
    }

    // 星の座標
    tnl::Vector3 planet_pos = m_planets.empty() ? tnl::Vector3(0, 0, 0) : m_planets[0]->pos;

    // --- 【ここから：エネミーの一括移動計算と更新】 ---
    for (auto it = m_enemies.begin(); it != m_enemies.end();) {
        auto enemy = *it;

        // 狙うターゲットに応じて目的地を変える
        tnl::Vector3 target_pos = (enemy->m_state == EnemyState::TARGET_PLAYER) ? player.m_position : planet_pos;

        // 目的地に向かう移動ベクトルを計算して、エネミーの m_velocity に叩き込む
        tnl::Vector3 dir = target_pos - enemy->m_position;
        if (dir.length() > 10.0f) {
            enemy->m_velocity = tnl::Vector3::Normalize(dir) * enemy->m_speed;
        }
        else {
            enemy->m_velocity = { 0, 0, 0 }; // 到着したら停止
        }

        // エネミー自身の位置・メッシュ更新処理を呼び出す
        enemy->update(delta_time, time_scale);

        // 将来的にHPが0になったら削除する判定はここに入れるぜ
        ++it;
    }
    // ----------------------------------------------------


    // 3. 弾の生成判定
    if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
        spawnBullet();
    }

    // 4. 弾の更新と寿命管理
    for (auto it = m_bullets.begin(); it != m_bullets.end();) {
        (*it)->update(delta_time, time_scale);
        if ((*it)->m_life_timer <= 0) {
            it = m_bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

void GameManager::checkSwingBy() {
    // プレイヤーに一番近い星を探す
    Shared<Planet> near_planet = nullptr;
    for (auto& p : m_planets) {
        float dist = (p->pos - player.m_position).length();
        // 星の重力圏に入っているかの確認
        if (dist < p->gravity_range) {
            near_planet = p;
            break;
        }
    }

    // LSHIFTを押している、かつクールタイム中でない、かつ重力圏内に星がある場合
    if (near_planet && tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) && player.m_swingby_cooltime <= 0) {

        // まだスイングバイモードに入っていない「突入の瞬間」だけ初期位置と角度を確定させる
        if (player.state != PlayerState::SWINGBY) {
            player.state = PlayerState::SWINGBY;
            player.m_target_planet = near_planet;

            // 現在の自機の位置から、星に対する「初期の角度（ラジアン）」を逆算
            tnl::Vector3 dir = player.m_position - near_planet->pos;
            player.m_swingby_angle = atan2(dir.z, dir.x);

            // 突入した瞬間に、星の表面ギリギリ（半径 + 150.0f）に引き寄せて固定
            float h = near_planet->radius + 150.0f;
            player.m_position.x = near_planet->pos.x + cos(player.m_swingby_angle) * h;
            player.m_position.z = near_planet->pos.z + sin(player.m_swingby_angle) * h;
            player.m_position.y = near_planet->pos.y; // 高さは星と同じに揃える
        }
    }
    else {
        // LSHIFTを離した、または星から離れた場合
        if (player.state == PlayerState::SWINGBY) {
            player.state = PlayerState::BOOST;
            player.releaseSwingBy(); // 溜めたエネルギーでドカンと離脱！
        }
        else if (player.state == PlayerState::BOOST) {
            // ブーストが落ち着いたら通常飛行に戻す
            if (player.m_velocity.length() <= player.m_max_speed) {
                player.state = PlayerState::FLIGHT;
                player.m_target_planet = nullptr;
            }
        }
        else {
            player.state = PlayerState::FLIGHT;
            player.m_target_planet = nullptr;
        }
    }
}

void GameManager::updateCamera() {
    // スイングバイ中も通常時も同じ距離（-200.0f）のまま固定して、ガタつきを無くす
    float cam_dist = -200.0f;
    float cam_height = 55.0f;

    tnl::Quaternion rot = player.m_rotation;

    // 1. 自機の後ろの位置（目標地点）を計算
    tnl::Vector3 target_pos = player.m_position + tnl::Vector3::TransformCoord({ 0, cam_height, cam_dist }, rot);

    // 2. 現在の位置から、目標地点へじわっと近づける
    tnl::Vector3 current_pos = camera->getPosition();
    float follow_speed = 0.12f; // これがカメラの「遊び」。0.1〜0.2くらいで調整

    tnl::Vector3 next_pos;
    next_pos.x = MyLerp(current_pos.x, target_pos.x, follow_speed);
    next_pos.y = MyLerp(current_pos.y, target_pos.y, follow_speed);
    next_pos.z = MyLerp(current_pos.z, target_pos.z, follow_speed);

    camera->setPosition(next_pos);

    // 3. カメラの向きも自機の少し先を見るようにして躍動感を出す
    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot);
    camera->setTarget(player.m_position + forward * 400.0f);

    camera->update();
}


void GameManager::spawnBullet() {
    auto new_bullet = std::make_shared<Bullet>();
    new_bullet->init();

    new_bullet->m_position = player.m_position;

    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, player.m_rotation);
    new_bullet->m_velocity = forward * new_bullet->m_max_speed;

    m_bullets.push_back(new_bullet);
}

void GameManager::render() {
    for (auto& p : m_planets) p->render(camera);
    player.render(camera);

    // エネミーの描写
    for (auto& e : m_enemies) e->render(camera);

    //弾の描写
    for (auto& b : m_bullets) b->render(camera);

    // UI表示
    DrawFormatString(10, 10, GetColor(255, 255, 255), "ENERGY: %.1f", player.energy);
    DrawFormatString(10, 30, GetColor(255, 255, 0), "BULLET COUNT: %d", (int)m_bullets.size());
   
    //------デバッグ表示用---------
    // 画面に現在のエネミー数を出してみようぜ
    DrawFormatString(10, 50, GetColor(255, 0, 0), "ENEMY COUNT: %d", (int)m_enemies.size());
}

void GameManager::end() {
    m_planets.clear();
    skybox = nullptr;
    camera = nullptr;
    m_enemies.clear(); 
}