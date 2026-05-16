#include "scene_in_game.h"
#include "../../../ResourceConstantHedder.h"
#include "../../engine/public/engine.h"
#include "../../engine/public/object/100_obj_text.h"
#include "../../engine/public/object/110_obj_scenery.h"
#include "../result/scene_result.h"
#include "021_player.h"
#include "022_mob_enemy.h"
#include "030_field_object.h"

//-----------------------------------------------------------------------------------------------------------------------
// デストラクタ：シーン終了時にサウンド・画像などのリソースを解放
SceneInGame::~SceneInGame() {
	DeleteSoundMem(sound_hdl_se_);
}

//-----------------------------------------------------------------------------------------------------------------------
// シーン初期化処理：ゲーム開始時に一度だけ呼ばれる
void SceneInGame::lazyInitialize() {

	font_res_big_ = dxe::FontTextResouce::Create( 80, FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 2, 1);
	font_res_mid_ = dxe::FontTextResouce::Create( 40, FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 2, 1);
	font_res_sml_ = dxe::FontTextResouce::Create( 20, FONT_NAME_CORPORATE_LOGO_ROUNDED_VER3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, 2, 1);

	// インゲームシーンの状態遷移を管理するステートマシンを生成
	// 最初は seqOpening を設定
	sequence_ = TNL_STATE_MACHINE_CREATE(&SceneInGame::seqOpening, this);

	// 背景の生成
	// ※背景は設置するだけのオブジェクトとして生成
	Shared<dxe::SpriteResouce> bg_image = dxe::SpriteResouce::Create(FILE_PATH_PNG_SKY01);
	Shared<eng::ObjScenery> bg = std::make_shared<eng::ObjScenery>(bg_image);
	Shared<dxe::Sprite> bg_sprite = bg->getSprite();
	bg_sprite->setCameraFollowWeightX(0.1f); // 遠景なのでカメラの影響値を小さくする
	bg_sprite->setCameraFollowWeightY(0.1f);
	bg->setDrawPriority(static_cast<int>(eDrawPriority::BackGround));
	addObject(bg);

	// プレイヤキャラの生成
	player_ = std::make_shared<Player>();
	player_->setDrawPriority(static_cast<int>(eDrawPriority::Player));
	addObject(player_);


	// フィールドデータ構築
	auto field_obj_csv = tnl::LoadCsv(FILE_PATH_CSV_STAGE1_FIELD_INFO);
	world_size_.x = field_obj_csv[0].size() * BLOCK_SIZE;
	world_size_.y = field_obj_csv.size() * BLOCK_SIZE ;
	world_size_half_.x = world_size_.x * 0.5f;
	world_size_half_.y = world_size_.y * 0.5f;

	// ザコキャラ情報をcsvから取得
	auto enemy_mob_oct_csv = tnl::LoadCsv(FILE_PATH_CSV_ENEMY_MOB_OCTOPUS);


	for (int i = 0; i < field_obj_csv.size(); ++i) {
		for (int k = 0; k < field_obj_csv[i].size(); ++k) {
			int32_t param = field_obj_csv[i][k].getInt();
			if (!param) continue;
			if (FIELD_INFO_ID_BLOCK == param) {
				FieldObjectDesc desc;
				desc.type_ = static_cast<int>(FieldObject::eType::Block);
				desc.bounding_box_ = { 64.0f, 64.0f };
				desc.sprite_descs_.emplace_back( dxe::SpriteDesc(FILE_PATH_PNG_BLOCK) );
				Shared<FieldObject> block = std::make_shared<FieldObject>( desc );
				block->onSelfIntersectState(PlayableEntity::fIntersectState::Block);
				block->setPosition({ -world_size_half_.x + k * BLOCK_SIZE, -world_size_half_.y + i * BLOCK_SIZE });
				block->setDrawPriority(static_cast<int>(eDrawPriority::Block));
				block_list_.emplace_back(block);
				addObject(block);
			}
			if (FIELD_INFO_ID_START_POSITION == param) {
				player_->setPosition({ -world_size_half_.x + k * BLOCK_SIZE, -world_size_half_.y + i * BLOCK_SIZE });
			}
			if (FIELD_INFO_ID_GOAL_POSITION == param) {
				FieldObjectDesc desc;
				desc.type_ = static_cast<int>(FieldObject::eType::Goal);
				desc.bounding_box_ = { 50.0f, 50.0f };
				desc.sprite_descs_.emplace_back(dxe::SpriteDesc(FILE_PATH_PNG_STAR));
				goal_ = std::make_shared<FieldObject>(desc);
				goal_->onSelfIntersectState(PlayableEntity::fIntersectState::Goal);
				goal_->setPosition({ -world_size_half_.x + k * BLOCK_SIZE, -world_size_half_.y + i * BLOCK_SIZE });
				goal_->setDrawPriority(static_cast<int>(eDrawPriority::Goal));
				addObject(goal_);
			}

			if (FIELD_INFO_ID_ENEMY_MOB_OCTOPUS == param) {
				MobEnemyDesc desc( enemy_mob_oct_csv );
				Shared<MobEnemy> mob = std::make_shared<MobEnemy>( desc );
				mob->setPosition({ -world_size_half_.x + k * BLOCK_SIZE, -world_size_half_.y + i * BLOCK_SIZE });
				mob->setDrawPriority(static_cast<int>(eDrawPriority::Enemy));
				mob->setPosture(Unit2D::ePosture::Left);
				mob->setEnableUpdate(false);
				mob_list_.emplace_back(mob);
				addObject(mob);
			}
		}
	}


	// 効果音の読み込みと音量設定
	sound_hdl_se_ = LoadSoundMem(FILE_PATH_MP3_SE_SAMPLE_0);
	SetVolumeSoundMem(8500, sound_hdl_se_);


	// 操作方法の説明テキストを表示
	Shared<eng::ObjText> p_text = std::make_shared<eng::ObjText>(font_res_sml_);
	p_text->setString(" Left  Move [ A ] \n Right Move [ D ] \n Jump [ W ] \n Dash [ R-Ctrl ]");
	p_text->setPosition({ 0, 0 });
	p_text->setColor(dxe::Colors::Black);
	p_text->setUpdatePriority(10);
	addObject(p_text);


	// カメラの初期位置を設定
	camera_->setPosition2D(player_->getPosition() + CAMERA_FORCUS_OFFSET);
}

