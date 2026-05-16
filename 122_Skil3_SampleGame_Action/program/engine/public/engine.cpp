#include <dxe.h>
#include "engine.h"
#include "scene.h"
#include "../../../ResourceConstantHedder.h"

namespace eng {

	//-----------------------------------------------------------------------------------------------------------------------------
	Engine& Engine::GetInstance() {
		static Engine instatnce;

		// 初回アクセス時に遅延初期化
		if (!instatnce.is_initalize_) {
			instatnce.lazyInitialize();
		}
		return instatnce;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	/// 遅延初期化処理（初回のみ呼ばれる）
	void Engine::lazyInitialize() {
		is_initalize_ = true;

		// フェード用の黒画像を読み込み
		image_hdl_fade_ = LoadGraph(FILE_PATH_PNG_BLACK1);
	}


	void Engine::setFirstScene(const Shared<Scene>& first_scene) {
		if (current_scene_) return;
		current_scene_ = first_scene;
		current_scene_->lazyInitialize();
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	/// メインの更新処理（毎フレーム呼ばれる）
	void Engine::update() {
		// 現在のシーンがあればその更新・描画処理を実行
		if (current_scene_) {
			current_scene_->update();
			current_scene_->deleteNotAliveObject();
			current_scene_->draw();
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
	void Engine::destroy() {
		current_scene_ = nullptr;
		reserve_scene_ = nullptr;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	/// 次のシーンを予約し、フェードアウトを開始
	void Engine::reserveScene(const Shared<Scene>& next_scene) {
		reserve_scene_ = next_scene;
		e_transition_state_ = eTransitionState::FadeOut;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	/// 現在のシーンを破棄し、予約されたシーンに切り替える
	void Engine::changeScene() {

		current_scene_ = reserve_scene_;

		if (!current_scene_) return;

		// 新しいシーンの初期化を実行
		current_scene_->lazyInitialize();

	}


	//-----------------------------------------------------------------------------------------------------------------------------
	Shared<dxe::ResourceHandle> Engine::loadGraphCached(const std::string& file_path) {
		auto it = resource_chash_.find(file_path);
		if (it != resource_chash_.end()) {
			return std::dynamic_pointer_cast<dxe::ResourceHandle>( it->second );
		}
		Shared<dxe::ResourceHandle> handle = dxe::SpriteResouce::LoadGraph(file_path) ;
		handle->setReleaseFunction([](dxe::ResourceHandle* resource) {
			DeleteGraph(resource->getDxlibHandle());
		});
		resource_chash_.insert(std::make_pair(file_path, handle));
		return handle ;
	}

	//-----------------------------------------------------------------------------------------------------------------------------
	Shared<dxe::ResourceHandleArray> Engine::loadDivGraphCached
	(const std::string& file_path
		, int32_t all_num
		, int32_t x_num
		, int32_t y_num
		, int32_t x_size
		, int32_t y_size) {

		auto it = resource_chash_.find(file_path);
		if (it != resource_chash_.end()) {
			return std::dynamic_pointer_cast<dxe::ResourceHandleArray>(it->second);
		}
		Shared<dxe::ResourceHandleArray> handle_array = dxe::SpriteResouce::LoadDivGraph(file_path, all_num, x_num, y_num, x_size, y_size);
		handle_array->setReleaseFunction([](dxe::ResourceHandleArray* resource) {
			for (auto rh : resource->handles_) {
				DeleteGraph(rh->getDxlibHandle());
			}
		});
		resource_chash_.insert(std::make_pair(file_path, handle_array));
		return handle_array;
	}
	Shared<dxe::ResourceHandleArray> Engine::loadDivGraphCached(const dxe::SpriteDivGraphDesc& desc) {
		return loadDivGraphCached(desc.image_file_path_, desc.all_frame_num_, desc.frame_num_.x, desc.frame_num_.y, desc.size_.x, desc.size_.y);
	}

}
