#include "scene_in_game.h"
#include "../../../ResourceConstantHedder.h"
#include "../../common/game_manager.h"
#include "../../common/object/obj_text.h"
#include "obj_bar.h"
#include "obj_ball.h"
#include "obj_block.h"

//-----------------------------------------------------------------------------------------------------------------------
// デストラクタ：シーン終了時にサウンド・画像などのリソースを解放
SceneInGame::~SceneInGame() {
	DeleteGraph(img_hdl_block_);
	DeleteGraph(img_hdl_bar_);
	DeleteSoundMem(sound_hdl_se_);
}


//-----------------------------------------------------------------------------------------------------------------------
// シーン初期化処理：ゲーム開始時に一度だけ呼ばれる
void SceneInGame::lazyInitialize() {

	// インゲームシーンの状態遷移を管理するステートマシンを生成
	// 最初は seqOpening を設定
	sequence_ = TNL_STATE_MACHINE_CREATE(&SceneInGame::seqOpening, this);

	// 効果音の読み込みと音量設定
	sound_hdl_se_ = LoadSoundMem(FILE_PATH_MP3_SE_SAMPLE_0);
	SetVolumeSoundMem(8500, sound_hdl_se_);

	// ブロックとバーの画像読み込み
	img_hdl_block_ = LoadGraph(FILE_PATH_PNG_BLOCK);
	img_hdl_bar_ = LoadGraph(FILE_PATH_PNG_BAR);

	// バーオブジェクトの生成と登録
	ObjBar* bar = new ObjBar();
	addObject(bar);
	p_bar_ = bar;
	p_bar_->setEnableUpdate(false); // 最初は非アクティブ（オープニング後に有効化）
	p_bar_->setImageHandle(img_hdl_bar_);

	// ボールオブジェクトの生成と登録
	ObjBall* ball = new ObjBall();
	addObject(ball);
	p_ball_ = ball;
	p_ball_->setEnableUpdate(false); // 最初は非アクティブ（オープニング後に有効化）

	// ブロックをグリッド状に配置
	float sx = 290;
	float sy = 100;
	for (int i = 0; i < ObjBlock::BLOCK_NUM_H; ++i) {
		for (int k = 0; k < ObjBlock::BLOCK_NUM_W; ++k) {
			ObjBlock* p_block = new ObjBlock();
			p_block->setPosition({ sx + k * ObjBlock::BLOCK_SIZE_W, sy + i * ObjBlock::BLOCK_SIZE_H });
			p_block->setSize({ ObjBlock::BLOCK_SIZE_W, ObjBlock::BLOCK_SIZE_H });
			p_block->setImageHandle(img_hdl_block_);
			addObject(p_block);
			blocks_.emplace_back(p_block);
		}
	}

	// 操作方法の説明テキストを表示
	ObjText* p_text = new ObjText();
	p_text->setString(" Left  Move [ A ] \n Right Move [ D ]");
	p_text->setPosition({ 0, 0 });
	p_text->setFontSize(20);
	p_text->setColor(dxe::Colors::AliceBlue);
	p_text->setUpdatePriority(10);
	addObject(p_text);
}

//-----------------------------------------------------------------------------------------------------------------------
// 毎フレームの更新処理：シーケンスと全オブジェクトを更新
void SceneInGame::update() {
	sequence_->update(dxe::GetDeltaTime()); // 時間に応じて現在のシーケンスを進行
	Scene::update(); // 登録されたオブジェクト全体の更新
}