//-----------------------------------------------------------------------------------------------------------------------
// 毎フレームの更新処理：シーケンスと全オブジェクトを更新
void SceneInGame::update() {
	sequence_->update(dxe::GetDeltaTime()); // 時間に応じて現在のシーケンスを進行
	Scene::update(); // 登録されたオブジェクト全体の更新

	followCameraUpdate();
	intersectPlayerAndGoal();
	intersectCharacterAndBlock(player_);
	resolveEnemyInteractions();

}


void SceneInGame::draw() {
	Scene::draw();
}


void SceneInGame::followCameraUpdate() {
	if (!enable_follow_camera_) return;
	tnl::Vector2f cam_pos = camera_->getPosition2D();
	tnl::Vector2f cam_fix_pos = player_->getPosition() + CAMERA_FORCUS_OFFSET;
	cam_pos += (cam_fix_pos - cam_pos) * 0.05f;
	cam_pos.x = std::clamp(cam_pos.x, -world_size_half_.x, world_size_half_.x);
	cam_pos.y = std::clamp(cam_pos.y, -world_size_half_.y, world_size_half_.y);
	camera_->setPosition2D(cam_pos);
}


//--------------------------------------------------------------------------------------------------------------------------
// オープニング演出（カウントダウン）
void SceneInGame::seqOpening() {

	if (sequence_->isStart()) {

		// カウントダウン用のテキストオブジェクト生成
		p_text_opening_ = std::make_shared<eng::ObjText>(font_res_big_);
		p_text_opening_->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F });
		p_text_opening_->setColor(dxe::Colors::MediumVioletRed);
		p_text_opening_->setLocation(dxe::eRectOrigin::CENTER);
		addObject(p_text_opening_);
	}

	// 残り秒数を文字列にして表示（小数点以下切り捨て）
	p_text_opening_->setString(
		std::to_string(static_cast<int>(opening_count_down_time_ - sequence_->getProgressTime())));

	// カウントが終了したらシーケンスをプレイ状態へ
	if (sequence_->getProgressTime() > opening_count_down_time_) {
		p_text_opening_->setAlive(false);
		sequence_->change( TNL_STATE_BIND( &SceneInGame::seqPlaying, this ) );
	}

	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ゲームプレイ中の処理
