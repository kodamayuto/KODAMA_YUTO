#pragma once
//=============================================================================
//
// ゲームの処理 [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#include "Player.h"		//プレイヤーの処理
#include "bg.h"			//背景の処理
#include "enemy.h"		//敵キャラの処理
#include "block.h"		//ブロックの処理
#include "item.h"		//アイテムの処理
#include "score.h"		//スコアの処理
#include "time.h"		//制限時間の処理

//=============================================================================
//	マクロ定義
//=============================================================================
#define GRAVITY (0.7f)					//重力

//=============================================================================
//	ゲームの状態
//=============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,	//何もしてない状態
	GAMESTATE_NORMAL,	//通常状態
	GAMESTATE_END,		//終了状態
	GAMESTATE_MAX
}GAMESTATE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(int nNumStage);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void MakeStageSet(int nNumStage);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

void PauseModeChange(void);
#endif
