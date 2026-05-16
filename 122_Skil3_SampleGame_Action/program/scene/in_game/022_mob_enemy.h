#pragma once
#include <dxe.h>
#include "020_character.h"


class MobEnemyDesc {
public:
	MobEnemyDesc() = default;
	MobEnemyDesc(const tnl::CsvCells& csv);
	int32_t type_ = 0;
	tnl::Vector2f bounding_box_size_;
	std::vector<dxe::SpriteAnimationDesc> animations_;
};

//--------------------------------------------------------------------------------------------------------------------------
// MobEnemy クラス
//--------------------------------------------------------------------------------------------------------------------------
class MobEnemy : public Character {
public:

	MobEnemy(const MobEnemyDesc& desc);
	~MobEnemy() = default;

	void onGrounded() override;
	void onHeadBump() override;
	void onSideBump() override;
	void toFreeFall() override;
	void toIdle();
	void toDamage();

private:

	TNL_COROUTINE(seqDamage);

	// 待機シーケンス
	void seqIdle(void);
	// 歩きシーケンス
	void seqWalk(void);
	// 自由落下シーケンス
	void seqFreeFall(void);
	// ダメージシーケンス
	void seqDamage(void);

	int32_t anim_idx_ = 0;

	// 移動制御用変数
	float move_vel_walk_x_ = 2.0f;

};
