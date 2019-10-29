//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
// ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0,   // 何もしていない状態
	GAMESTATE_NONE_RETRY, // 何もしていない状態(リトライ)
	GAMESTATE_NORMAL,     // 通常(プレイ)状態
	GAMESTATE_RETRY,      // やり直し状態
	GAMESTATE_CLEAR,
	GAMESTATE_OVER,
	GAMESTATE_MAX
}GAMESTATE;

typedef enum
{
	TURNSTATE_NONE,				//初期状態
	TURNSTATE_DICE,				//ダイスを振れる時間
	TURNSTATE_MAP,				//マップ確認の時間
	TURNSTATE_COUNTDOWN,		//ダイス振り後の待ち時間
	TURNSTATE_MOVEandATTACK,	//移動and妨害ができる時間
	TURNSTATE_ABILITY,			//マスの能力増減処理の時間
	TURNSTATE_END,				//ターン終了し、次の人に代わるまでの時間
	TURNSTATE_MAX
}TURNSTATE;

//***************************************************************************** 
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

void SetTurnState(TURNSTATE Tstate);
TURNSTATE GetTurnState(void);

#endif