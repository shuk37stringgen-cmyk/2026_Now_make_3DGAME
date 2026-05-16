#include <dxe.h>
#include "gm_main.h"
#include "scene_result.h"

// リザルト画面の点滅表示用スイッチ
bool g_result_time_switch = true;

// リザルト画面での時間カウンタ（点滅切り替えのためのタイマー）
float g_result_time_count = 0;

//--------------------------------------------------------------------------------------------------------------------------
// リザルトシーンの初期化処理
// 点滅切り替えフラグやタイマーをリセットする
//--------------------------------------------------------------------------------------------------------------------------
void sceneResultInitialize() {
	g_result_time_count = 0;
	g_result_time_switch = true;
}

//--------------------------------------------------------------------------------------------------------------------------
// リザルトシーンの更新および描画処理
// 入力によるシーン遷移、点滅表示の制御、文字の描画を行う
//--------------------------------------------------------------------------------------------------------------------------
int sceneResultProcess() {

	// 経過時間を加算（毎フレーム）
	g_result_time_count += dxe::GetDeltaTime();

	// 0.5秒ごとに点滅フラグを反転
	if (g_result_time_count > 0.5f) {
		g_result_time_count = 0;
		g_result_time_switch = !g_result_time_switch;
	}

	// スペースキーが押されたらタイトルシーンに戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		return SCENE_TITLE_INIT;
	}

	// 結果シーンのタイトルを表示
	SetFontSize(50);
	dxe::DrawString(
		{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F },
		dxe::Colors::AliceBlue,
		dxe::eRectOrigin::CENTER,
		"Scene Result");

	// 「Press the space key」の点滅表示
	SetFontSize(20);
	if (g_result_time_switch) {
		dxe::DrawString(
			{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F },
			dxe::Colors::AliceBlue,
			dxe::eRectOrigin::CENTER,
			"Press the space key");
	}

	// 現在のシーン（リザルト）を維持
	return SCENE_RESULT;
}