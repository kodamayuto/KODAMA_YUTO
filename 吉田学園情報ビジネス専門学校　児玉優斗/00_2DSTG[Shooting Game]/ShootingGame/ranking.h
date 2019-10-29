#pragma once
//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "game.h"
#include "score.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_RANKING_00	"data/TEXTURE/bg100.png"
#define TEXTURE_RANKING_01	"data/TEXTURE/bg101.png"
#define TEXTURE_RANKING_02	"data/TEXTURE/bg102.png"
#define TEXTURE_RANKING_03	"data/TEXTURE/HighScore.png"
#define	TEXTURE_RANKING_04	"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RANKING_05	"data/TEXTURE/press_enter.png"	// 読み込むテクスチャファイル名

#define MAX_RANKING_DIGIT (10)									//桁数
#define MAX_RANKING_TEXTURE (6)
#define RANKING_SIZE      (30.0f)								//スコアの大きさ

#define RANKING_POS_X (400)									//スコアのX軸
#define RANKING_POS_Y (370)									//スコアのY軸

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRankScore(int nScore);

void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

#endif
