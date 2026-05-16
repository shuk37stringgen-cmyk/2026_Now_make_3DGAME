#include "scene_result.h"
#include "../../common/game_manager.h"
#include "../../common/object/obj_text.h"


//-----------------------------------------------------------------------------------------------------------------------
// リザルトシーンの初期化処理。
// この関数はシーン切り替え時に1度だけ呼び出され、画面に表示するテキストオブジェクトを追加する。
void SceneResult::lazyInitialize() {

	ObjText* p_text = nullptr;

	// 中央に "Scene Result" と表示する大きなテキスト
	p_text = new ObjText();
	p_text->setString("Scene Result");
	p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F }); // 画面中央
	p_text->setFontSize(50);                       // フォントサイズ
	p_text->setColor(dxe::Colors::AliceBlue);      // 色設定
	p_text->setLocation(dxe::eRectOrigin::CENTER); // 座標の基準点を中央に設定
	addObject(p_text);                             // シーンに追加

	// 下に "Press the space key" と表示する小さなテキスト（点滅効果付き）
	p_text = new ObjText();
	p_text->setString("Press the space key");
	p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F }); // 中央より下
	p_text->setFontSize(20);                         // フォントサイズ
	p_text->setColor(dxe::Colors::AliceBlue);        // 色設定
	p_text->setLocation(dxe::eRectOrigin::CENTER);   // 座標の基準点を中央に設定
	p_text->setEffectType(ObjText::eEffectType::Flashing); // フラッシング（点滅）効果
	addObject(p_text);                               // シーンに追加
}


//-----------------------------------------------------------------------------------------------------------------------
// 毎フレーム呼び出される更新処理。
// 入力処理や次のシーンへの遷移制御などを行う。
void SceneResult::update() {

	Scene::update(); // ベースクラスの更新処理（オブジェクトの更新など）

	// シングルトンの GameManager インスタンスを取得
	GameManager& mgr = GameManager::GetInstance();

	// 現在シーン遷移中（フェード中）なら、操作を無効にする
	if (GameManager::eTransitionState::None != mgr.getTransitionState()) return;

	// スペースキーが押されたら、タイトルシーンへ遷移を予約する
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		mgr.reserveScene(GameManager::eScene::Title);
	}

}