//--------------------------------------------------------------------------------------------------------------------------
// オープニング演出（カウントダウン）
void SceneInGame::seqOpening() {
	
	if (sequence_->isStart()) {
		// カウントダウン用のテキストオブジェクト生成
		p_text_opening_ = new ObjText();
		p_text_opening_->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F });
		p_text_opening_->setFontSize(50);
		p_text_opening_->setColor(dxe::Colors::AliceBlue);
		p_text_opening_->setLocation(dxe::eRectOrigin::CENTER);
		addObject(p_text_opening_);
	}

	// 残り秒数を文字列にして表示（小数点以下切り捨て）
	p_text_opening_->setString(
		std::to_string(static_cast<int>(opening_count_down_time_ - sequence_->getProgressTime())));

	// カウントが終了したらシーケンスをプレイ状態へ
	if (sequence_->getProgressTime() > opening_count_down_time_) {
		p_text_opening_->setAlive(false);
		sequence_->change(TNL_STATE_BIND(&SceneInGame::seqPlaying, this));
	}
	
	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ゲームプレイ中の処理
void SceneInGame::seqPlaying() {
	
	if (sequence_->isStart()) {
		// ゲーム開始時にバーとボールの更新を有効化
		p_bar_->setEnableUpdate(true);
		p_ball_->setEnableUpdate(true);
	}

	// デバッグ用：リターンキーで強制的にブロックを消す
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		for (auto block : blocks_) block->setAlive(false);
		blocks_.clear();
	}

	// ブロックをすべて消したらクリア演出へ移行
	if (blocks_.empty()) {
		p_bar_->setEnableUpdate(false);
		p_ball_->setEnableUpdate(false);
		sequence_->change(TNL_STATE_BIND(&SceneInGame::seqClearEnding, this));

	}

	// ボールが画面外に落ちたらゲームオーバーへ
	if (p_ball_->getPosition().y > DXE_WINDOW_HEIGHT_F) {
		sequence_->change(TNL_STATE_BIND(&SceneInGame::seqOverEnding, this));
	}

	// 衝突判定
	intersectProcessBarAndBall();
	intersectProcessBallAndBlock();
	intersectProcessWindowFrame();
	
	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ゲームオーバー演出
void SceneInGame::seqOverEnding() {
	
	if (sequence_->isStart()) {
		// "Game Over" と "Press the space key" を表示
		ObjText* p_text = new ObjText();
		p_text->setString("Game Over");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F });
		p_text->setFontSize(50);
		p_text->setColor(dxe::Colors::AliceBlue);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		addObject(p_text);

		p_text = new ObjText();
		p_text->setString("Press the space key");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F });
		p_text->setFontSize(20);
		p_text->setColor(dxe::Colors::AliceBlue);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		p_text->setEffectType(ObjText::eEffectType::Flashing);
		addObject(p_text);
	}

	// スペースキーでリザルトシーンへ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		GameManager& mgr = GameManager::GetInstance();
		mgr.reserveScene(GameManager::eScene::Result);
	}
	
	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ゲームクリア演出
void SceneInGame::seqClearEnding() {
	
	if (sequence_->isStart()) {
		// "Congratulations" と "Press the space key" を表示
		ObjText* p_text = new ObjText();
		p_text->setString("Congratulations");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F });
		p_text->setFontSize(50);
		p_text->setColor(dxe::Colors::AliceBlue);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		addObject(p_text);

		p_text = new ObjText();
		p_text->setString("Press the space key");
		p_text->setPosition({ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F });
		p_text->setFontSize(20);
		p_text->setColor(dxe::Colors::AliceBlue);
		p_text->setLocation(dxe::eRectOrigin::CENTER);
		p_text->setEffectType(ObjText::eEffectType::Flashing);
		addObject(p_text);
	}

	// スペースキーでリザルトシーンへ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		GameManager& mgr = GameManager::GetInstance();
		mgr.reserveScene(GameManager::eScene::Result);
	}
	
	return ;
}

