#include "GameManager.h"

void GameManager::init() {

    //// 1. まずメインライトを平行光源をつかうらしい
    //ChangeLightTypeDir(VGet(0.0f, -1.0f, 1.0f));

    //// 2. メインライトの高原を最大にする
    //SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

    //// 3. 全体を明るくして影をけす
    //SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));


    SetUseLighting(FALSE);


    camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F);
    player.init();

    // 最初から大きめの星を配置
    m_planets.push_back(std::make_shared<Planet>(tnl::Vector3(0, 0, 0), 3000.0f));

    skybox = dxe::Mesh::CreateCubeMV(80000, 10, 10);
    skybox->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/skybox/skybox_a.png"));
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


    // --- ここから：エネミーの自動生成（無双モード） ---
    m_enemy_spawn_timer += delta_time * time_scale;
    if (m_enemy_spawn_timer >= 0.3f) {
        m_enemy_spawn_timer = 0.0f;

        if (m_enemies.size() < 100) {

            //エネミー生成と初期化
            auto new_enemy = std::make_shared<Enemy>();
            new_enemy->init();
            

            // プレイヤーの周囲のランダムな位置
            float spawn_radius = 4000.0f;

            //角度をrandomにしてる
            float angle = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159f;

            new_enemy->m_position = player.m_position + tnl::Vector3(cos(angle), 0, sin(angle)) * spawn_radius;

            // 50%の確率で星か自分か選ぶ
            if ((rand() % 10) > 5) {

                new_enemy->switchTarget(EnemyState::TARGET_PLAYER, new_enemy->m_speed);
            }
            else {

                new_enemy->switchTarget(EnemyState::TARGET_PLANET, new_enemy->m_speed);
            }

            m_enemies.push_back(new_enemy);
        }
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

        // 将来的にHPが0になったら削除する判定はここに入れる
        ++it;
    }
    // ----------------------------------------------------


    // 3. 弾の生成判定
    if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
        spawnBullet();
    }
    //弾の射出処理
    for (auto it = m_bullets.begin(); it != m_bullets.end();) {
        (*it)->update(delta_time, time_scale); // 弾を前に進める！
        if ((*it)->m_life_timer <= 0) {
            it = m_bullets.erase(it); // 寿命が尽きたら消す
        }
        else {
            ++it;
        }
    }

    //  --- 弾 と 敵 の当たり判定---
    for (auto it_bullet = m_bullets.begin(); it_bullet != m_bullets.end();) {
        bool bullet_hit = false; // 

        for (auto it_enemy = m_enemies.begin(); it_enemy != m_enemies.end();) {

            // 弾と敵の距離のベクトルの差を出す
            tnl::Vector3 diff = (*it_bullet)->m_position - (*it_enemy)->m_position;
            float distance = diff.length();

            // 当たり判定の基準距離
            float hit_range = 500.0f;

            if (distance < hit_range) {
                // 
                (*it_enemy)->m_hp -= 5.0f;

               
                bullet_hit = true;

                // もし敵のHPが0以下になったら、敵をリストから消す
                if ((*it_enemy)->m_hp <= 0) {
                    it_enemy = m_enemies.erase(it_enemy); // 敵の消滅きえる
                    continue; // 削除された場合は自動で次を指すからインクリメントせず次のループへ
                }
            }

            // ⭕ ここが正しい位置！当たってない、またはHPが残っている場合は次の敵へ進める
            ++it_enemy;
        }

        // 何かに当たった弾はリストから削除する
        if (bullet_hit) {
            it_bullet = m_bullets.erase(it_bullet);
        }
        else {
            ++it_bullet;
        }
    }



    //エネミーがプレイヤーにあたった時のHPを減らす処理
    for (auto it_enemy = m_enemies.begin(); it_enemy != m_enemies.end();) {

        tnl::Vector3 diff = player.m_position - (*it_enemy)->m_position;

        float distance = diff.length();
        
        float hit_range = 120.0f;

        if (distance < hit_range) {
            player.m_hp -= (*it_enemy)->m_attack_power;

            it_enemy = m_enemies.erase(it_enemy);

            if (player.m_hp <= 0.0f) {
                player.m_hp = 0.0f;
            }

            continue;
        }

        it_enemy++;

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
    // 1. プレイヤーの現在の回転と位置を取得
    tnl::Quaternion player_rot = player.m_rotation;
    tnl::Vector3 player_pos = player.m_position;

    // 現在のスピード（velocityの長さ）を取得
    float current_speed = player.m_velocity.length();

   
    float target_z_offset = -450.0f - (current_speed * 4.0f);
    float target_y_offset = 120.0f + (current_speed * 0.3f);

    // 2. プレイヤー基準の「理想の上方向」と「理想のカメラ位置」を計算
    tnl::Vector3 target_up = tnl::Vector3::TransformCoord({ 0, 1, 0 }, player_rot);
    tnl::Vector3 cam_offset = tnl::Vector3::TransformCoord({ 0, target_y_offset, target_z_offset }, player_rot);
    tnl::Vector3 target_pos = player_pos + cam_offset;

    
    static bool is_first = true;
    static tnl::Vector3 current_cam_pos;
    static tnl::Vector3 current_cam_up;
    static tnl::Vector3 current_look_at;

    if (is_first) {
        current_cam_pos = target_pos;
        current_cam_up = target_up;
        current_look_at = player_pos + tnl::Vector3::TransformCoord({ 0, 0, 1 }, player_rot) * 200.0f;
        is_first = false;
    }

    // 3. MyLerpを使って、カメラの位置と上方向を「じわっと」追従させる
    current_cam_pos = MyLerp(current_cam_pos, target_pos, 0.1f);

    
    current_cam_up = MyLerp(current_cam_up, target_up, 0.2f);

    camera->setPosition(current_cam_pos);
    camera->setUpper(tnl::Vector3::Normalize(current_cam_up));

    // 4. カメラの注視点（ターゲット）の調整
    float look_ahead_dist = 200.0f + (current_speed * 2.0f);
    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, player_rot);
    tnl::Vector3 target_look_at = player_pos + forward * look_ahead_dist;

    current_look_at = MyLerp(current_look_at, target_look_at, 0.2f);

    camera->setTarget(current_look_at);

    // 5. カメラ情報を確定
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

    //スカイボックスを表示
    skybox->render(camera);

    player.render(camera);

    // エネミーの描写
    for (auto& e : m_enemies) e->render(camera);

    //弾の描写
    for (auto& b : m_bullets) b->render(camera);

    // UI表示
    DrawFormatString(10, 10, GetColor(255, 255, 255), "ENERGY: %.1f", player.energy);
    DrawFormatString(10, 30, GetColor(255, 255, 0), "BULLET COUNT: %d", (int)m_bullets.size());
   
    //プレイヤーのHP表示
    DrawFormatString(10, 70, GetColor(0, 255, 0), "PLAYER HP: %.1f / %.1f", player.m_hp, player.m_max_hp);

    
    //------デバッグ表示用---------
    // 画面に現在のエネミー数をだす
    DrawFormatString(10, 50, GetColor(255, 0, 0), "ENEMY COUNT: %d", (int)m_enemies.size());
}

void GameManager::end() {
    m_planets.clear();
    skybox = nullptr;
    camera = nullptr;
    m_enemies.clear(); 
}