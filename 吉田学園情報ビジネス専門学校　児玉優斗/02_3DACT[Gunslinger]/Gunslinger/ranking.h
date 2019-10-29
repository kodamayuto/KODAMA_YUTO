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
//#include "score.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define	TEXTURE_RANKING_01	"data/TEXTURE/press_enter.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RANKING_02	"data/TEXTURE/HighScore.png"	// 読み込むテクスチャファイル名

#define MAX_RANKING_DIGIT (10)									//桁数
#define MAX_RANKING_TEXTURE (2)
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

void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);
void SetRankScore(int nScore);
#endif
