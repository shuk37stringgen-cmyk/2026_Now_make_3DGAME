#pragma once
#include "020_obj_mover.h"

namespace eng {

	class ObjDrawable : public ObjMover {
	public:

		ObjDrawable() = default;
		~ObjDrawable() = default;

		virtual void draw(const Shared<dxe::Camera>& camera) {}

		// 描画されるかどうかを制御
		TNL_PROPERTY(bool, Visible, is_visible_);

		// 描画処理の優先度（大きい方が先に描画される）
		TNL_PROPERTY(int, DrawPriority, draw_priority_);

	private:

		// 描画フラグ（false で draw() がスキップされる）
		bool is_visible_ = true;

		int draw_priority_ = 0;

	};

}