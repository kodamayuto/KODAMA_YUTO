//=============================================================================
//
// モデル処理 [island.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ISLAND_H_
#define _ISLAND_H_

#include "main.h"
//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMove;
	D3DXVECTOR3 difPos;
	D3DXVECTOR3 difAngle;
	D3DXMATRIX  mtxWorld;
	DWORD nNumMatISLAND = 0;		//マテリアル情報の数
	bool bUse;
	LPCSTR filename;
}ISLAND;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitIsland(void);
void UninitIsland(void);
void UpdateIsland(void);
void DrawIsland(void);

#endif
