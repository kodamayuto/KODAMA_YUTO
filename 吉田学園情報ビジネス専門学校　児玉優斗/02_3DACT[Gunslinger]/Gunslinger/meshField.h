//=============================================================================
//
// ポリゴン処理 [meshField.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;	  //位置
	D3DXVECTOR3 rot;	  //方向
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	float fWidth;	//幅
	float fDepth;	//奥行
	bool bUse;
	int nNumVertex;	//頂点数
	int nNumIndex;	//インデックス数
	int nNumPolygon;//ポリゴン数
}MESHFIELD;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
#endif