void SceneInGame::seqPlaying() {

	if (sequence_->isStart()) {
		player_->setEnableInput(true);
		setEnableFollowCamera(true);
	}

	if (!player_->isInsideScreen(camera_)) {
		player_->setEnableUpdate(false);
		sequence_->change(TNL_STATE_BIND(&SceneInGame::seqOverEnding, this));
	}

	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ゲームオーバー演出
void SceneInGame::seqOverEnding() {


	if (sequence_->isStart()) {
		player_->setEnableInput(false);

		// "Game Over" と "Press the space key" を表示
		Shared<eng::ObjText> p_text = std::make_shared<eng::ObjText>(font_res_big_);
		p_text->setString("Game Over");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F });
		p_text->setColor(dxe::Colors::MediumVioletRed);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		addObject(p_text);

		p_text = std::make_shared<eng::ObjText>(font_res_mid_);
		p_text->setString("Press the space key");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F });
		p_text->setColor(dxe::Colors::MediumVioletRed);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		p_text->setEffectType(eng::ObjText::eEffectType::Flashing);
		addObject(p_text);
	}

	// スペースキーでリザルトシーンへ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		eng::Engine& mgr = eng::Engine::GetInstance();
		mgr.reserveScene( std::make_shared<SceneResult>() );
	}

	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ゲームクリア演出
void SceneInGame::seqClearEnding() {

	if (sequence_->isStart()) {
		player_->setEnableInput(false);

		// "Congratulations" と "Press the space key" を表示
		Shared<eng::ObjText> p_text = std::make_shared<eng::ObjText>(font_res_big_);
		p_text->setString("Congratulations");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F });
		p_text->setColor(dxe::Colors::MediumVioletRed);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		addObject(p_text);

		p_text = std::make_shared<eng::ObjText>(font_res_mid_);
		p_text->setString("Press the space key");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F });
		p_text->setColor(dxe::Colors::MediumVioletRed);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		p_text->setEffectType(eng::ObjText::eEffectType::Flashing);
		addObject(p_text);
	}

	// スペースキーでリザルトシーンへ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		eng::Engine& mgr = eng::Engine::GetInstance();
		mgr.reserveScene(std::make_shared<SceneResult>());
	}

	return ;
}


//--------------------------------------------------------------------------------------------------------------------------
void SceneInGame::intersectCharacterAndBlock( const Shared<Character>& character ) {

	if (!character->isEnableOhterIntersect(PlayableEntity::fIntersectState::Block)) return;

	// 対象キャラクタに近い順にブロックをソート
	block_list_.sort([&](Shared<FieldObject> l, Shared<FieldObject> r) {
		float ld = (character->getPosition() - l->getPosition()).length();
		float rd = (character->getPosition() - r->getPosition()).length();
		return ld < rd;
		});

	if (PlayableEntity::eMobilityState::Grounded == character->getMobilityState()) {
		character->setMobilityState(PlayableEntity::eMobilityState::Floating);

		for_with_index(it, block_list_, i, 0, ++) {
			if (4 == i) break;
			Shared<FieldObject> block = *it;
			tnl::Vector2f posA = character->getPositionWithFallVelocity();
			tnl::Vector2f sizeA = character->getBoundingBox();
			tnl::Vector2f before_A = character->getBeforePosition();
			tnl::Vector2f posB = block->getPosition();
			tnl::Vector2f sizeB = block->getBoundingBox();
			tnl::Vector2f before_B = block->getBeforePosition();

			if (tnl::IsIntersectRect(posA, sizeA.x, sizeA.y, posB, sizeB.x, sizeB.y)) {
				character->setMobilityState(PlayableEntity::eMobilityState::Grounded);
				break;
			}
		}
		if (PlayableEntity::eMobilityState::Floating == character->getMobilityState()) {
			character->toFreeFall();
		}
	}

	for_with_index(it, block_list_, i, 0, ++) {
		if (4 == i) break;
		Shared<FieldObject> block = *it;
		tnl::Vector2f posA = character->getPosition();
		tnl::Vector2f sizeA = character->getBoundingBox();
		tnl::Vector2f before_A = character->getBeforePosition();
		tnl::Vector2f posB = block->getPosition();
		tnl::Vector2f sizeB = block->getBoundingBox();
		tnl::Vector2f before_B = block->getBeforePosition();

		// 衝突判定
		if (tnl::IsIntersectRect(posA, sizeA.x, sizeA.y, posB, sizeB.x, sizeB.y)) {

			tnl::eCorrResRect corr = tnl::CorrectPositionRect(
				before_A
				, before_B
				, sizeA
				, sizeB
				, posA
				, posB
				, tnl::eCorrTypeRect::PWRFL_B
				, tnl::eCorrTypeRect::PWRFL_B, 0.5f);

			character->setPosition(posA);
			if (corr == tnl::eCorrResRect::UP) {
				character->onGrounded();
			}
			if (corr == tnl::eCorrResRect::DOWN) {
				character->onHeadBump();
			}
			if (corr == tnl::eCorrResRect::LEFT || corr == tnl::eCorrResRect::RIGHT) {
				character->onSideBump();
			}
		}

	}
}


