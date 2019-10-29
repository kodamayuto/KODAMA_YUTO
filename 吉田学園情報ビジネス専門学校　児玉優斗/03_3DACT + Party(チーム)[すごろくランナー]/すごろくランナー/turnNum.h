//=============================================================================
//
// ターン数処理 [turnNum.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _TURN_H_
#define _TURN_H_

#include "main.h"

//*****************************************************************************
// ターン数の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3  pos;          // 位置
	float        Width;        // 幅
	float        Height;       // 高さ
	int          nScore;       // スコア
	int          TexturePos;   // テクスチャ座標
	int          NumScore;     // スコアの桁数
}TurnNum;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTurnNum(void);
void UninitTurnNum(void);
void UpdateTurnNum(void);
void DrawTurnNum(void);
void AddTurnNum(int nValue);
int GetTurnNum(void);

#endif