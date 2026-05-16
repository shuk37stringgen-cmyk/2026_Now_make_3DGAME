#include "GameManager.h" // ‚±‚ê‚ğˆê”Ôã‚É’Ç‰ÁI[cite: 3]
#include "gm_main.h"

GameManager g_manager; //[cite: 4]
void gameStart() { g_manager.init(); }
void gameMain(float dt) { g_manager.update(dt); g_manager.render(); }
void gameEnd() { g_manager.end(); }