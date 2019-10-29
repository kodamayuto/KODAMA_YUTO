//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	POLYGONTYPE_FIELD,
	POLYGONTYPE_MAX
}POLYGONTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	POLYGONTYPE type;
	float fWidth;	//幅
	float fDepth;	//奥行
	bool bUse;
}POLYGON;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot,POLYGONTYPE type, float fWidth ,float fDepth);
#endif
