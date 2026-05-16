#include "010_unit2d.h"

void Unit2D::update() {
	setBeforePosition(position_);
	addMoveVelocityY(gravity_vel_);
	// Y é≤à⁄ìÆó Ç…èdóÕâ¡ë¨ìxÇâ¡éZ ( Ç±ÇÍÇ…ÇÊÇËÇ¢Ç∏ÇÍóéâ∫ÇµÇƒÇ≠ÇÈ )
	//if (getMobilityState() == Unit2D::eMobilityState::Floating) {
	//}
}

void Unit2D::drawBoundingCircle(const Shared<dxe::Camera>& camera, int32_t color) {
	tnl::Vector2f position = camera->convertWorldToScreenPosition2D(position_);
	DrawCircle((int)position.x, (int)position.y, bounding_sphere_, color, false);
}

void Unit2D::drawBoundingBox(const Shared<dxe::Camera>& camera, int32_t color) {
	tnl::Vector2f position = camera->convertWorldToScreenPosition2D(position_);
	dxe::DrawBox(position, bounding_box_.x, bounding_box_.y, false, color);
}

bool Unit2D::isInsideScreen(const Shared<dxe::Camera>& camera) {
	tnl::Vector2f position = camera->convertWorldToScreenPosition2D(position_);
	return tnl::IsIntersectRect({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F }, { DXE_WINDOW_WIDTH_F, DXE_WINDOW_HEIGHT_F }, position, bounding_box_);
}


void Unit2D::setMoveVelocityX(const float& value) {
	move_vel_.x = value;
	move_vel_.x = std::clamp(move_vel_.x, -lim_move_vel_horiz_, lim_move_vel_horiz_);
}
void Unit2D::setMoveVelocityY(const float& value) {
	move_vel_.y = value;
	move_vel_.y = std::clamp(move_vel_.y, lim_move_vel_up_, lim_move_vel_down_);
}
void Unit2D::setMoveVelocity(const tnl::Vector2f& value) {
	move_vel_ = value;
	move_vel_.x = std::clamp(move_vel_.x, -lim_move_vel_horiz_, lim_move_vel_horiz_);
	move_vel_.y = std::clamp(move_vel_.y, lim_move_vel_up_, lim_move_vel_down_);
}

void Unit2D::addMoveVelocityX(float value) {
	move_vel_.x += value;
	move_vel_.x = std::clamp(move_vel_.x, -lim_move_vel_horiz_, lim_move_vel_horiz_);
}
void Unit2D::addMoveVelocityY(float value) {
	move_vel_.y += value;
	move_vel_.y = std::clamp(move_vel_.y, lim_move_vel_up_, lim_move_vel_down_);
}

void Unit2D::addMoveVelocity(const tnl::Vector2f& value) {
	move_vel_ += value;
	move_vel_.x = std::clamp(move_vel_.x, -lim_move_vel_horiz_, lim_move_vel_horiz_);
	move_vel_.y = std::clamp(move_vel_.y, lim_move_vel_up_, lim_move_vel_down_);
}