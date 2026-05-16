#pragma once
#include <dxe.h>
#include "../../engine/public/scene.h"
#include "../../engine/public/object/100_obj_text.h"

// 前方宣言（循環参照防止）
class Character;
class Player;
class MobEnemy;
class FieldObject;


//-----------------------------------------------------------------------------------------------------------------------
// ゲーム本編のシーンを管理するクラス
// Scene クラスを継承し、ゲーム中の描画や衝突処理、状態遷移などを制御
class SceneInGame : public eng::Scene {
public:

	// オブジェクトの描画優先度( 下に行くほど奥に描画されます )
	enum class eDrawPriority {
		Player
		, Enemy
		, Goal
		, Block
		, BackGround
	};

	const int32_t FIELD_INFO_ID_BLOCK = 1;
	const int32_t FIELD_INFO_ID_START_POSITION = 20;
	const int32_t FIELD_INFO_ID_GOAL_POSITION = 21;
	const int32_t FIELD_INFO_ID_ENEMY_MOB_OCTOPUS = 30;

	SceneInGame() = default;
	~SceneInGame();  // リソースの解放（画像・サウンド）を担当

	// 遅延初期化（シーン開始時に一度だけ呼び出される）
	void lazyInitialize() override;

	// 毎フレーム呼び出される更新処理
	void update() override;

	void draw() override;

	// カメラの取得
	const Shared<dxe::Camera> getCamera() { return camera_; }

	TNL_PROPERTY(bool, EnableFollowCamera, enable_follow_camera_);

	const float BLOCK_SIZE = 64.0f ;

	// プレイ中にカメラはプレイヤーから少し上をフォーカスするためのオフセット
	const tnl::Vector2f CAMERA_FORCUS_OFFSET = { 0, -100 };

private:

	// ゲーム空間のサイズ
	// csv からチップ数を取得して決定される
	tnl::Vector2f world_size_;
	tnl::Vector2f world_size_half_;

	// フォントリソース
	Shared<dxe::FontTextResouce> font_res_big_;
	Shared<dxe::FontTextResouce> font_res_mid_;
	Shared<dxe::FontTextResouce> font_res_sml_;

	// プレイ中の状態遷移（カウントダウン → プレイ中 → 結果）を管理するステートマシン
	Shared<tnl::StateMachine> sequence_;

	Shared<Player> player_;

	Shared<FieldObject> goal_;

	// 現在シーン内に存在するブロックのリスト
	std::list<Shared<FieldObject>> block_list_;

	// 現在シーン内に存在するモブのリスト
	std::list<Shared<MobEnemy>> mob_list_;

	// カウントダウンテキスト表示用インスタンス（開始前の演出用）
	Shared<eng::ObjText> p_text_opening_ = nullptr;


	bool enable_follow_camera_ = false;

	// 効果音ハンドル（ブロック破壊や跳ね返りで使用）
	int sound_hdl_se_ = 0;

	// 開始時のカウントダウン時間（秒）
	const int opening_count_down_time_ = 4.0f;

	void followCameraUpdate();

	// キャラクタとブロックの衝突処理
	void intersectCharacterAndBlock(const Shared<Character>& charcter);

	// プレイヤとモブ１体の衝突処理
	void intersectPlayerAndMobEnemy(const Shared<MobEnemy>& mob_enemy);

	// プレイヤとゴールオブジェクトの衝突処理
	void intersectPlayerAndGoal();

	// モブ敵全体に対してシーンから行う処理
	void resolveEnemyInteractions();

	// 以下はシーン内のステートマシン関数。各ゲーム状態（開始・プレイ・クリア・ゲームオーバー）を制御

	// 開始時カウントダウン演出
	void seqOpening();

	// プレイ中のロジック
	void seqPlaying();

	// クリア演出
	void seqClearEnding();

	// ゲームオーバー演出
	void seqOverEnding();


};