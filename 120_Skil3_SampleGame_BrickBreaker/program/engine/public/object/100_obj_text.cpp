#include "100_obj_text.h"

namespace eng {

	ObjText::ObjText(const Shared<dxe::FontTextResouce>& resource) {
		text_ = dxe::FontText::CreateAnimation(resource);
		setVisible(true);
	}

	void ObjText::update() {

		if (e_effect_type_ == eEffectType::Flashing) {

			// ŽžŠÔŒo‰ß‚ð‰ÁŽZiƒtƒŒ[ƒ€ŽžŠÔ‚ÉŠî‚Ã‚¢‚Äj
			time_count_ += dxe::GetDeltaTime();

			// 0.5•b‚²‚Æ‚É•`‰æƒtƒ‰ƒO‚ð”½“]
			if (time_count_ > 0.5f) {
				time_count_ = 0;
				setVisible(!getVisible());
			}
		}

		if (e_effect_type_ != eEffectType::Animation) {
			text_->restartAnimation();
			text_->finishAnimation();
		}

		text_->updateAnimation() ;
	}

	void ObjText::draw(const Shared<dxe::Camera>& camera) {
		text_->setPosition(position_);
		text_->draw();
	}

	void ObjText::setColor(int32_t color) { text_->setColor(color); }
	void ObjText::setEdgeColor(int32_t color) { text_->setEdgeColor(color); }
	void ObjText::setLocation(dxe::eRectOrigin location) { text_->setLocation(location); }
	void ObjText::setString(const std::string& str) { text_->setString(str); }
	void ObjText::setScale(const tnl::Vector2f& scale) { text_->setScale(scale); }

	int32_t ObjText::getColor() { return text_->getColor(); }
	int32_t ObjText::getEdgeColor() { return text_->getEdgeColor(); }
	dxe::eRectOrigin ObjText::getLocation() { return text_->getLocation(); }
	const std::string& ObjText::getString() { return text_->getString(); }
	const tnl::Vector2f& ObjText::getScale() { return text_->getScale(); }


	void ObjText::playAnimation() { text_->playAnimation(); }
	void ObjText::pauseAnimation() { text_->pauseAnimation(); }
	void ObjText::restartAnimation() { text_->restartAnimation(); }
	void ObjText::finishAnimation() { text_->finishAnimation(); }

	void ObjText::addAnimTimeScale(float add_scale) { text_->addAnimTimeScale(add_scale); }
	void ObjText::setAnimTimeScale(float time_scale) { text_->setAnimTimeScale( time_scale ); }
	void ObjText::setAnimWaitTime(float wait_time) { text_->setAnimWaitTime(wait_time); }
	tnl::SeekUnit::eCondition ObjText::getAnimCondition() { return text_->getAnimCondition(); }
	void ObjText::setAnimUpdateCallback(const std::function<void()>& callback) {
		text_->setAnimUpdateCallback(callback);
	}

}
