#pragma once
#include <dxe.h>
#include "010_playable_entity.h"

class FieldObjectDesc : public Unit2DDesc{
public :
	int32_t type_ = 0;
};

//--------------------------------------------------------------------------------------------------------------------------
// フィールドオブジェクト共通データ
//--------------------------------------------------------------------------------------------------------------------------
class FieldObject : public PlayableEntity {
public:
	enum class eType {
		None
		,Block
		,Goal
	};

	FieldObject( const FieldObjectDesc& desc );
	~FieldObject() = default;

	void update() override;
	void draw(const Shared<dxe::Camera>& camera) override;

protected:

	eType type_ = eType::None ;
	Shared<dxe::Sprite> sprite_;
	
};
