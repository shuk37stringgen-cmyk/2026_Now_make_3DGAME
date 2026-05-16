#pragma once
#include <dxe.h>

class Scene;

/// ゲーム全体の状態管理、シーン遷移、フェード管理などを行うシングルトンクラス
class GameManager {
public:

	/// ゲームシーンの種類
	enum class eScene {
		Title,     /// タイトル画面
		InGame,    /// ゲームプレイ中
		Result     /// リザルト画面
	};

	/// シーン遷移の状態（フェード管理）
	enum class eTransitionState {
		None,      /// トランジションなし
		FadeOut,   /// フェードアウト中（次のシーンへ切り替え準備）
		FadeIn     /// フェードイン中（新しいシーンへ切り替え後）
	};

	/// シングルトンのインスタンス取得
	static GameManager& GetInstance();

	/// 次に遷移するシーンを予約（即時切り替えではなくフェードを挟む）
	void reserveScene(eScene next_scene);

	/// 現在のトランジション状態を取得
	eTransitionState getTransitionState() const { return e_transition_state_; }

	/// 毎フレーム呼ばれる更新処理（シーン更新とトランジション制御）
	void update();

	/// シーン解放など終了処理
	void destroy();

private:

	/// トランジションにかける時間（秒）
	const float TRANSITION_TIME_LIMIT = 0.5f;

	/// 初期化済みかどうかのフラグ
	bool is_initalize_ = false;

	/// 予約された次のシーン
	eScene e_reserve_scene_ = eScene::Title;

	/// トランジションの状態（初期状態はフェードイン中）
	eTransitionState e_transition_state_ = eTransitionState::FadeIn;

	/// フェード用の画像ハンドル（黒画像など）
	int image_hdl_fade_ = 0;

	/// トランジションの経過時間
	float transition_time_count_ = 0;

	/// フェードのアルファ値（0.0?1.0）
	float transition_fade_alpha_ = (eTransitionState::FadeIn == e_transition_state_) ? 1.0f : 0.0f;

	/// 次のシーンへのポインタ（切り替え時に使う）
	Scene* p_next_scene_ = nullptr;

	/// 現在実行中のシーン
	Scene* p_current_scene_ = nullptr;

	/// 遅延初期化（初回アクセス時のみ呼ばれる）
	void lazyInitialize();

	/// 予約されたシーンに実際に切り替える処理
	void changeScene();

	/// コンストラクタはプライベート（シングルトンのため）
	GameManager() = default;

	/// コピー禁止
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};