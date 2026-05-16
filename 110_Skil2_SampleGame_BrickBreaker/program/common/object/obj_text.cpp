#include "obj_text.h"


void ObjText::update() {

	// ‰‰o‚È‚µ‚È‚ç‚È‚É‚à‚µ‚È‚¢
	if (e_effect_type_ == eEffectType::None) return;

	if (e_effect_type_ == eEffectType::Flashing) {

		// ŽžŠÔŒo‰ß‚ð‰ÁŽZiƒtƒŒ[ƒ€ŽžŠÔ‚ÉŠî‚Ã‚¢‚Äj
		time_count_ += dxe::GetDeltaTime();

		// 0.5•b‚²‚Æ‚É•`‰æƒtƒ‰ƒO‚ð”½“]
		if (time_count_ > 0.5f) {
			time_count_ = 0;
			setVisible( !getVisible() ) ;
		}
	}
}

void ObjText::draw() {
	SetFontSize(font_size_);
	dxe::DrawString(getPosition(), color_, e_location_, draw_word_.c_str());
}
