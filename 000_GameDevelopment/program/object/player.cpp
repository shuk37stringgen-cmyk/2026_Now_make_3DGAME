#include "Player.h"

void Player::init() {
    m_mesh = dxe::Mesh::CreateFromFileMV("resource/graphics/example/PlayerBard.mv1", 0.5f);

    //スポーン位置
    m_position = { 0, 500, -4500 };
    m_velocity = { 0, 0, 0 };
    m_rotation = { 0, 0, 0, 1 };

    //角度
    m_senkai = 0;
    m_unazuki = 0;
    m_katamuki = 0;

    //反転した時の数値
    m_hanten_timer = 0.0f;
    m_is_hanten = false;

    //持つべき要素の数値
    energy = 0;
    m_hp = 100.0f;
    m_max_hp = 100.0f;

    //機体の速さやらなんやら
    m_max_speed = 30.0f;
    m_accel_power = 0.8f;
    m_friction = 0.98f;

    //スイングバイ中に必要な距離やら
    m_swingby_angle = 0;
    m_hosi_kyori = 0;
    m_target_planet = nullptr;
    m_swingby_cooltime = 0;
}

void Player::update(float delta_time, float time_scale) {
    // クールタイムの更新
    if (m_swingby_cooltime > 0.0f) {
        m_swingby_cooltime -= delta_time;
    }

    //プレイヤーの状態分けをする
    if (state == PlayerState::SWINGBY && m_target_planet) {

        // 1. 角度を進める
        m_swingby_angle += 0.02f * time_scale;

        // 2. 表面滑走の距離
        float h = m_target_planet->radius + 150.0f;

        // 3. メリーゴーランドのような回転をする計算
        m_position.x = m_target_planet->pos.x + cos(m_swingby_angle) * h;
        m_position.z = m_target_planet->pos.z + sin(m_swingby_angle) * h;
        m_position.y = m_target_planet->pos.y;

        // 4. 機体の向きを円の接線方向（進む方向）にぴったり沿わせる
        m_senkai = -m_swingby_angle + (3.141592f / 2.0f);
        m_unazuki = 0.0f;  // 上下ブレをリセット
        m_katamuki = 0.0f; // 左右の傾きをリセット

        m_rotation = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, m_senkai);

        // メッシュに即座に位置と回転を適用して固定
        m_mesh->setRotation(m_rotation);
        m_mesh->setPosition(m_position);

        // エネルギーを溜める
        energy += 0.5f * time_scale;
        if (energy > 100.0f) energy = 100.0f;
    }
    else {
        // ----【通常フライト移動の処理】-----

        

        //Playerそのものの動きを上下反転させる
       //上下反転ロジック
        if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
            //現在の自機の中心軸をそのまま反転させて使う
            tnl::Vector3 current_f = tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rotation);
            tnl::Quaternion flip_q = tnl::Quaternion::RotationAxis(current_f, tnl::ToRadian(180.0f));

            //姿勢の反転
            m_rotation = flip_q * m_rotation;

            //傾き、うなずきの動きも切り替え
            m_unazuki = -m_unazuki;
       }


        //前進
        tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rotation);
        if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
            m_velocity += forward * m_accel_power * time_scale;
        }

        // 旋回
        float turn_speed = 0.03f * time_scale;
        float pitch_speed = 0.02f * time_scale;
      

        tnl::Quaternion deltaRotation = { 0.0f, 0.0f, 0.0f, 1.0f };

        if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
            deltaRotation = deltaRotation * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, -turn_speed);
           
        }
        else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
            deltaRotation = deltaRotation * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, +turn_speed);
           
        }
        
        // 上下 (上と下の向ける角度の制限をする)
        if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
            if (m_unazuki > tnl::ToRadian(-90.0f)) {
                m_unazuki -= pitch_speed;
                deltaRotation = deltaRotation * tnl::Quaternion::RotationAxis({ 1, 0, 0 }, pitch_speed);
            }

          
        }
        else if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
            
            if (m_unazuki < tnl::ToRadian(90.0f)) {
                m_unazuki += pitch_speed;
                deltaRotation = deltaRotation * tnl::Quaternion::RotationAxis({ 1, 0, 0 }, -pitch_speed);
            }
        }
        else
        {
            m_unazuki = MyLerp(m_unazuki, 0.0f, 0.05f * time_scale);
        }

        //回転の適応
        m_rotation = deltaRotation * m_rotation;
   
        m_mesh->setRotation(m_rotation );



        //  進行方向の調整
        if (m_velocity.length() > 0.1f) {
            float current_speed = m_velocity.length();
            m_velocity = MyLerp(m_velocity, forward * current_speed, 0.05f * time_scale);
        }

        // 7. 移動の適用
        m_position += m_velocity * time_scale;
        m_velocity *= m_friction;
        m_mesh->setPosition(m_position);
    }
}

void Player::applySwingBy(tnl::Vector3 planet_pos) {
  
}

void Player::releaseSwingBy() {
    
    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rotation);
    m_velocity = forward * (m_max_speed + (energy * 0.3f));
    energy = 0;
}

void Player::render(Shared<dxe::Camera> cam) {
    if (m_mesh) {
        m_mesh->render(cam);
    }
}