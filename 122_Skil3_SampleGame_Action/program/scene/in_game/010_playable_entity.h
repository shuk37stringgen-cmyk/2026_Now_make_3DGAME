#pragma once
#include <dxe.h>
#include "../common/010_unit2d.h"

//--------------------------------------------------------------------------------------------------------------------------
// Characterã§í ÉfÅ[É^
//--------------------------------------------------------------------------------------------------------------------------
class PlayableEntity : public Unit2D {
public:

	PlayableEntity();
	virtual ~PlayableEntity() = default;

	enum class eMobilityState {
		Grounded
		, Floating
		, Flying
	};

	enum class fIntersectState {
		None
		, Character		= 1 << 0
		, Player		= 1 << 1
		, MobEnemy		= 1 << 2
		, FieldObject	= 1 << 3
		, Block			= 1 << 4
		, Goal			= 1 << 5
	};

	TNL_PROPERTY(eMobilityState, MobilityState, mobility_state_);

	fIntersectState getSelfIntersectState() { return self_intersect_state_; }
	void onSelfIntersectState(fIntersectState flag);
	bool isEnableOhterIntersect(fIntersectState other_state);

	fIntersectState getOtherIntersectState() { return other_intersect_states_; }
	void clearOtherIntersectState() { other_intersect_states_ = fIntersectState::None; }
	void onOtherIntersectState(fIntersectState flag);
	void offOtherIntersectState(fIntersectState flag);

private:
	fIntersectState self_intersect_state_;
	fIntersectState other_intersect_states_;
	eMobilityState mobility_state_ = eMobilityState::Grounded;

};

TNL_ENUM_CLASS_BIT_MASK_OPERATOR(PlayableEntity::fIntersectState);

