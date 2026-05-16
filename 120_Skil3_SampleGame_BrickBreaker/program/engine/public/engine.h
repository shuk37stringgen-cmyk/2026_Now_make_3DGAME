#pragma once
#include <dxe.h>

namespace eng {

	class Scene;

	/// ゲーム全体の状態管理、シーン遷移、フェード管理などを行うシングルトンクラス
	class Engine {
	public:

		/// シーン遷移の状態（フェード管理）
		enum class eTransitionState {
			None,      /// トランジションなし
			FadeOut,   /// フェードアウト中（次のシーンへ切り替え準備）
			FadeIn     /// フェードイン中（新しいシーンへ切り替え後）
		};

		/// シングルトンのインスタンス取得
		static Engine& GetInstance();

		void setFirstScene(const Shared<Scene>& first_scene);

		/// 次に遷移するシーンを予約（即時切り替えではなくフェードを挟む）
		void reserveScene(const Shared<Scene>& next_scene);

		/// 現在実行中のシーンを取得
		const Shared<Scene>& getCurrentScene() { return current_scene_; }

		/// 現在のトランジション状態を取得
		eTransitionState getTransitionState() const { return e_transition_state_; }

		/// 画像ロード
		/// arg1... ファイルパス
		/// ret.... dxe リソースハンドル
		/// tips...多重ロード防止措置付き
		Shared<dxe::ResourceHandle> loadGraphCached(const std::string& file_path);

		/// 画像分割ロード
		/// arg1... ファイルパス
		/// arg2... 分割フレームの総数
		/// arg3... 横フレーム数
		/// arg4... 縦フレーム数
		/// arg5... １フレームあたりの横幅
		/// arg5... １フレームあたりの縦幅
		/// ret.... dxe リソース配列型ハンドル
		Shared<dxe::ResourceHandleArray> loadDivGraphCached
			( const std::string& file_path
			, int32_t frame_num
			, int32_t x_num
			, int32_t y_num
			, int32_t x_size
			, int32_t y_size );

		/// 画像分割ロード
		/// arg1... スプライト分割情報 ( csv 等からの SpriteDivGraphDesc 作成を想定 )
		/// ret.... dxe リソース配列型ハンドル
		Shared<dxe::ResourceHandleArray> loadDivGraphCached(const dxe::SpriteDivGraphDesc& desc);

		/// 毎フレーム呼ばれる更新処理（シーン更新とトランジション制御）
		void update();

		/// シーン解放など終了処理
		void destroy();

	private:

		/// トランジションにかける時間（秒）
		const float TRANSITION_TIME_LIMIT = 0.5f;

		/// 初期化済みかどうかのフラグ
		bool is_initalize_ = false;

		/// トランジションの状態（初期状態はフェードイン中）
		eTransitionState e_transition_state_ = eTransitionState::FadeIn;

		/// フェード用の画像ハンドル（黒画像など）
		int image_hdl_fade_ = 0;

		/// トランジションの経過時間
		float transition_time_count_ = 0;

		/// フェードのアルファ値（0.0?1.0）
		float transition_fade_alpha_ = (eTransitionState::FadeIn == e_transition_state_) ? 1.0f : 0.0f;

		/// 予約された次のシーン
		Shared<Scene> reserve_scene_ = nullptr;

		/// 現在実行中のシーン
		Shared<Scene> current_scene_ = nullptr;

		/// リソース管理マップ
		std::unordered_map<std::string, Shared<dxe::IResourceUnit>> resource_chash_;

		/// 遅延初期化（初回アクセス時のみ呼ばれる）
		void lazyInitialize();

		/// 予約されたシーンに実際に切り替える処理
		void changeScene();

		/// コンストラクタはプライベート（シングルトンのため）
		Engine() = default;

		/// コピー禁止
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
	};

}
