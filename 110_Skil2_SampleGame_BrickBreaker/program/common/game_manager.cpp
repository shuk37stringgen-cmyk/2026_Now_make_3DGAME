#include <dxe.h>
#include "game_manager.h"
#include "../scene/scene.h"
#include "../scene/title/scene_title.h"
#include "../scene/in_game/scene_in_game.h"
#include "../scene/result/scene_result.h"
#include "../../ResourceConstantHedder.h"

//-----------------------------------------------------------------------------------------------------------------------------
/// ゲームマネージャの唯一のインスタンスを取得する（シングルトン）
GameManager& GameManager::GetInstance() {
	static GameManager instatnce;

	// 初回アクセス時に遅延初期化
	if (!instatnce.is_initalize_) {
		instatnce.lazyInitialize();
	}
	return instatnce;
}

//-----------------------------------------------------------------------------------------------------------------------------
/// 遅延初期化処理（初回のみ呼ばれる）
void GameManager::lazyInitialize() {
	is_initalize_ = true;

	// フェード用の黒画像を読み込み
	image_hdl_fade_ = LoadGraph(FILE_PATH_PNG_BLACK1);

	// 最初のシーンへ遷移
	changeScene();
}

//-----------------------------------------------------------------------------------------------------------------------------
/// メインの更新処理（毎フレーム呼ばれる）
void GameManager::update() {
	// 現在のシーンがあればその更新・描画処理を実行
	if (p_current_scene_) {
		p_current_scene_->update();
		p_current_scene_->deleteNotAliveObject();
		p_current_scene_->draw();
	}

	// トランジション状態がなければ早期リターン
	if (eTransitionState::None == e_transition_state_) return;

	// 経過時間を加算
	transition_time_count_ += dxe::GetDeltaTime();

	// フェードイン処理
	if (eTransitionState::FadeIn == e_transition_state_) {
		transition_fade_alpha_ = 1.0f - (transition_time_count_ / TRANSITION_TIME_LIMIT);

		if (transition_fade_alpha_ < 0) {
			// フェードイン終了
			transition_time_count_ = 0.0f;
			e_transition_state_ = eTransitionState::None;
		}

		// フェードアウト処理
	}
	else if (eTransitionState::FadeOut == e_transition_state_) {
		transition_fade_alpha_ = (transition_time_count_ / TRANSITION_TIME_LIMIT);

		if (transition_fade_alpha_ > 1.0f) {
			// フェードアウト完了後、次のシーンへ遷移
			transition_time_count_ = 0.0f;
			e_transition_state_ = eTransitionState::FadeIn;
			changeScene();
		}
	}

	// アルファ値を [0, 1] にクランプ
	transition_fade_alpha_ = std::clamp<float>(transition_fade_alpha_, 0, 1.0f);

	// 画面全体にフェード画像を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(transition_fade_alpha_ * 255.0f));
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, image_hdl_fade_, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

//-----------------------------------------------------------------------------------------------------------------------------
/// ゲーム終了時の破棄処理（現在のシーンを破棄）
void GameManager::destroy() {
	TNL_SAFE_DELETE(p_current_scene_);
}

//-----------------------------------------------------------------------------------------------------------------------------
/// 次のシーンを予約し、フェードアウトを開始
void GameManager::reserveScene(eScene reserve_scene) {
	e_reserve_scene_ = reserve_scene;
	e_transition_state_ = eTransitionState::FadeOut;
}

//-----------------------------------------------------------------------------------------------------------------------------
/// 現在のシーンを破棄し、予約されたシーンに切り替える
void GameManager::changeScene() {
	TNL_SAFE_DELETE(p_current_scene_);

	// 予約されたシーンに応じてインスタンス生成
	switch (e_reserve_scene_) {
	case eScene::Title:
		p_current_scene_ = new SceneTitle();
		break;
	case eScene::InGame:
		p_current_scene_ = new SceneInGame();
		break;
	case eScene::Result:
		p_current_scene_ = new SceneResult();
		break;
	}

	if (!p_current_scene_) return;

	// 新しいシーンの初期化を実行
	p_current_scene_->lazyInitialize();
}
