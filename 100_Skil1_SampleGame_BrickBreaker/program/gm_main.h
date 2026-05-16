#pragma once

enum {
	SCENE_TITLE_INIT,
	SCENE_TITLE,
	SCENE_IN_GAME_INIT,
	SCENE_IN_GAME,
	SCENE_RESULT_INIT,
	SCENE_RESULT
};

void gameStart();
void gameMain( float delta_time );
void gameEnd();
