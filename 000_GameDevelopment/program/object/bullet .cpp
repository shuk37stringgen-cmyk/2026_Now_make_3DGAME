#include "bullet .h"

void Bullet::init() {

	//1.　メッシュの作成
	/*m_mesh = dxe::Mesh::CreateSphereMV(30.0f, 8, 8);
	m_mesh->setTexture(dxe::Texture::CreateFromFile("resource/graphics/example/laser.mv1"));*/

	m_mesh = dxe::Mesh::CreateFromFileMV("resource/graphics/example/laser2.mv1", 1.0f);

	//キャラのハイライトを変えるカラー
	m_hairaito_color = GetColorF(1.0f,  1.0f,  0.0f,  1.0f);

	//2.　弾の基本用パラメータの設定
	m_max_speed = 300.0f;
	m_life_timer = 2.0f;    // 2秒で消える
	m_friction = 0.98f;
}

void Bullet::update(float delta_time, float time_scale) {
	// 1. 移動
	m_position += m_velocity * time_scale;

	// 2. 摩擦
	m_velocity *= m_friction;

	// 3. 寿命の減少
	m_life_timer -= delta_time * time_scale;
}

void Bullet::render(Shared<dxe::Camera> cam) {
	m_mesh->setPosition(m_position);
	m_mesh->setRotation(m_rotation);
	m_mesh->render(cam);

	if (m_mesh) {
		
		m_mesh->render(cam); 
	}
}

void Bullet::applySwingBy(tnl::Vector3 planet_pos) {
	
}