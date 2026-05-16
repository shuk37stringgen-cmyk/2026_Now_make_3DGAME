#pragma once
#include <dxe.h>
#include "010_playable_entity.h"

//--------------------------------------------------------------------------------------------------------------------------
// Character共通データ
//--------------------------------------------------------------------------------------------------------------------------
class Character : public PlayableEntity {
public:

	Character();
	virtual ~Character() = default;

	void update() override;
	void draw(const Shared<dxe::Camera>& camera) override;

	virtual void onGrounded();
	virtual void onHeadBump(){}
	virtual void onSideBump(){}

	virtual void toFreeFall();
	virtual void toDamage(){}

protected:

	int32_t hp_ = 0;
	float spped_ = 0;
	Shared<dxe::Sprite> main_sprite_;

	// キャラクタの行動制御ステートマシン
	Shared<tnl::StateMachine> state_flow_;

};
