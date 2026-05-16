#include "scene_title.h"
#include "../../../ResourceConstantHedder.h"
#include "../../engine/public/engine.h"
#include "../../engine/public/object/100_obj_text.h"
#include "../in_game/scene_in_game.h"
#include "../../engine/public/object/030_obj_drawable.h"


//-----------------------------------------------------------------------------------------------------------------------
// タイトルシーンの初期化処理
// シーン開始時に一度だけ呼ばれ、テキストオブジェクトの生成と配置を行う
void SceneTitle::lazyInitialize() {

	// テキストオブジェクト用リソース
	// arg1... フォントサイズ
	// arg2... フォント名 ( 省略は "ＭＳ Ｐ明朝" )
	// arg3... クオリティ設定 ( DX_FONTTYPE_**** )
	// arg4... フォントの太さ ( 省略 は デフォルトの -1 )
	// arg5... 文字枠の太さ ( 省略は枠無し )
	// ret.... dxe::FontText の std::shared_ptr
	Shared<dxe::FontTextResouce> resource = dxe::FontTextResouce::Create(
		50, FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 2, 1);


	Shared<eng::ObjText> p_text = nullptr;

	// ゲームタイトルの表示テキストを作成
	p_text = std::make_shared<eng::ObjText>(resource);
	p_text->setString("ActionGame"); // 表示するタイトル名
	p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F }); // 画面中央に配置
	p_text->setColor(dxe::Colors::AliceBlue); // テキストカラー
	p_text->setLocation(dxe::eRectOrigin::CENTER); // 中央基準で配置
	addObject(p_text); // シーンに追加

	// スタート操作の案内テキスト（スペースキーで開始）
	p_text = std::make_shared<eng::ObjText>(resource);
	p_text->setString("Press the space key"); // 案内文
	p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F }); // 画面中央より下に表示
	p_text->setColor(dxe::Colors::AliceBlue); // テキストカラー
	p_text->setLocation(dxe::eRectOrigin::CENTER); // 中央基準で配置
	p_text->setScale({ 0.3f, 0.3f });
	p_text->setEffectType(eng::ObjText::eEffectType::Flashing); // 点滅効果で注目を集める
	addObject(p_text); // シーンに追加

}


//-----------------------------------------------------------------------------------------------------------------------
// タイトルシーンの更新処理
// 毎フレーム呼ばれ、シーン内オブジェクトの更新と入力チェックを行う
void SceneTitle::update() {

	// ベースクラス（Scene）の更新処理を呼び出す
	Scene::update();

	// ゲームマネージャーのインスタンスを取得
	eng::Engine& mgr = eng::Engine::GetInstance();

	// フェード中は入力を無効化（トランジションが完了していない場合はスキップ）
	if (eng::Engine::eTransitionState::None != mgr.getTransitionState()) return;

	// スペースキーが押されたらゲーム本編シーン（InGame）へ遷移予約
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		mgr.reserveScene( std::make_shared<SceneInGame>() );
	}
}


