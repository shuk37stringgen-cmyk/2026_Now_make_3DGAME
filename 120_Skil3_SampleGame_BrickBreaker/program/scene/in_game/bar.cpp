#include "bar.h"


Bar::Bar() {
	setPosition( { DXE_WINDOW_WIDTH_HALF, 650.0f } ) ; // 横中央、Y位置650に配置（画面下部）

}

//--------------------------------------------------------------------------------------------------------------------------
// Bar::update
// バーの移動処理。キーボードのA/Dキーで左右に移動し、画面外への移動を制限。
//--------------------------------------------------------------------------------------------------------------------------
void Bar::update() {

	tnl::Vector2f position = getPosition();

	// 左キー[A]で左へ、右キー[D]で右へ移動（1フレームあたり5ピクセル）
	if (tnl::Input::IsKeyDown(eKeys::KB_A)) position.x -= 5.0f;
	if (tnl::Input::IsKeyDown(eKeys::KB_D)) position.x += 5.0f;

	// 画面端での移動制限（バーが画面外にはみ出さないように）
	float limit_x_max = (DXE_WINDOW_WIDTH_F - (size_.x / 2.0f));
	float limit_x_min = size_.x / 2.0f;

	if (position.x > limit_x_max) position.x = limit_x_max;
	if (position.x < limit_x_min) position.x = limit_x_min;

	setPosition( position );
}

//--------------------------------------------------------------------------------------------------------------------------
// Bar::draw
// バーの描画処理。現在の位置に四角形を描画する。
//--------------------------------------------------------------------------------------------------------------------------
void Bar::draw(const Shared<dxe::Camera>& camera) {
	DrawRotaGraphF(getPosition().x, getPosition().y, 1.0f, 0.0f, image_handle_, true);
}
