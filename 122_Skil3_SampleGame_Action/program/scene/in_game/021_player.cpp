#include <dxe.h>
#include "021_player.h"
#include "../../../ResourceConstantHedder.h"

Player::Player() {

	onSelfIntersectState(fIntersectState::Player);
	onOtherIntersectState(fIntersectState::Block);
	onOtherIntersectState(fIntersectState::Goal);
	onOtherIntersectState(fIntersectState::MobEnemy);

	setBoundingSphere(32.0f);
	setBoundingBox({ 32.0f, 60.0f });

	// 行動制御用ステートマシンを作成
	// ※ 使い方は example -> util -> tnl_state_machine.h を参照
	state_flow_ = TNL_STATE_MACHINE_CREATE(&Player::seqIdle, this);

	// アニメーションを利用するスプライトの生成に必要なリソースの作成
	// ※ リソースを共有して別のスプライトを作成することも可能です
	Shared<dxe::SpriteResouce> resource = dxe::SpriteResouce::CreateAnimation();

	// 各アニメーション情報を追加してアクセス用ハンドルを作成
	// arg1... スプライトシートのファイルパス
	// arg2... 総コマ数
	// arg3... 横方向のコマ数
	// arg4... 縦方向のコマ数
	// arg5... １コマの横サイズ
	// arg6... １コマの縦サイズ
	// arg7... １回あたりの再生時間
	// arg8... 再生モード ( tnl::SeekUnit::ePlayMode )
	anim_idx_idle_ = resource->addAnimation(FILE_PATH_PNG_C2_ANIM_IDLE, 4, 4, 1, 64, 64, 0.75f, tnl::SeekUnit::ePlayMode::REFLECTION);
	anim_idx_walk_ = resource->addAnimation(FILE_PATH_PNG_C2_ANIM_WALK, 11, 8, 2, 64, 64, 0.75f, tnl::SeekUnit::ePlayMode::REPEAT);
	anim_idx_run_ = resource->addAnimation(FILE_PATH_PNG_C2_ANIM_RUN, 20, 8, 3, 64, 64, 0.75f, tnl::SeekUnit::ePlayMode::REPEAT);
	anim_idx_jump_ = resource->addAnimation(FILE_PATH_PNG_C2_ANIM_JUMP, 3, 3, 1, 64, 64, 0.6f, tnl::SeekUnit::ePlayMode::SINGLE);
	anim_idx_surprise_ = resource->addAnimation(FILE_PATH_PNG_SURPRISE, 1, 1, 1, 64, 64, 1.0f, tnl::SeekUnit::ePlayMode::SINGLE);

	// スプライトの作成
	// arg1... 作成リソース
	main_sprite_ = dxe::Sprite::CreateAnimation(resource);
	main_sprite_->setPosition({ 0, 0 });

	// 座標の基点を「中央」に
	main_sprite_->setLocation(dxe::eRectOrigin::CENTER_BOTTOM);

	// 入力制御オブジェクトの作成
	input_kb_ = dxe::Input::Create(0);
	input_pad_ = dxe::Input::Create(0, dxe::Input::eJoypad::PAD1);


}
void Player::onGrounded() {
	Character::onGrounded();
	setMobilityState(eMobilityState::Grounded);
	setMoveVelocityY(0);
	state_flow_->change(TNL_STATE_BIND(&Player::seqIdle, this));
}

void Player::onHeadBump() {
	setMoveVelocityY(0);
}

void Player::toFreeFall() {
	Character::toFreeFall();
	state_flow_->change(TNL_STATE_BIND(&Player::seqFreeFall, this));
}

void Player::toDamage() {
	setMoveVelocity({ 0, 0 });
	clearOtherIntersectState();
	state_flow_->change(TNL_STATE_BIND(&Player::seqDamage, this));
}
void Player::toJump() {
	state_flow_->change(TNL_STATE_BIND(&Player::seqJump, this));
}


bool Player::isInputLeft() {
	if (!enable_input_) return false;	
	return ( input_kb_->keep( dxe::Input::eButton::KB_A) || input_pad_->keep(dxe::Input::eButton::PAD_LEFT) );
}
bool Player::isInputRight() {
	if (!enable_input_) return false;
	return ( input_kb_->keep(dxe::Input::eButton::KB_D) || input_pad_->keep(dxe::Input::eButton::PAD_RIGHT) );
}
bool Player::isInputRun() {
	if (!enable_input_) return false;
	return ( input_kb_->keep(dxe::Input::eButton::KB_RCONTROL) || input_pad_->keep(dxe::Input::eButton::PAD_A) );
}
bool Player::isInputJump() {
	if (!enable_input_) return false;
	return ( input_kb_->pressed(dxe::Input::eButton::KB_W) || input_pad_->pressed(dxe::Input::eButton::PAD_B) ) ;
}


void Player::floatingHorizontalMovement() {

	float mvx = getMoveVelocityX();
	mvx = tnl::AddAbsClampZero<float>(mvx, -0.1f);
	setMoveVelocityX(mvx);

	// 左右の入力でジャンプ中の X軸 移動量を設定
	if (isInputLeft()) {
		addMoveVelocityX(-move_vel_jump_x_);
	}
	else if (isInputRight()) {
		addMoveVelocityX(move_vel_jump_x_);
	}

}


