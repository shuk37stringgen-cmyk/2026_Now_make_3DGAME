#pragma once
#include <dxe.h>

// ゲームオブジェクトの基本クラス
// update/drawの仮想関数を持ち、派生クラスで具体的な挙動を定義する。
// 各シーンにおける描画・更新オブジェクトのベースとして使われる。
class Object {
public:
	// コンストラクタ（特に初期化処理なし）
	Object() = default;

	// 仮想デストラクタ（派生クラスでリソース解放が必要な場合に対応）
	virtual ~Object() {}

	// 更新処理（フレーム毎に呼ばれる想定、派生クラスでオーバーライド）
	virtual void update() {}

	// 描画処理（毎フレーム呼ばれる想定、派生クラスでオーバーライド）
	virtual void draw() {}

	// オブジェクトの有効・無効（削除フラグ）を制御
	TNL_PROPERTY(bool, Alive, is_alive_);

	// 描画されるかどうかを制御
	TNL_PROPERTY(bool, Visible, is_visible_);

	// 更新されるかどうかを制御
	TNL_PROPERTY(bool, EnableUpdate, is_update_);

	// 更新処理の優先度（大きい方が先に更新される）
	TNL_PROPERTY(int, UpdatePriority, update_priority_);

	// 描画処理の優先度（大きい方が先に描画される）
	TNL_PROPERTY(int, DrawPriority, draw_priority_);

	// オブジェクトの座標
	TNL_CALC_PROPERTY(tnl::Vector2f, Position, position_);

	// 経過時間（秒）を取得（シーン内で自動的に加算される）
	float getElapsedTime() const { return elapsed_time_; }

	// 経過フレーム数を取得（シーン内で自動的に加算される）
	int getElapsedFrame() const { return elapsed_frame_; }

protected:
	// Scene クラスからアクセス可能にする
	friend class Scene;

	// 生存フラグ（false でオブジェクトが削除対象になる）
	bool is_alive_ = true;

	// 描画フラグ（false で draw() がスキップされる）
	bool is_visible_ = true;

	// 更新フラグ（false で update() がスキップされる）
	bool is_update_ = true;

	// 経過時間（秒）
	float elapsed_time_ = 0;

	// 経過フレーム数
	int elapsed_frame_ = 0;

	// 更新優先度
	int update_priority_ = 0;

	// 描画優先度
	int draw_priority_ = 0;

	// オブジェクトの座標（左上または中心座標など使用側に依存）
	tnl::Vector2f position_;

	// 経過時間を加算する（内部用、Scene から呼ばれる）
	void addElapsedTime(float delta_time) { elapsed_time_ += delta_time; }

	// フレーム数を加算する（内部用、Scene から呼ばれる）
	void updateElapsedFrame() { elapsed_frame_++; }
};