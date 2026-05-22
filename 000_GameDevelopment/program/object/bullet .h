#pragma once
#include "CharacterBase.h" //’e‚ÌƒNƒ‰ƒX


class Bullet : public CharacterBase {
public:

	float m_life_timer; //’e‚ÌÁ‚¦‚é‚Ü‚Å‚ÌŠÔ

	void init() override; //‰Šú‰»
	void update(float delta_time, float time_scale) override; //XV
	void render(Shared<dxe::Camera> cam) override; //•`‰æ

	void applySwingBy(tnl::Vector3 planet_pos) override; 



};