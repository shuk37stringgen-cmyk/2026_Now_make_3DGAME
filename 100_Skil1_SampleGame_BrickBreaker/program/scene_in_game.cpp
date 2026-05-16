#include "gm_main.h"
#include "scene_in_game.h"
#include "obj_ball.h"
#include "obj_bar.h"
#include "obj_block.h"

//--------------------------------------------------------------------------------------------------------------------------
//
// 定数宣言
//

// ゲーム内シーケンス（状態）の定義
enum {
	IN_GAME_SEQ_OPENING, // 開始前のカウントダウン
	IN_GAME_SEQ_PLAY,    // プレイ中
	IN_GAME_SEQ_ENDING,  // 結果表示中（クリア or ゲームオーバー）
	IN_GAME_SEQ_FINISH   // シーン終了
};

// ブロック配置数とサイズ
const int BLOCK_NUM_W = 10;       // 横に10個
const int BLOCK_NUM_H = 7;        // 縦に7個
const float BLOCK_SIZE_W = 80;    // ブロックの幅   ( block.png 画像の幅 )
const float BLOCK_SIZE_H = 36;    // ブロックの高さ ( block.png 画像の高さ )

// オープニングのカウントダウン時間（秒）
const float IN_GAME_OPENING_COUNT_DOWN_TIME = 3.0f;


//--------------------------------------------------------------------------------------------------------------------------
//
// グローバル変数宣言
//

std::string g_in_game_ending_message;               // ゲーム終了時に表示されるメッセージ
int g_in_game_remaining_block_num = BLOCK_NUM_W * BLOCK_NUM_H; // 残りブロック数
int g_in_game_sequence = IN_GAME_SEQ_OPENING;       // 現在のゲームシーケンス
float g_in_game_time_count = 0;                     // 経過時間
bool g_in_game_time_switch = true;                  // 点滅演出用フラグ（Ending時）

int g_in_game_img_block_hdl = 0;					// ブロックの画像ハンドル
int g_in_game_img_bar_hdl = 0;						// バーの画像ハンドル

int g_in_game_sound_hdl_se = 0;						// ボールが跳ね返るSEのハンドル

Ball  g_ball;                                        // ボールオブジェクト
Bar   g_bar;                                         // バー（パドル）オブジェクト
Block g_blocks[BLOCK_NUM_H][BLOCK_NUM_W];			// ブロック群


//--------------------------------------------------------------------------------------------------------------------------
//
// 関数プロトタイプ宣言
//
void sceneInGameLogic();                             // ゲームロジック制御
void sceneInGameDraw();                              // 描画処理
int seqInGameOpening();                              // 開始演出処理
int seqInGamePlay();                                 // プレイ中処理
int seqInGameEnding();                               // 終了待機処理
void intersectProcessBarAndBall(Bar& bar, Ball& ball);            // ボールとバーの衝突処理
void intersectProcessBallAndBlock(Ball& ball, Block& block);      // ボールとブロックの衝突処理
void intersectProcessWindowFrame(Ball& ball);					  // ボールとウインドウ枠の衝突処理


