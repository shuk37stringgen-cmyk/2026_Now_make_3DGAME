#pragma once
#include <dxe.h>
#include "../../common/object/object.h"

//--------------------------------------------------------------------------------------------------------------------------
// Bar クラス
// プレイヤーが操作するバーのクラス。位置、サイズ、描画、更新処理を管理。
//--------------------------------------------------------------------------------------------------------------------------
class ObjBar : public Object {
public:

	ObjBar() ;
	~ObjBar() = default;

	void update() override  ;

	void draw() override ;

	TNL_PROPERTY(tnl::Vector2f, Size, size_);
	TNL_PROPERTY(int, ImageHandle, image_handle_);

private:
	tnl::Vector2f size_ = { 140.0f, 30.0f };
	int image_handle_;

};
