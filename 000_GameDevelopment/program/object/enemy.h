#pragma once
#include "CharacterBase.h" 

enum class EnemyState {
	TARGET_PLAYER,
	TARGET_PLANET,
};

class Enemy : public CharacterBase{
public:
	EnemyState m_state = EnemyState::TARGET_PLAYER;
	float m_speed;
	float m_attack_power;


	//基底クラスのオーバーライド
	void init() override;
	void update(float delta_time, float time_scale) override;
	void render(Shared<dxe::Camera> cam) override;

	//スイングバイ用の加速処理(星の軌道に乗った時の加速処理をする) だがエネミーは使わない
	void applySwingBy(tnl::Vector3 planet_pos) override ;

	//エネミーがプレイヤー、惑星のどちらをターゲットにしているかを切り替える関数
	void switchTarget(EnemyState state, float speed) ;

private:

};

