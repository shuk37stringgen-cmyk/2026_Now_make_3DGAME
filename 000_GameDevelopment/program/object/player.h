#pragma once
#include <memory>
#include "CharacterBase.h" //基底クラスから継承
#include "planet.h" //スイングバイのために星のクラスを参照

//---------自機はフライトモード、スイングバイモード、ブーストモードの3つの状態を持つ---------
/*
　基本は空を飛ぶモードがある
　星の重力を利用して加速するスイングバイモードがある
 　
  　ブーストモードがある（スイングバイで溜まったエネルギーを消費して一時的に加速する）

   スイングバイは溜めたエネルギーによってエネルギーと周りの時間がスローになる（スローモーション）ようにする

   星からはそれぞれバフを受けられるようにする
   それぞれ星に対するスイングバイできた経過時間によって、バフのレベルが上がるようにする
   1,攻撃力アップ
   2,防御力アップ
   3,HP回復
   4,弾数アップ
   5,デバフ弾
   6,特殊弾


   攻撃はマウス左クリックで行う

*/

class Player: public CharacterBase {
private:
    float m_hanten_timer;
    bool m_is_hanten;


public:

	// 状態管理
    PlayerState state = PlayerState::FLIGHT;
    float energy;

    // 操作用変数
	float m_senkai;            //旋回はそのまま左右の回転角度として使う
    float m_unazuki;         //うなずきは上下の角度
	float m_katamuki;      // 傾きは機体の動きに合わせて自動で変化させる（左右の傾き）

	//スイングバイ関係の変数等
    float m_swingby_angle;
	float m_hosi_kyori; // 星との距離
    std::shared_ptr<Planet> m_target_planet;
	float m_swingby_cooltime; 

	//-----必要関数-----
    void init() override;
    void update(float delta_time, float time_scale) override;
    void render(Shared<dxe::Camera> cam) override;
    // スイングバイ用の加速処理(星の軌道に乗った時の加速処理をする)
    void applySwingBy(tnl::Vector3 planet_pos) override ;
    void releaseSwingBy();
};