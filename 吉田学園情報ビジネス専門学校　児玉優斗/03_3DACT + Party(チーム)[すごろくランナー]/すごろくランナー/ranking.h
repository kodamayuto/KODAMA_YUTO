//=============================================================================
//
// ランキング画面 [ranking.h]
// Author : 高橋美優
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MODEL	(10)		// モデルの最大数

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMesh;			// メッシュ情報へのポインタ(頂点情報)
	LPD3DXBUFFER pBuffMat;		// マテリアル情報へのポインタ(色)
	DWORD nNumMat;				// マテリアル情報の数
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	int nIdxModelParent;		// 親モデルのインデックス
}RankingModel;

typedef enum
{
	RANKINGOLD_TITLE = 0,
	RANKINGOLD_SELECT,
	RANKINGOLD_MAX
} RankingOld;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRankingOld(RankingOld ranking);

#endif