#pragma once
#include <dxe.h>
#include "020_character.h"

//--------------------------------------------------------------------------------------------------------------------------
// Player クラス
//--------------------------------------------------------------------------------------------------------------------------
class Player : public Character {
public:

	Player() ;
	~Player() = default;

	TNL_PROPERTY(bool, EnableInput, enable_input_);

	void onGrounded() override ;
	void onHeadBump() override ;
	void toFreeFall() override ;
	void toDamage() override ;
	void toJump();

private:

	TNL_COROUTINE(seqDamage);

	// 待機シーケンス
	void seqIdle(void);
	// 歩きシーケンス
	void seqWalk(void);
	// 走りシーケンス
	void seqRun(void);
	// ジャンプシーケンス
	void seqJump(void);
	// 自由落下シーケンス
	void seqFreeFall(void);
	// ダメージシーケンス
	void seqDamage(void);


	bool isInputLeft();
	bool isInputRight();
	bool isInputRun();
	bool isInputJump();


	void floatingHorizontalMovement();

	// 入力オブジェクト
	bool enable_input_ = false ;
	Shared<dxe::Input> input_kb_;
	Shared<dxe::Input> input_pad_;

	// 複数アニメーションの切り替え用
	// アニメーションを作成して各変数に制御インデックスを保存して
	// どのアニメーションを再生するかなどを制御 ( ハンドルのようなもの )
	int32_t anim_idx_idle_ = 0;
	int32_t anim_idx_walk_ = 0;
	int32_t anim_idx_run_ = 0;
	int32_t anim_idx_attack_ = 0;
	int32_t anim_idx_jump_ = 0;
	int32_t anim_idx_surprise_ = 0;

	// 移動制御用変数
	float move_vel_walk_x_ = 2.0f;
	float move_vel_run_x_ = 5.0f;
	float move_vel_jump_x_ = 1.0f;
	float move_vel_jump_y_ = -20.0f;

};
