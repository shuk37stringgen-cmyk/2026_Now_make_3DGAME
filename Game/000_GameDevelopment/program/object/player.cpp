#include "Player.h"

void Player::init() {
    mesh = dxe::Mesh::CreateSphereMV(15.0f, 16, 16);
    mesh->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/test.jpg"));

	// 初期位置と物理パラメータの設定

    //初期値の設定
    m_positon = { 0, 500, -4500 };
    m_velocity = { 0, 0, 0 };
    m_rotation = { 0, 0, 0, 1 };

	// 状態の初期化
    energy = 0;

	// 操作用変数の初期化
    m_senkai = 0;
    m_unazuki = 0;
    m_katamuki = 0;

	// プレイヤーのHPの初期化
	m_hp = 100.0f;
	m_max_hp = 100.0f;

	// モードによって加算される変数の初期化
    m_max_speed = 30.0f;
    m_accel_power = 0.8f;
	m_friction = 0.98f;





}

void Player::update(float delta_time, float time_scale) {
    // 1. 前進
    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rotation);
    if (tnl::Input::IsKeyDown(eKeys::KB_SPACE)) {
        m_velocity += forward * m_accel_power * time_scale;
    }

    // 2. 旋回
    float turn_speed = 0.03f * time_scale;
    float roll_limit = 0.6f;
    if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
        m_senkai -= turn_speed;
        m_katamuki = MyLerp(m_katamuki, -roll_limit, 0.1f);
    }
    else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
        m_senkai += turn_speed;
        m_katamuki = MyLerp(m_katamuki, roll_limit, 0.1f);
    }
    else {
        m_katamuki = MyLerp(m_katamuki, 0.0f, 0.1f);
    }

    // 3. 上下
    if (tnl::Input::IsKeyDown(eKeys::KB_W)) m_unazuki += 0.02f * time_scale;
    else if (tnl::Input::IsKeyDown(eKeys::KB_S)) m_unazuki -= 0.02f * time_scale;

    // 4. 回転
    tnl::Quaternion qYaw = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, m_senkai);
    tnl::Quaternion qPitch = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, -m_unazuki);
    tnl::Quaternion qRoll = tnl::Quaternion::RotationAxis({ 0, 0, 1 }, -m_katamuki);
    m_rotation = qYaw * qPitch * qRoll;
    mesh->setRotation(m_rotation);

    // 5. 進行方向の調整
    if (m_velocity.length() > 0.1f) {
        float current_speed = m_velocity.length();
        // ここを Vector3版の MyLerp に書き換え！
        m_velocity = MyLerp(m_velocity, forward * current_speed, 0.05f * time_scale);
    }

    // 6. 移動の適用
    m_positon += m_velocity * time_scale;
    m_velocity *= m_friction;
    mesh->setPosition(m_positon);
}

void Player::applySwingBy(tnl::Vector3 planet_pos) {
    tnl::Vector3 to_planet = planet_pos - m_positon;
    tnl::Vector3 dir = tnl::Vector3::Normalize(to_planet);
    m_velocity += dir * 0.8f;
    energy += 0.5f;
    if (energy > 100.0f) energy = 100.0f;
}

void Player::releaseSwingBy() {
    tnl::Vector3 forward = tnl::Vector3::TransformCoord({ 0, 0, 1 }, m_rotation);
    m_velocity += forward * (energy * 0.2f);
    energy = 0;
}

void Player::render(Shared<dxe::Camera> cam) {
    if (mesh) {
        mesh->render(cam);
    }
}