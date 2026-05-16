#pragma once
#include "030_obj_drawable.h"

namespace eng {

	// 設置するだけの景観オブジェクト( 背景や賑やかしの汎用オブジェクト )
	class ObjScenery final : public ObjDrawable {
	public:

		ObjScenery() = default;
		ObjScenery(const Shared<dxe::SpriteResouce>& sprite_resouce);

		~ObjScenery() = default;

		// 更新処理
		void update() override;

		// 描画処理
		void draw(const Shared<dxe::Camera>& camera) override;

		const Shared<dxe::Sprite>& getSprite() ;

	protected:

		Shared<dxe::Sprite> sprite_ = nullptr;

	};

}