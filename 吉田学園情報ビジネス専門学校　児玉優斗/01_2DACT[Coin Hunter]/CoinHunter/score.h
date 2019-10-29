//=============================================================================
//
// スコア処理 [score.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number001.png"	// 読み込むテクスチャファイル名
#define TEXTURE_FRAME		"data/TEXTURE/waku.png"
#define MAX_SCORE_DIGIT (8)									//桁数
#define SCORE_SIZE      (20.0f)								//スコアの大きさ

#define SCORE_POS_X (800)									//スコアのX軸
#define SCORE_POS_Y (50)									//スコアのY軸

#define FRAME_INTERVAL (180)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

void OverStageScore(int nScore);
void ResetScore(void);
int GetScore(void);
#endif
