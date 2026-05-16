#pragma once
#include "010_object.h"

namespace eng {

	class ObjMover : public Object {
	public:

		ObjMover() = default;
		~ObjMover() = default;

		// オブジェクトの座標
		TNL_CALC_PROPERTY(tnl::Vector2f, Position, position_);

		TNL_PROPERTY(tnl::Vector2f, BeforePosition, before_position_);

	protected:

		// オブジェクトの座標（左上または中心座標など使用側に依存）
		tnl::Vector2f position_ = { 0, 0 };
		tnl::Vector2f before_position_ = { 0, 0 };


	};

}
