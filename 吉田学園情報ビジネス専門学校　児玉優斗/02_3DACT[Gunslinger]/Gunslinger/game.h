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

#include "model.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "explosion.h"
#include "meshField.h"
#include "meshWall.h"
#include "meshCylinder.h"
#include "effect.h"
#include "player.h"
#include "npc.h"
#include "particle.h"
#include "arrow.h"
#include "Timer.h"
#include "piller.h"
#include "roof.h"
#include "object.h"
#include "miniMap.h"
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
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

void PauseModeChange(void);
#endif
