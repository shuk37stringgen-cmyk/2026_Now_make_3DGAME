#include "110_obj_scenery.h"


namespace eng{

	ObjScenery::ObjScenery(const Shared<dxe::SpriteResouce>& sprite_resouce) {
		if (sprite_resouce->isAnimation()) {
			sprite_ = dxe::Sprite::CreateAnimation(sprite_resouce);
		}
		else {
			sprite_ = dxe::Sprite::Create(sprite_resouce);
		}
	}

	const Shared<dxe::Sprite>& ObjScenery::getSprite() { return sprite_; }

	// XVˆ—
	void ObjScenery::update() {
		sprite_->updateAnimation();
	}

	// •`‰æˆ—
	void ObjScenery::draw(const Shared<dxe::Camera>& camera) {
		sprite_->draw(camera);
	}

}