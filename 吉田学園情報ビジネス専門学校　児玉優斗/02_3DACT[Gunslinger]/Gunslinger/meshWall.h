//=============================================================================
//
// ポリゴン処理 [meshWall.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;	  //位置
	D3DXVECTOR3 rot;	  //方向
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	bool bUse;
	int nNumVertex;	//頂点数
	int nNumIndex;	//インデックス数
	int nNumPolygon;//ポリゴン数
	D3DXVECTOR3 aPos;//判定用座標//先
	D3DXVECTOR3 bPos;//判定用座標//元
	int nMeshBlockWidth;//メッシュの横分割
	int nMeshBlockHaight;//メッシュの縦分割
	float fMeshSizeW;//壁の幅
	float fMeshSizeH;//壁の高さ
}MESHWALL;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

bool CollisionMeshWall(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld);
void SetMeshWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
#endif
