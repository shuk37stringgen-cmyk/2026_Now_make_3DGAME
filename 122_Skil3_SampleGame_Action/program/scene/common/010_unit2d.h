#pragma once
#include <dxe.h>
#include "../../engine/public/object/030_obj_drawable.h"

class IUnit2DState {
public :
	// ç∂âEÇÃépê®íËêî
	enum class ePosture {
		Right,		// âEå¸Ç´
		Left		// ç∂å¸Ç´
	};

};

class Unit2DDesc : public IUnit2DState {
public:
	Unit2DDesc() = default;
	virtual ~Unit2DDesc() = default;
	ePosture posture_ = ePosture::Right;
	float bounding_sphere_ = 0;
	float lim_move_vel_up_ = -20;
	float lim_move_vel_down_ = 10;
	float lim_move_vel_horiz_ = 5.0f;
	float gravity_vel_ = 0.98f;
	tnl::Vector2f bounding_box_;
	tnl::Vector2f move_vel_;
	std::vector<dxe::SpriteDesc> sprite_descs_;
};


class Unit2D : public eng::ObjDrawable, public IUnit2DState {
public :

	Unit2D() = default ;
	~Unit2D() = default ;

	const float GRAVITY_VELOCITY = 0.98f;

	void setReversePosture() { posture_ = (posture_ == ePosture::Right) ? ePosture::Left : ePosture::Right; }
	TNL_PROPERTY(ePosture, Posture, posture_);
	TNL_PROPERTY(float, BoundingSphere, bounding_sphere_);
	TNL_PROPERTY(tnl::Vector2f, BoundingBox, bounding_box_);

	TNL_PROPERTY(float, LimMoveVelUp, lim_move_vel_up_);
	TNL_PROPERTY(float, LimMoveVelDown, lim_move_vel_down_);
	TNL_PROPERTY(float, LimMoveVelHoriz, lim_move_vel_horiz_);

	TNL_SET_SELF_PROPERTY(float, MoveVelocityX, move_vel_.x);
	TNL_SET_SELF_PROPERTY(float, MoveVelocityY, move_vel_.y);
	TNL_SET_SELF_PROPERTY(tnl::Vector2f, MoveVelocity, move_vel_);
	void addMoveVelocityX(float value);
	void addMoveVelocityY(float value);
	void addMoveVelocity(const tnl::Vector2f& value);


	TNL_CALC_PROPERTY(float, GravityVelocity, gravity_vel_);

	tnl::Vector2f getPositionWithFallVelocity() { return { position_.x, position_.y + GRAVITY_VELOCITY }; }

	void drawBoundingCircle(const Shared<dxe::Camera>& camera, int32_t color);
	void drawBoundingBox(const Shared<dxe::Camera>& camera, int32_t color);

	bool isInsideScreen(const Shared<dxe::Camera>& camera);

	void update() override ;

private :

	// ç∂âEÇÃï`âÊîΩì]êßå‰óp
	ePosture posture_ = ePosture::Right;
	float bounding_sphere_ = 0;
	tnl::Vector2f move_vel_;
	float lim_move_vel_up_ = -20;
	float lim_move_vel_down_ = 10;
	float lim_move_vel_horiz_ = 5.0f;
	tnl::Vector2f bounding_box_;
	float gravity_vel_ = GRAVITY_VELOCITY;

};
