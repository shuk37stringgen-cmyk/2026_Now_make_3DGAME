#pragma once
#include <dxe.h>
#include "../../common/object/object.h"

class ObjBlock : public Object {
public:

	// ブロック配置数とサイズ
	static constexpr int BLOCK_NUM_W = 10;       // 横に10個
	static constexpr int BLOCK_NUM_H = 7;        // 縦に7個
	static constexpr float BLOCK_SIZE_W = 80;   // ブロックの幅
	static constexpr float BLOCK_SIZE_H = 36;    // ブロックの高さ

	ObjBlock();
	~ObjBlock() = default;

	// 更新処理：現在は未使用。将来的な拡張のために定義
	void update() override;

	// 描画処理：ブロックを画面に描画する
	void draw() override;

	TNL_PROPERTY(tnl::Vector2f, Size, size_);
	TNL_PROPERTY(int, ImageHandle, image_handle_);

private:

	// ブロックのサイズ（幅と高さ）
	tnl::Vector2f size_;

	// ブロックの画像ハンドル
	int image_handle_;

};
