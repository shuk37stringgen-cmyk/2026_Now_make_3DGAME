#pragma once
#include <dxe.h>
#include "../../engine/public/scene.h"

// タイトル画面シーンのクラス
// Scene を継承して、タイトル特有の初期化・更新処理を実装する
class SceneTitle : public eng::Scene {
public:

	// デフォルトコンストラクタ（特別な初期化は不要）
	SceneTitle() = default;

	// 遅延初期化処理（ゲーム開始時に一度だけ呼ばれる想定）
	// タイトル画面に必要なリソースの読み込みやオブジェクトの生成を行う
	void lazyInitialize() override;

	// フレーム毎の更新処理
	// 入力受付やアニメーション処理などを記述
	void update() override;

private:

	// タイトルシーン用のメンバ変数があればここに追加
	// 例: テキストオブジェクト、アニメーション、選択中項目など
};