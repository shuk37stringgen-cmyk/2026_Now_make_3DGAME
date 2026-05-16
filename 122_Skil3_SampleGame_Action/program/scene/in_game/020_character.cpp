#include "020_character.h"


Character::Character() {
	setMobilityState(eMobilityState::Floating);
	onSelfIntersectState(fIntersectState::Character);
	onOtherIntersectState(fIntersectState::Block);
}

void Character::onGrounded() {
	setGravityVelocity(0.0f);
}
void Character::toFreeFall() {
	setGravityVelocity(0.98f);
}

//--------------------------------------------------------------------------------------------------------------------------
// Character::update
//--------------------------------------------------------------------------------------------------------------------------
void Character::update() {
	Unit2D::update();

	// シーケンス機能の更新処理
	state_flow_->update(dxe::GetDeltaTime());

	// move_vel_.x の値が 0 の近似でなければ
	// 横方向への移動量で左右の姿勢を更新
	if (!tnl::IsAlmostEqualRelative(getMoveVelocityX(), 0)) {
		setPosture((getMoveVelocityX() >= 0) ? ePosture::Right : ePosture::Left);
	}
	// 左右の姿勢変数でスプライトの描画反転の設定を行う
	if (ePosture::Right == getPosture()) {
		if (main_sprite_->isImageReverseX()) main_sprite_->setImageReverse(dxe::Sprite::fImageReverse::None);
	}
	if (ePosture::Left == getPosture()) {
		if (!main_sprite_->isImageReverseX()) main_sprite_->setImageReverse(dxe::Sprite::fImageReverse::X);
	}
	// スプライトのアニメーション更新処理
	main_sprite_->updateAnimation();

	// キャラクタとしての座標更新
	position_.x += getMoveVelocityX();
	position_.y += getMoveVelocityY();

}


//--------------------------------------------------------------------------------------------------------------------------
// Character::draw
//--------------------------------------------------------------------------------------------------------------------------
void Character::draw(const Shared<dxe::Camera>& camera) {

	tnl::Vector2f compute_position = dxe::ComputeRectPositionByOrigin( position_, main_sprite_->getSize(), main_sprite_->getLocation() );

	// スプライトの座標更新
	// キャラクタの座標と同じ座標をセット
	main_sprite_->setPosition(compute_position);

	// スプライトの描画
	main_sprite_->draw(camera);

	drawBoundingBox(camera, dxe::Colors::MediumVioletRed);
}
