#include "010_playable_entity.h"


PlayableEntity::PlayableEntity() {
	setMobilityState(eMobilityState::Floating);
}

void PlayableEntity::onSelfIntersectState(fIntersectState flag) {
	self_intersect_state_ |= flag;
}

bool PlayableEntity::isEnableOhterIntersect(fIntersectState other_state) { 
	return static_cast<bool>(other_intersect_states_ & other_state); 
}

void PlayableEntity::onOtherIntersectState(fIntersectState flag) {
	other_intersect_states_ |= flag;
}
void PlayableEntity::offOtherIntersectState(fIntersectState flag) {
	other_intersect_states_ &= ~flag;
}
