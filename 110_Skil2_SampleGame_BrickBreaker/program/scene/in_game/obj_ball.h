#pragma once
#include <dxe.h>
#include "../../common/object/object.h"

//--------------------------------------------------------------------------------------------------------------------------
// Ballクラス
// プレイヤーが操作しない自動移動するボールオブジェクト。
// 画面内を反射しながら移動し、バーやブロックとの衝突処理に関わる。
//--------------------------------------------------------------------------------------------------------------------------
class ObjBall : public Object {
public:

	ObjBall();
	~ObjBall() = default ;

	// 更新処理（位置更新・壁反射）
	void update() override;

	// 描画処理（現在位置にボールを描画）
	void draw() override;

	// 移動ベクトルを反射させる
	// arg1... 接触地点の法線ベクトル
	void reflection( const tnl::Vector2f& surface_normal );

	TNL_PROPERTY(tnl::Vector2f, BeforePosition, before_position_);
	TNL_PROPERTY(float, Speed, speed_);
	TNL_PROPERTY(float, Radius, radius_);

private:
	float radius_ = 20.0f;				  // ボールの半径（衝突判定や描画に使用）
	tnl::Vector2f before_position_;       // 1フレーム前の位置（衝突補正時に使用）
	tnl::Vector2f move_dir_;              // 移動方向ベクトル（単位にspeed_が乗算されて使われる）
	float speed_ = 3.0f;                  // 移動速度（ピクセル毎フレーム）

};
