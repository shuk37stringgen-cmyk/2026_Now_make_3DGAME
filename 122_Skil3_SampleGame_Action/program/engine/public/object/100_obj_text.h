#pragma once
#include "030_obj_drawable.h"

namespace eng {

	// テキスト表示用のゲームオブジェクトクラス
	// 文字列・フォントサイズ・色・位置・エフェクトなどを持ち、画面に情報を描画する
	class ObjText final : public ObjDrawable {
	public:

		// テキストに適用可能なエフェクトの種類
		enum class eEffectType {
			None
			, Flashing    // 点滅（時間経過によって描画ON/OFFを切り替える）
			, Animation
		};

		ObjText(const Shared<dxe::FontTextResouce>& resource);
		~ObjText() = default;

		// テキストの更新処理（点滅エフェクトなどに使用）
		void update() override;

		// テキストの描画処理
		void draw(const Shared<dxe::Camera>& camera) override;

		// 表示効果の種類（例：点滅）
		TNL_PROPERTY(eEffectType, EffectType, e_effect_type_);

		// テキストカラー（ARGB形式など、DxLibの色指定を想定）
		void setColor( int32_t color );
		void setEdgeColor( int32_t color );
		// 表示位置の基準（左上・中央など、DxLibのeRectOriginを使用）
		void setLocation( dxe::eRectOrigin location );
		void setString( const std::string& str );
		void setScale( const tnl::Vector2f& scale );

		int32_t getColor();
		int32_t getEdgeColor();
		dxe::eRectOrigin getLocation();
		const std::string& getString();
		const tnl::Vector2f& getScale();

		void playAnimation();
		void pauseAnimation();
		void restartAnimation();
		void finishAnimation();

		void addAnimTimeScale(float add_scale);
		void setAnimTimeScale(float time_scale);
		void setAnimWaitTime(float wait_time);
		tnl::SeekUnit::eCondition getAnimCondition();
		void setAnimUpdateCallback(const std::function<void()>& callback);

	private:
		Shared<dxe::FontText> text_;

		// 適用中のエフェクト種別
		eEffectType e_effect_type_ = eEffectType::None;

		// エフェクト用の内部カウンタ（秒単位、点滅などのタイミング制御に使用）
		float time_count_ = 0;
	};

}