//--------------------------------------------------------------------------------------------------------------------------
// ボールとバーの衝突処理（反射方向の決定）
void SceneInGame::intersectProcessBarAndBall() {

	tnl::Vector2f bar_position = p_bar_->getPosition();
	tnl::Vector2f bar_size = p_bar_->getSize();
	tnl::Vector2f ball_position = p_ball_->getPosition();

	if (tnl::IsIntersectRect(bar_position, bar_size.x, bar_size.y,
		ball_position, p_ball_->getRadius(), p_ball_->getRadius())) {

		PlaySoundMem(sound_hdl_se_, DX_PLAYTYPE_BACK); // 効果音再生

		// 位置補正と衝突面の取得
		tnl::eCorrResRect n = tnl::CorrectPositionRect(
			bar_position,
			p_ball_->getBeforePosition(),
			p_bar_->getSize(),
			tnl::Vector2f(p_ball_->getRadius()),
			bar_position,
			ball_position,
			tnl::eCorrTypeRect::PWRFL_A,
			tnl::eCorrTypeRect::PWRFL_A, 1.0f);

		// 衝突面に応じた反射
		if (n == tnl::eCorrResRect::LEFT)	p_ball_->reflection({ -1, 0 });
		if (n == tnl::eCorrResRect::RIGHT)	p_ball_->reflection({ 1, 0 });
		if (n == tnl::eCorrResRect::UP)		p_ball_->reflection({ 0, 1 });
		if (n == tnl::eCorrResRect::DOWN)	p_ball_->reflection({ 0, -1 });

		p_ball_->setPosition(ball_position); // 修正位置を反映
	}
}

//--------------------------------------------------------------------------------------------------------------------------
// ボールとブロックの衝突処理（破壊と反射）
void SceneInGame::intersectProcessBallAndBlock() {

	tnl::Vector2f ball_position = p_ball_->getPosition();

	auto it = blocks_.begin();
	while (it != blocks_.end()) {

		ObjBlock* block = (*it);
		tnl::Vector2f block_position = block->getPosition();
		tnl::Vector2f block_size = block->getSize();

		// 衝突していないなら次へ
		if (!tnl::IsIntersectRect(block_position, block_size.x, block_size.y,
			ball_position, p_ball_->getRadius(), p_ball_->getRadius())) {
			it++;
			continue;
		}

		PlaySoundMem(sound_hdl_se_, DX_PLAYTYPE_BACK); // 効果音再生

		// 衝突面と補正処理
		tnl::eCorrResRect n = tnl::CorrectPositionRect(
			block_position,
			p_ball_->getBeforePosition(),
			block_size,
			tnl::Vector2f(p_ball_->getRadius()),
			block_position,
			ball_position,
			tnl::eCorrTypeRect::PWRFL_A,
			tnl::eCorrTypeRect::PWRFL_A, 1.0f);

		block->setAlive(false); // ブロック破壊

		// 衝突面に応じた反射処理
		if (n == tnl::eCorrResRect::LEFT)	p_ball_->reflection({ -1, 0 });
		if (n == tnl::eCorrResRect::RIGHT)	p_ball_->reflection({ 1, 0 });
		if (n == tnl::eCorrResRect::UP)		p_ball_->reflection({ 0, 1 });
		if (n == tnl::eCorrResRect::DOWN)	p_ball_->reflection({ 0, -1 });

		p_ball_->setPosition(ball_position); // 修正位置を反映
		it = blocks_.erase(it); // リストから削除
	}
}

//--------------------------------------------------------------------------------------------------------------------------
// ボールとウィンドウ端の当たり判定と反射処理
void SceneInGame::intersectProcessWindowFrame() {
	bool is_reflection = false;

	// 上端との衝突
	if (p_ball_->getPosition().y < (p_ball_->getRadius() * 0.5f)) {
		p_ball_->reflection({ 0.0f, 1.0f });
		is_reflection = true;
	}

	// 左端との衝突
	if (p_ball_->getPosition().x < (p_ball_->getRadius() * 0.5f)) {
		p_ball_->reflection({ 1.0f, 0.0f });
		is_reflection = true;
	}

	// 右端との衝突
	if (p_ball_->getPosition().x > (DXE_WINDOW_WIDTH_F - (p_ball_->getRadius() * 0.5f))) {
		p_ball_->reflection({ -1.0f, 0.0f });
		is_reflection = true;
	}

	// 反射が起きた場合は効果音を再生
	if (is_reflection) {
		PlaySoundMem(sound_hdl_se_, DX_PLAYTYPE_BACK);
	}
}