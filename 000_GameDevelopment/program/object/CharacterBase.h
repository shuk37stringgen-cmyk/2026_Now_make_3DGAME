#pragma once
#include "..//Common.h"
#include <dxe.h>

//--------------------キャラクターの基底クラス-------------------
  //基本要素のみ入力などはいらない
class CharacterBase {
public:

	//オブジェクトの物理挙動を管理するための変数
	Shared<dxe::Mesh> m_mesh;
	tnl::Vector3 m_position;           // 位置
	tnl::Vector3 m_velocity;          //速度
	tnl::Quaternion m_rotation;  //回転

	//共通のメーターケース
	float m_hp;        //ヒットポイント
	float m_max_hp;    //最大ヒットポイント
	float m_max_speed;    //最高速度
	float m_accel_power;   //加算される加速力
	float m_attack_power; //攻撃力
	float m_friction;     //摩擦
	float m_defense_power;   //防御力

	//共通関数　純粋仮想関数基底クラスで宣言すべき関数
	virtual void init() = 0; //初期化  
	virtual void update(float delta_time, float time_scale) = 0; //更新
	virtual void render(Shared<dxe::Camera> cam)= 0; //描画
	
	virtual void applySwingBy(tnl::Vector3 planet_pos) = 0; //スイングバイ用の加速処理(星の軌道に乗った時の加速処理をする)

};