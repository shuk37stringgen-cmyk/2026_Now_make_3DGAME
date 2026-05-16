#include "030_field_object.h"
#include "../../engine/public/engine.h"

FieldObject::FieldObject(const FieldObjectDesc& desc) {
	onSelfIntersectState(fIntersectState::FieldObject);

	type_ = static_cast<eType>(desc.type_);
	eng::Engine& engine = eng::Engine::GetInstance();
	auto rhandle = engine.loadGraphCached(desc.sprite_descs_[0].image_file_path_);
	Shared<dxe::SpriteResouce> resouce = dxe::SpriteResouce::Create(rhandle);
	sprite_ = dxe::Sprite::Create(resouce);
	setMobilityState(eMobilityState::Flying);
	setBoundingBox({ desc.bounding_box_.x, desc.bounding_box_.y });
}

void FieldObject::update() {
	Unit2D::update();
}

void FieldObject::draw(const Shared<dxe::Camera>& camera) {
	sprite_->setPosition(getPosition());
	sprite_->draw(camera);
	drawBoundingBox(camera, dxe::Colors::MediumVioletRed);
}
