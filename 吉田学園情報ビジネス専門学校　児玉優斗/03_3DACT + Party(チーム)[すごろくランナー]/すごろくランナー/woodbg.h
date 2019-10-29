//=============================================================================
//
// 背景の木の処理 [woodBG.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _WOODBG_H_
#define _WOODBG_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	WOODBG_TYPE_PALM,
	WOODBG_TYPE_LAKE,
	WOODBG_TYPE_MAX,
}WOODBG_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;	              // 位置
	D3DXVECTOR3 rot;	              // 向き
	D3DXVECTOR3 move;	              // 移動量
	int			nInxShadow;           // 影
	WOODBG_TYPE	nType;            // 種類
	D3DXMATRIX	mtxWorld;	          // ワールドマトリックス
	bool		bUse;                 // 使用しているかどうか
	D3DXVECTOR3	vtxMinWoodBG, vtxMaxWoodBG;	// モデルの最小値、最大値
}WOODBG;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;        // 向き
	D3DXVECTOR3 move;		// 移動量
	WOODBG_TYPE nType;	// 種類
}WOODBG_INFO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitWoodBG(void);
void UninitWoodBG(void);
void UpdateWoodBG(void);
void DrawWoodBG(void);
WOODBG *GetWoodBG(void);
void SetWoodBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, WOODBG_TYPE nType);
//bool CollisionWoodBG(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif
