//=============================================================================
//
// ビルボードの処理 [billboard.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _BILLBORAD_H_
#define _BILLBORAD_H_

#include "main.h"

//*****************************************************************************
// ビルボードの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3   pos;              // 位置(中心)
	D3DXVECTOR3   move;             // 移動量
	D3DXVECTOR3   rot;              // 向き
	D3DXMATRIX    mtxWorld;         // ワールドマトリックス
	float         fWidth;           // 幅
	float         fHeight;          // 高さ
	int           nIdxShadow;       // 使用している影の番号
	bool          bUse;             // 使用しているかどうか
}Billboard;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;        // 向き
	float       fWidth;     // 幅
	float       fHeight;    // 高さ
} BILLBOARD_INFO;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define  MAX_BILLBOARD   (256)         // ビルボードの総数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float width, float height);
bool CollisionBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 radius);
Billboard *GetBillboard(void);

#endif
