//=============================================================================
//
// ポリゴン処理 [meshCylinder.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

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
	D3DXCOLOR col;	//色
}MESHCYLINDER;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
#endif
