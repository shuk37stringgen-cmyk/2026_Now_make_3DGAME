#pragma once
#include <dxe.h>
#include "../scene.h"

// リザルト（結果）画面を管理するシーンのクラス
// Scene 基底クラスを継承して、結果画面に必要な処理を実装
class SceneResult : public Scene {
public:

	// コンストラクタ（特別な初期化は不要）
	SceneResult() = default;

	// 遅延初期化処理（シーン切り替え時に一度だけ呼ばれる）
	// リザルト画面に必要なテキストやオブジェクトの生成を行う
	void lazyInitialize() override;

	// フレーム毎の更新処理（毎フレーム呼び出される）
	// 入力判定やアニメーション処理などを行う
	void update() override;

private:

	// リザルトシーン専用のメンバ変数（テキストや演出など）を追加する場合はここに定義
};