//-----------------------------------------------------------------------------------------------------------------------------
// 待機シーケンス
void Player::seqIdle() {

	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_idle_);
	}

	// X 方向への移動量を 0 でリセット
	setMoveVelocityX(0);

	// 横移動に対応したキーの入力チェック
	if ( isInputLeft() || isInputRight() ) {
		// 加えて「走る」キーが押されていれば「走る」処理へ
		if ( isInputRun() ) {
			state_flow_->change(TNL_STATE_BIND(&Player::seqRun, this));
		}
		// 移動キーのみの入力なら「歩く」へ
		else {
			state_flow_->change(TNL_STATE_BIND(&Player::seqWalk, this));
		}
	}

	// ジャンプキーが押されていれば優先してジャンプへ
	if ( isInputJump() ) {
		state_flow_->change(TNL_STATE_BIND(&Player::seqJump, this));
	}

	return;
}


//-----------------------------------------------------------------------------------------------------------------------------
// 歩くシーケンス
void Player::seqWalk() {

	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_walk_);
		setLimMoveVelHoriz(move_vel_walk_x_);
	}

	// 入力状態で左右の移動量を設定
	if ( isInputLeft() ) {
		setMoveVelocityX(-move_vel_walk_x_);
	}
	else if ( isInputRight() ) {
		setMoveVelocityX(move_vel_walk_x_);
	}
	// 入力がなければ「待機」へ
	else {
		state_flow_->change(TNL_STATE_BIND(&Player::seqIdle, this));
		return;
	}

	// 歩きの最中にも「走る」へ切り替え
	if ( isInputRun() ) {
		state_flow_->change(TNL_STATE_BIND(&Player::seqRun, this));
	}

	// 優先的にジャンプ処理
	if ( isInputJump() ) {
		state_flow_->change(TNL_STATE_BIND(&Player::seqJump, this));
	}

	return;
}


//-----------------------------------------------------------------------------------------------------------------------------
// 走るシーケンス
void Player::seqRun() {

	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_run_);
		setLimMoveVelHoriz(move_vel_run_x_);
	}
	// 「走る」入力がなければ「待機」へ
	if ( !isInputRun() ) {
		state_flow_->change(TNL_STATE_BIND(&Player::seqIdle, this));
		return;
	}

	// 移動処理
	if ( isInputLeft() ) {
		setMoveVelocityX(-move_vel_run_x_);
	}
	else if ( isInputRight() ) {
		setMoveVelocityX(move_vel_run_x_);
	}
	// 移動処理がなければ「待機」へ
	else {
		state_flow_->change(TNL_STATE_BIND(&Player::seqIdle, this));
		return;
	}

	// 優先的にジャンプ処理
	if ( isInputJump() ) {
		state_flow_->change(TNL_STATE_BIND(&Player::seqJump, this));
	}

	return;
}


//-----------------------------------------------------------------------------------------------------------------------------
// ジャンプシーケンス
void Player::seqJump() {

	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		setMobilityState(eMobilityState::Floating);

		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_jump_);

		// ジャンプ用 初期 Y軸 移動量設定
		setMoveVelocityY(move_vel_jump_y_);
		setGravityVelocity(GRAVITY_VELOCITY);
	}

	// ジャンプ中の加速度によってジャンプアニメーションの
	// 再生フレームを任意のフレームで固定する
	// 移動力の 80% 未満と それ以外で「上昇中」「滞空」「下降中」を設定
	if ((fabs(getMoveVelocityY()) / fabs(move_vel_jump_y_)) > 0.2f) {
		if (getMoveVelocityY() < 0) {
			// 上昇中
			main_sprite_->jumpAnimSeekFrame(0);
		}
		else {
			// 下降中
			main_sprite_->jumpAnimSeekFrame(2);
		}
	}
	else {
		// 滞空
		main_sprite_->jumpAnimSeekFrame(1);
	}

	// 空中にいる間の水平方向入力に対応した処理
	floatingHorizontalMovement();

	return;
}


//-----------------------------------------------------------------------------------------------------------------------------
// 自由落下シーケンス
void Player::seqFreeFall(void) {

	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		setMobilityState(eMobilityState::Floating);

		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_jump_);

		// 滞空
		main_sprite_->jumpAnimSeekFrame(1);

		// ジャンプ用 初期 Y軸 移動量設定
		setMoveVelocityY(0);
	}

	// 空中にいる間の水平方向入力に対応した処理
	floatingHorizontalMovement();

}

//-----------------------------------------------------------------------------------------------------------------------------
// ダメージシーケンス
void Player::seqDamage() {

	// コルーチンの開始。
	// [ !注意! ] このマクロ引数には必ず動作中の関数名を指定してください
	TNL_CO_BEGIN(seqDamage);

	// シーケンス初期化処理
	if (state_flow_->isStart()) {

		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_surprise_);

		setMoveVelocityY(0);
		setMoveVelocityX(0);
		setGravityVelocity(0);
	}

	// 一定時間待機
	TNL_CO_TIME_YIELD_RETURN(0.5f, dxe::GetDeltaTime(), [&]() {
		if (TNL_CO_TIME_YIELD_IS_END()) {
			// ジャンプ用 初期 Y軸 移動量設定
			setMoveVelocityY(move_vel_jump_y_);
			setGravityVelocity(GRAVITY_VELOCITY);
		}
	});


	// コルーチンの終了
	TNL_CO_END();
}