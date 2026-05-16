#include <dxe.h>
#include "gm_main.h"
#include "scene_title.h"

// タイトル画面での点滅表示の切り替えフラグ
bool g_title_time_switch = true;

// タイトル画面での時間カウント（点滅のタイミング管理用）
float g_title_time_count = 0;

//--------------------------------------------------------------------------------------------------------------------------
// タイトル画面の初期化処理
// 点滅タイマーやフラグを初期状態に戻す
//--------------------------------------------------------------------------------------------------------------------------
void sceneTitleInitialize() {
	g_title_time_count = 0;
	g_title_time_switch = true;
}

//--------------------------------------------------------------------------------------------------------------------------
// タイトル画面の更新処理
// 点滅の管理、入力判定、タイトル描画を行う
//--------------------------------------------------------------------------------------------------------------------------
int sceneTitleProcess() {

	// 時間経過を加算（フレーム時間に基づいて）
	g_title_time_count += dxe::GetDeltaTime();

	// 0.5秒ごとに点滅フラグを反転
	if (g_title_time_count > 0.5f) {
		g_title_time_count = 0;
		g_title_time_switch = !g_title_time_switch;
	}

	// スペースキーが押されたらゲームシーンへ遷移
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		return SCENE_IN_GAME_INIT;
	}

	// タイトル文字の描画
	SetFontSize(50);
	dxe::DrawString(
		{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F },
		dxe::Colors::AliceBlue,
		dxe::eRectOrigin::CENTER,
		"BrickBreaker");

	// 「Press the space key」の点滅表示
	SetFontSize(20);
	if (g_title_time_switch) {
		dxe::DrawString(
			{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F },
			dxe::Colors::AliceBlue,
			dxe::eRectOrigin::CENTER,
			"Press the space key");
	}

	// 現在のシーンIDを返す（継続）
	return SCENE_TITLE;
}