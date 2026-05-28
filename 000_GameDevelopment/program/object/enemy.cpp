#include "enemy.h"

void Enemy::init() {
	//Enemyメッシュのよみこみ
	m_mesh = dxe::Mesh::CreateFromFileMV("resource/graphics/example/Enemy_Obj_pt2.mv1", 0.5f);

	m_hairaito_color = GetColorF(1.0f, 1.0f, 0.0f, 1.0f);

	//エネミーの基本情報
	m_hp = 10.0f;
	m_max_hp = 10.0f;
	m_speed = 2.0f;
	m_attack_power = 5.0f;

	m_velocity = { 0, 0, 0 };
	m_rotation = { 0, 0, 0, 1 };

	
}

void Enemy::update(float delta_time, float time_scale) {
	m_position += m_velocity * time_scale;    //位置の更新をする

	if (m_mesh) {
		m_mesh->setPosition(m_position);

		if (m_velocity.length() > 0.1f) {
			float angle = atan2(m_velocity.z, m_velocity.x);
			m_rotation = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, -angle + (3.1415f / 2.0f));
			m_mesh->setRotation(m_rotation);
		}


	}
}

void Enemy::switchTarget(EnemyState state, float speed) {
	m_state = state;
	m_speed = speed;
}

void Enemy::applySwingBy(tnl::Vector3 planet_pos) {

}

void Enemy::render(Shared<dxe::Camera> cam) {
	if (m_mesh) {
		MV1SetMaterialEmiColor(m_mesh->getDxMvHdl(), 0, m_hairaito_color);
		m_mesh->render(cam);
	}
}