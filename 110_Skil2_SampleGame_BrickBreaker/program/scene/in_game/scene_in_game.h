#pragma once
#include <dxe.h>
#include "../scene.h"

// 前方宣言（循環参照防止）
class ObjBar;
class ObjBall;
class ObjBlock;
class ObjText;

//-----------------------------------------------------------------------------------------------------------------------
// ゲーム本編（ブロック崩しプレイ中）のシーンを管理するクラス
// Scene クラスを継承し、ゲーム中の描画や衝突処理、状態遷移などを制御
class SceneInGame : public Scene {
public:

	SceneInGame() = default;
	~SceneInGame();  // リソースの解放（画像・サウンド）を担当

	// 遅延初期化（シーン開始時に一度だけ呼び出される）
	void lazyInitialize() override;

	// 毎フレーム呼び出される更新処理
	void update() override;


	// プレイ中の状態遷移（カウントダウン → プレイ中 → 結果）を管理するステートマシン
	Shared<tnl::StateMachine> sequence_;

	// 以下はシーン内のステートマシン関数。各ゲーム状態（開始・プレイ・クリア・ゲームオーバー）を制御

	// 開始時カウントダウン演出
	void seqOpening();

	// プレイ中のロジック
	void seqPlaying();

	// すべてのブロック破壊後のクリア演出
	void seqClearEnding();

	// ボールが画面外に出た時のゲームオーバー演出
	void seqOverEnding();

private:


	// プレイヤーが操作するバーのインスタンス
	ObjBar* p_bar_ = nullptr;

	// ボールのインスタンス（跳ね返りやブロック破壊に使用）
	ObjBall* p_ball_ = nullptr;

	// カウントダウンテキスト表示用インスタンス（開始前の演出用）
	ObjText* p_text_opening_ = nullptr;

	// 現在シーン内に存在するブロックのリスト
	std::list<ObjBlock*> blocks_;

	// 効果音ハンドル（ブロック破壊や跳ね返りで使用）
	int sound_hdl_se_ = 0;

	// ブロック画像のグラフィックハンドル
	int img_hdl_block_ = 0;

	// バー画像のグラフィックハンドル
	int img_hdl_bar_ = 0;

	// 開始時のカウントダウン時間（秒）
	const int opening_count_down_time_ = 4.0f;


	// ボールとバーの衝突処理
	void intersectProcessBarAndBall();

	// ボールとブロックの衝突・破壊処理
	void intersectProcessBallAndBlock();

	// ボールと画面端（壁）の衝突処理
	void intersectProcessWindowFrame();
};


