#pragma once
#include "object.h"

// テキスト表示用のゲームオブジェクトクラス
// 文字列・フォントサイズ・色・位置・エフェクトなどを持ち、画面に情報を描画する
class ObjText : public Object {
public:

	// テキストに適用可能なエフェクトの種類
	enum class eEffectType {
		None,       // なし
		Flashing    // 点滅（時間経過によって描画ON/OFFを切り替える）
	};

	ObjText() = default;
	~ObjText() = default;

	// テキストの更新処理（点滅エフェクトなどに使用）
	void update() override;

	// テキストの描画処理
	void draw() override;

	// 描画する文字列
	TNL_PROPERTY(std::string, String, draw_word_);

	// フォントサイズ
	TNL_PROPERTY(int, FontSize, font_size_);

	// テキストカラー（ARGB形式など、DxLibの色指定を想定）
	TNL_PROPERTY(int, Color, color_);

	// 表示効果の種類（例：点滅）
	TNL_PROPERTY(eEffectType, EffectType, e_effect_type_);

	// 表示位置の基準（左上・中央など、DxLibのeRectOriginを使用）
	TNL_PROPERTY(dxe::eRectOrigin, Location, e_location_);

private:

	// 実際に描画する文字列（プロパティとしても外部から操作可能）
	std::string draw_word_;

	// フォントサイズ（ピクセル単位）
	int font_size_ = 20;

	// 表示色（DxLib の定義値）
	int color_ = dxe::Colors::AliceBlue;

	// 適用中のエフェクト種別
	eEffectType e_effect_type_ = eEffectType::None;

	// 表示座標の基準点（左上・中央など）
	dxe::eRectOrigin e_location_ = dxe::eRectOrigin::LEFT_TOP;

	// エフェクト用の内部カウンタ（秒単位、点滅などのタイミング制御に使用）
	float time_count_ = 0;
};
