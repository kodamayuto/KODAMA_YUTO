//=============================================================================
//
// 影処理[shadow.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorldShadow;
	bool bUse;
}Shadow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int  SetShadow(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetSizeShadow(int nIdxShadow, float posY ,float Size);
void DeleteShadow(int nIdxShadow);
#endif
