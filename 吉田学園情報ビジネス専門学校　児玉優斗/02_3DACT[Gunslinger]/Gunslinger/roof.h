//=============================================================================
//
// 壁処理[roof.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ROOF_H_
#define _ROOF_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	ROOFTYPE_1,
	ROOFTYPE_MAX
}ROOFTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	ROOFTYPE type;
	float fWidth;	//幅
	float Haight;	//奥行
	bool bUse;
}ROOF;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRoof(void);
void UninitRoof(void);
void UpdateRoof(void);
void DrawRoof(void);
void SetRoof(D3DXVECTOR3 pos, D3DXVECTOR3 rot,ROOFTYPE type, float fWidth ,float haight);
#endif
