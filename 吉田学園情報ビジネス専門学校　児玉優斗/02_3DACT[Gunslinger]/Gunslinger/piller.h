//=============================================================================
//
// モデル処理 [piller.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PILLER_H_
#define _PILLER_H_

#include "main.h"
//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
	D3DXVECTOR3 VtxMin;	//モデルの当たり判定の最小
	D3DXVECTOR3 VtxMax;	//モデルの当たり判定の最大
	DWORD NumMatModel;	//マテリアル情報の数
}PILLER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPiller(void);
void UninitPiller(void);
void UpdatePiller(void);
void DrawPiller(void);

bool CollisionPiller(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);


void SetPillerVertex(int nCntModel);
void SetPiller(D3DXVECTOR3 pos);

PILLER *GetPiller(void);
#endif
