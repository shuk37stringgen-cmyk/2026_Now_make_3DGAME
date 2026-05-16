#if 0

//---------------------------------------------------------------------------------------------------------------
//
//
// ImGui 利用サンプル
// 
// ※ 各種ウィジェットの詳しい使用法はネットや AI で調べてください
//
//---------------------------------------------------------------------------------------------------------------


#include <time.h>
#include <string>
#include <dxe.h>
#include "../ResourceConstantHedder.h"
#include "gm_main.h"

int input_param = 0;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	/* DxLib_Init() はシステム側で行われているので必要ありません */
	srand(time(0));
}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	// ディスプレイ上のゲームウィンドウ座標を取得
	tnl::Vector2i winpos;
	GetWindowPosition(&winpos.x, &winpos.y);


	// ImGui の使用開始
	dxe::ImGuiNewFrame();


	// ImGuiは ウインドウ単位で Begin()  End() で囲います
	ImGui::SetNextWindowSize(ImVec2(200, 300));
	ImGui::SetNextWindowPos(ImVec2(winpos.x + 100, winpos.y + 50));
	ImGui::Begin("window1");

	ImGui::Text("text message");
	ImGui::InputInt("label", &input_param);

	ImGui::End();


	// ImGuiは ウインドウ単位で Begin()  End() で囲います
	ImGui::SetNextWindowSize(ImVec2(200, 300));
	ImGui::SetNextWindowPos(ImVec2(winpos.x + 300, winpos.y + 50));
	ImGui::Begin("window2");

	if (ImGui::Button("label")) {
		tnl::DebugTrace("on click button \n");
	}

	ImGui::End();


	// ImGui の最終的な描画処理
	dxe::ImGuiRender();


	dxe::DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10 });
}


//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	/* DxLib_End() はシステム側で終了処理が行われるので必要ありません */
}


#endif