//--------------------------------------------------------------------------------------------------------------------------
void SceneInGame::intersectPlayerAndMobEnemy(const Shared<MobEnemy>& mob) {

	if (!mob->isEnableOhterIntersect(PlayableEntity::fIntersectState::Player)) return;
	if (!player_->isEnableOhterIntersect(PlayableEntity::fIntersectState::MobEnemy)) return;

	tnl::Vector2f posA = player_->getPosition();
	tnl::Vector2f sizeA = player_->getBoundingBox();
	tnl::Vector2f before_A = player_->getBeforePosition();
	tnl::Vector2f posB = mob->getPosition();
	tnl::Vector2f sizeB = mob->getBoundingBox();
	tnl::Vector2f before_B = mob->getBeforePosition();

	// 衝突判定
	if (tnl::IsIntersectRect(posA, sizeA.x, sizeA.y, posB, sizeB.x, sizeB.y)) {

		tnl::eCorrResRect corr = tnl::CorrectPositionRect(
			before_A
			, before_B
			, sizeA
			, sizeB
			, posA
			, posB
			, tnl::eCorrTypeRect::PWRFL_B
			, tnl::eCorrTypeRect::PWRFL_B, 0.5f);

		if (corr == tnl::eCorrResRect::UP) {
			mob->toDamage();
			player_->setPosition(posA);
			player_->toJump();
		}
		else {
			player_->toDamage();
			mob->toIdle();
			setEnableFollowCamera(false);
		}
	}

}


//--------------------------------------------------------------------------------------------------------------------------
void SceneInGame::intersectPlayerAndGoal() {
	if (!player_->isEnableOhterIntersect(PlayableEntity::fIntersectState::Goal)) return;

	tnl::Vector2f posA = player_->getPosition();
	tnl::Vector2f sizeA = player_->getBoundingBox();
	tnl::Vector2f before_A = player_->getBeforePosition();
	tnl::Vector2f posB = goal_->getPosition();
	tnl::Vector2f sizeB = goal_->getBoundingBox();
	tnl::Vector2f before_B = goal_->getBeforePosition();

	// 衝突判定
	if (tnl::IsIntersectRect(posA, sizeA.x, sizeA.y, posB, sizeB.x, sizeB.y)) {
		player_->offOtherIntersectState(PlayableEntity::fIntersectState::Goal);
		player_->offOtherIntersectState(PlayableEntity::fIntersectState::MobEnemy);
		sequence_->change(TNL_STATE_BIND(&SceneInGame::seqClearEnding, this));
		goal_->setAlive(false);
		goal_ = nullptr;
	}

}


//--------------------------------------------------------------------------------------------------------------------------
void SceneInGame::resolveEnemyInteractions() {

	auto it = mob_list_.begin();
	while(it != mob_list_.end()) {
		Shared<MobEnemy> mob = *it;
		if (!mob->getAlive()) {
			it = mob_list_.erase(it);
			continue;
		}
		if (mob->isInsideScreen(camera_)) {
			mob->setEnableUpdate(true);
		}
		intersectCharacterAndBlock(mob);
		it++;
	}

	// プレイヤに近い順にモブをソート
	mob_list_.sort([&](Shared<MobEnemy> l, Shared<MobEnemy> r) {
		float ld = (player_->getPosition() - l->getPosition()).length();
		float rd = (player_->getPosition() - r->getPosition()).length();
		return ld < rd;
	});

	if (mob_list_.empty()) return;
	Shared<MobEnemy> mob = *mob_list_.begin();
	intersectPlayerAndMobEnemy(mob);

}

