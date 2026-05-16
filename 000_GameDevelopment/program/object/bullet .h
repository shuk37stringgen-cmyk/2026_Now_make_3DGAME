#pragma once
#include "CharacterBase.h" //弾のクラス


class Bullet : public CharacterBase {
public:

	float m_life_timer; //弾の消えるまでの時間

	void init() override; //初期化
	void update(float delta_time, float time_scale) override; //更新
	void render(Shared<dxe::Camera> cam) override; //描画

	void applySwingBy(tnl::Vector3 planet_pos) override; //スイングバイ用の加速処理(星の軌道に乗った時の加速処理をする)



};