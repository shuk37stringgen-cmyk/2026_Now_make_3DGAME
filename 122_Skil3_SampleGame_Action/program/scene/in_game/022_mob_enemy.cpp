#include <dxe.h>
#include "022_mob_enemy.h"
#include "../../engine/public/engine.h"
#include "../../../ResourceConstantHedder.h"


MobEnemyDesc::MobEnemyDesc(const tnl::CsvCells& csv) {

	type_ = csv[0][1].getInt();
	bounding_box_size_.x = csv[1][1].getFloat();
	bounding_box_size_.y = csv[1][2].getFloat();

	dxe::SpriteAnimationDesc anim_desc;
	anim_desc.image_file_path_ = csv[2][1].getString();
	anim_desc.all_frame_num_ = csv[3][1].getInt();
	anim_desc.frame_num_.x = csv[4][1].getInt();
	anim_desc.frame_num_.y = csv[5][1].getInt();
	anim_desc.size_.x = csv[6][1].getInt();
	anim_desc.size_.y = csv[6][2].getInt();
	anim_desc.once_playing_time_ = csv[7][1].getFloat();
	anim_desc.play_mode_ = static_cast<tnl::SeekUnit::ePlayMode>(csv[8][1].getInt());
	animations_.emplace_back(anim_desc);

}


MobEnemy::MobEnemy(const MobEnemyDesc& desc) {
	onSelfIntersectState(fIntersectState::MobEnemy);
	onOtherIntersectState(fIntersectState::Player);
	onOtherIntersectState(fIntersectState::Block);

	setBoundingSphere(32.0f);
	setBoundingBox({ 67.0, 60.0f });

	// 行動制御用ステートマシンを作成
	// ※ 使い方は example -> util -> tnl_state_machine.h を参照
	state_flow_ = TNL_STATE_MACHINE_CREATE(&MobEnemy::seqWalk, this);

	// アニメーションを利用するスプライトの生成に必要なリソースの作成
	// ※ リソースを共有して別のスプライトを作成することも可能です
	Shared<dxe::SpriteResouce> resource = dxe::SpriteResouce::CreateAnimation();


	dxe::SpriteDivGraphDesc div_desc = desc.animations_[0];
	div_desc.image_file_path_ = dxe::GetPathFromFileName(div_desc.image_file_path_.c_str());
	Shared<dxe::ResourceHandleArray> handle = eng::Engine::GetInstance().loadDivGraphCached(div_desc);
	anim_idx_ = resource->addAnimation(handle, desc.animations_[0]);


	// スプライトの作成
	// arg1... 作成リソース
	main_sprite_ = dxe::Sprite::CreateAnimation(resource);
	main_sprite_->setPosition({ 0, 0 });

	// 座標の基点を「中央」に
	main_sprite_->setLocation(dxe::eRectOrigin::CENTER_BOTTOM);

}

void MobEnemy::onGrounded() {
	Character::onGrounded();
	setMobilityState(eMobilityState::Grounded);
	setMoveVelocityY(0);
}
void MobEnemy::onHeadBump() {
}
void MobEnemy::onSideBump() {
	setReversePosture();
	setMoveVelocityX(-getMoveVelocityX());
}

void MobEnemy::toFreeFall() {
	Character::toFreeFall();
	state_flow_->change(TNL_STATE_BIND(&MobEnemy::seqFreeFall, this));
}
void MobEnemy::toDamage() {
	state_flow_->change(TNL_STATE_BIND(&MobEnemy::seqDamage, this));
}
void MobEnemy::toIdle() {
	state_flow_->change(TNL_STATE_BIND(&MobEnemy::seqIdle, this));
}

// 待機シーケンス
void MobEnemy::seqIdle(void) {
	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_);
		setMoveVelocityX(0);
	}

}

// 歩きシーケンス
void MobEnemy::seqWalk(void) {
	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		// 該当アニメーション設定
		main_sprite_->changeAnimation(anim_idx_);
		setMoveVelocityX(-move_vel_walk_x_);
	}
}

// 自由落下シーケンス
void MobEnemy::seqFreeFall(void) {
}

void MobEnemy::seqDamage(void) {

	// コルーチンの開始。
	// [ !注意! ] このマクロ引数には必ず動作中の関数名を指定してください
	TNL_CO_BEGIN(seqDamage);

	// シーケンス初期化処理
	if (state_flow_->isStart()) {
		offOtherIntersectState(fIntersectState::Player);
		setMoveVelocityX(0);
		main_sprite_->setScaleXY({ 1.0f, 0.5f });
		main_sprite_->setBlendMode(dxe::Sprite::eBlendMode::Alpha);
	}

	for (int i = 0; i < 10; ++i) {
		TNL_CO_TIME_YIELD_RETURN(0.05f, dxe::GetDeltaTime(), [&]() {
			main_sprite_->setAlpha(0.5f);
		});
		TNL_CO_TIME_YIELD_RETURN(0.05f, dxe::GetDeltaTime(), [&]() {
			main_sprite_->setAlpha(1.0f);
		});
	}

	setAlive(false);

	// コルーチンの終了
	TNL_CO_END();
}
