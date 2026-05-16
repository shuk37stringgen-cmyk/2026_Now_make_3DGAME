#include "scene_title.h"
#include "../../common/game_manager.h"
#include "../../common/object/obj_text.h"


//-----------------------------------------------------------------------------------------------------------------------
// タイトルシーンの初期化処理
// シーン開始時に一度だけ呼ばれ、テキストオブジェクトの生成と配置を行う
void SceneTitle::lazyInitialize() {

	ObjText* p_text = nullptr;

	// ゲームタイトルの表示テキストを作成
	p_text = new ObjText();
	p_text->setString("BrickBreaker"); // 表示するタイトル名
	p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F }); // 画面中央に配置
	p_text->setFontSize(50); // フォントサイズを大きく設定
	p_text->setColor(dxe::Colors::AliceBlue); // テキストカラー
	p_text->setLocation(dxe::eRectOrigin::CENTER); // 中央基準で配置
	addObject(p_text); // シーンに追加

	// スタート操作の案内テキスト（スペースキーで開始）
	p_text = new ObjText();
	p_text->setString("Press the space key"); // 案内文
	p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F }); // 画面中央より下に表示
	p_text->setFontSize(20); // 小さめのフォント
	p_text->setColor(dxe::Colors::AliceBlue); // テキストカラー
	p_text->setLocation(dxe::eRectOrigin::CENTER); // 中央基準で配置
	p_text->setEffectType(ObjText::eEffectType::Flashing); // 点滅効果で注目を集める
	addObject(p_text); // シーンに追加
}


//-----------------------------------------------------------------------------------------------------------------------
// タイトルシーンの更新処理
// 毎フレーム呼ばれ、シーン内オブジェクトの更新と入力チェックを行う
void SceneTitle::update() {

	// ベースクラス（Scene）の更新処理を呼び出す
	Scene::update();

	// ゲームマネージャーのインスタンスを取得
	GameManager& mgr = GameManager::GetInstance();

	// フェード中は入力を無効化（トランジションが完了していない場合はスキップ）
	if (GameManager::eTransitionState::None != mgr.getTransitionState()) return;

	// スペースキーが押されたらゲーム本編シーン（InGame）へ遷移予約
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		mgr.reserveScene(GameManager::eScene::InGame);
	}
}