//--------------------------------------------------------------------------------------------------------------------------
void sceneInGameInitialize() {
	// 各種初期化


	// 画像のロード
	g_in_game_img_block_hdl = LoadGraph("resource/graphics/block.png");
	g_in_game_img_bar_hdl = LoadGraph("resource/graphics/bar.png");

	// サウンドデータのロード
	g_in_game_sound_hdl_se = LoadSoundMem("resource/sound/example/se_sample_0.mp3");
	SetVolumeSoundMem(8500, g_in_game_sound_hdl_se);

	// 残りブロック数の設定 ( この値が 0 になるとクリア )
	g_in_game_remaining_block_num = BLOCK_NUM_W * BLOCK_NUM_H;

	// 開始演出から始まるように設定
	g_in_game_sequence = IN_GAME_SEQ_OPENING;

	// ボールとブロックの初期設定
	g_ball.initialize();
	g_bar.initialize(g_in_game_img_bar_hdl);

	// ブロックの配置（左上から横→縦に並べる）
	float sx = 290;
	float sy = 100;
	for (int i = 0; i < BLOCK_NUM_H; ++i) {
		for (int k = 0; k < BLOCK_NUM_W; ++k) {
			g_blocks[i][k].initialize(
				{ sx + k * BLOCK_SIZE_W, sy + i * BLOCK_SIZE_H }
				, { BLOCK_SIZE_W, BLOCK_SIZE_H }
				, g_in_game_img_block_hdl );
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------
int sceneInGameProcess() {
	// 毎フレーム呼ばれる処理

	sceneInGameLogic(); // ロジック更新
	sceneInGameDraw();  // 描画

	// 終了シーケンスに入っていたらシーン切り替え指示
	if (IN_GAME_SEQ_FINISH == g_in_game_sequence) {
		return SCENE_RESULT_INIT;
	}

	return SCENE_IN_GAME;
}

//--------------------------------------------------------------------------------------------------------------------------
void sceneInGameLogic() {
	// 現在のシーケンスに応じて処理を分岐
	switch (g_in_game_sequence) {
	case IN_GAME_SEQ_OPENING:
		g_in_game_sequence = seqInGameOpening();
		break;
	case IN_GAME_SEQ_PLAY:
		g_in_game_sequence = seqInGamePlay();
		break;
	case IN_GAME_SEQ_ENDING:
		g_in_game_sequence = seqInGameEnding();
		break;
	}
}

//--------------------------------------------------------------------------------------------------------------------------
void sceneInGameDraw() {
	// オブジェクトの描画

	g_ball.draw();
	g_bar.draw();

	// 生きているブロックのみ描画
	for (int i = 0; i < BLOCK_NUM_H; ++i) {
		for (int k = 0; k < BLOCK_NUM_W; ++k) {
			if (!g_blocks[i][k].is_alive_) continue;
			g_blocks[i][k].draw();
		}
	}

	// オープニング：カウントダウン表示
	if (IN_GAME_SEQ_OPENING == g_in_game_sequence) {
		SetFontSize(50);
		dxe::DrawString(
			{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F },
			dxe::Colors::AliceBlue,
			dxe::eRectOrigin::CENTER,
			"%d", (int)((IN_GAME_OPENING_COUNT_DOWN_TIME + 1.0f) - g_in_game_time_count));
	}

	// エンディング：結果メッセージ表示
	if (IN_GAME_SEQ_ENDING == g_in_game_sequence) {
		SetFontSize(40);
		dxe::DrawString(
			{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F },
			dxe::Colors::AliceBlue,
			dxe::eRectOrigin::CENTER,
			"%s", g_in_game_ending_message.c_str());

		// 点滅メッセージ
		if (g_in_game_time_switch) {
			SetFontSize(20);
			dxe::DrawString(
				{ DXE_WINDOW_WIDTH_HALF_F, DXE_WINDOW_HEIGHT_HALF_F + DXE_WINDOW_HEIGHT_QUARTER_F },
				dxe::Colors::AliceBlue,
				dxe::eRectOrigin::CENTER,
				"Press the space key");
		}
	}

	// 操作ヘルプ表示
	SetFontSize(20);
	DrawFormatString(0, 0, dxe::Colors::AliceBlue, " Left  Move [ A ] ");
	DrawFormatString(0, 20, dxe::Colors::AliceBlue, " Right Move [ D ] ");
}

//--------------------------------------------------------------------------------------------------------------------------
int seqInGameOpening() {
	// オープニングの時間カウント
	g_in_game_time_count += dxe::GetDeltaTime();

	if (g_in_game_time_count > IN_GAME_OPENING_COUNT_DOWN_TIME) {
		return IN_GAME_SEQ_PLAY;
	}

	return IN_GAME_SEQ_OPENING;
}

//--------------------------------------------------------------------------------------------------------------------------
int seqInGamePlay() {
	// メインプレイ処理

	g_ball.update();
	g_bar.update();

	// ブロックの更新
	for (int i = 0; i < BLOCK_NUM_H; ++i) {
		for (int k = 0; k < BLOCK_NUM_W; ++k) {
			if (!g_blocks[i][k].is_alive_) continue;
			g_blocks[i][k].update();
		}
	}

	// 衝突判定
	intersectProcessBarAndBall(g_bar, g_ball);

	for (int i = 0; i < BLOCK_NUM_H; ++i) {
		for (int k = 0; k < BLOCK_NUM_W; ++k) {
			if (!g_blocks[i][k].is_alive_) continue;
			intersectProcessBallAndBlock(g_ball, g_blocks[i][k]);
		}
	}

	intersectProcessWindowFrame(g_ball);


	// ゲームクリア判定
	if (g_in_game_remaining_block_num <= 0) {
		g_in_game_time_count = 0;
		g_in_game_ending_message = "Congratulations";
		return IN_GAME_SEQ_ENDING;
	}

	// ゲームオーバー判定（ボールが画面下に落下）
	if (g_ball.position_.y > DXE_WINDOW_HEIGHT_F) {
		g_in_game_time_count = 0;
		g_in_game_ending_message = "Game Over";
		return IN_GAME_SEQ_ENDING;
	}

	// デバッグ用：Zキーで強制クリア
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		for (int i = 0; i < BLOCK_NUM_H; ++i) {
			for (int k = 0; k < BLOCK_NUM_W; ++k) {
				g_blocks[i][k].is_alive_ = false;
				g_in_game_remaining_block_num = 0;
			}
		}
	}

	return IN_GAME_SEQ_PLAY;
}

//--------------------------------------------------------------------------------------------------------------------------
int seqInGameEnding() {
	// エンディング（結果表示）処理

	// 点滅用の時間管理
	g_in_game_time_count += dxe::GetDeltaTime();
	if (g_in_game_time_count > 0.5f) {
		g_in_game_time_count = 0;
		g_in_game_time_switch = !g_in_game_time_switch;
	}

	// スペースキーで次のシーンへ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {

		// InGame用にロードした画像を解放
		DeleteGraph(g_in_game_img_block_hdl);
		DeleteGraph(g_in_game_img_bar_hdl);

		// ロードしたサウンドを解放
		DeleteSoundMem(g_in_game_sound_hdl_se);

		return IN_GAME_SEQ_FINISH;
	}

	return IN_GAME_SEQ_ENDING;
}

//--------------------------------------------------------------------------------------------------------------------------
void intersectProcessBarAndBall(Bar& bar, Ball& ball) {
	// ボールとバーの当たり判定と反射処理

	// 衝突判定
	if (tnl::IsIntersectRect(bar.position_, bar.size_.x, bar.size_.y,
		ball.position_, ball.radius_, ball.radius_)) {

		// SE 再生
		PlaySoundMem(g_in_game_sound_hdl_se, DX_PLAYTYPE_BACK);

		// ボールの座標を補正
		tnl::eCorrResRect n = tnl::EasyCorrectPositionRect(ball.position_, tnl::Vector2f(ball.radius_), bar.position_, bar.size_);

		// 衝突面に応じて反射方向を変更
		if (n == tnl::eCorrResRect::LEFT || n == tnl::eCorrResRect::RIGHT) ball.move_dir_.x = -ball.move_dir_.x;
		if (n == tnl::eCorrResRect::UP || n == tnl::eCorrResRect::DOWN) ball.move_dir_.y = -ball.move_dir_.y;
	}
}

//--------------------------------------------------------------------------------------------------------------------------
void intersectProcessBallAndBlock(Ball& ball, Block& block) {
	// ボールとブロックの当たり判定とブロック破壊処理

	if (tnl::IsIntersectRect(block.position_, block.size_.x, block.size_.y,
		ball.position_, ball.radius_, ball.radius_)) {

		// SE 再生
		PlaySoundMem(g_in_game_sound_hdl_se, DX_PLAYTYPE_BACK);

		// ボールの座標を補正
		tnl::eCorrResRect n = tnl::EasyCorrectPositionRect(ball.position_, tnl::Vector2f(ball.radius_), block.position_, block.size_, 1.0f);

		// ブロック破壊
		block.is_alive_ = false;
		g_in_game_remaining_block_num--;

		// 衝突面に応じて反射方向を変更
		if (n == tnl::eCorrResRect::LEFT || n == tnl::eCorrResRect::RIGHT) ball.move_dir_.x = -ball.move_dir_.x;
		if (n == tnl::eCorrResRect::UP || n == tnl::eCorrResRect::DOWN) ball.move_dir_.y = -ball.move_dir_.y;
	}
}


//--------------------------------------------------------------------------------------------------------------------------
void intersectProcessWindowFrame(Ball& ball) {

	bool is_reflection = false;

	// 上端に当たったら上下方向を反転（跳ね返る）
	if (ball.position_.y < (ball.radius_ * 0.5f)) {
		ball.move_dir_.y = -ball.move_dir_.y;
		is_reflection = true;
	}

	// 左端に当たったら左右方向を反転
	if (ball.position_.x < (ball.radius_ * 0.5f)) {
		ball.move_dir_.x = -ball.move_dir_.x;
		is_reflection = true;
	}

	// 右端に当たったら左右方向を反転
	if (ball.position_.x > (DXE_WINDOW_WIDTH_F - (ball.radius_ * 0.5f))) {
		ball.move_dir_.x = -ball.move_dir_.x;
		is_reflection = true;
	}

	if (is_reflection) {
		// SE 再生
		PlaySoundMem(g_in_game_sound_hdl_se, DX_PLAYTYPE_BACK);
	}

}

