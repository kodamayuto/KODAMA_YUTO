//=============================================================================
//
// マスの処理 [nasu.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _MASU_H_
#define _MASU_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
//*****************************************************************************
// ブロックの種類
//*****************************************************************************
typedef enum
{// ブロックの種類
	MASUTYPE_JUMP_UP = 0,   // ジャンプ力上昇マス
	MASUTYPE_JUMP_DOWN,     // ジャンプ力減少マス
	MASUTYPE_SPEED_UP,      // 移動力上昇マス
	MASUTYPE_SPEED_DOWN,    // 移動力減少マス
	MASUTYPE_DICE_TWICE,    // 2倍マス
	MASUTYPE_JUMP_RAMP,     // ジャンプ台マス
	MASUTYPE_NORMAL,		// 通常マス
	MASUTYPE_GOAL,			// ゴール
	MASUTYPE_START,			// スタート
	MASUTYPE_MAX
} MASUTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	                // 位置
	D3DXVECTOR3 rot;	                // 向き
	D3DXVECTOR3 move;	                // 移動量
	int			nInxShadow;             // 影の番号
	MASUTYPE	masuType;               // マスの種類
	D3DXVECTOR3	vtxMinMasu, vtxMaxMasu;	// モデルの最小値、最大値
	D3DXMATRIX	mtxWorld;			    // ワールドマトリックス
	bool		bUse;                   // 使用しているかどうか
} MASU;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMasu(void);
void UninitMasu(void);
void UpdateMasu(void);
void DrawMasu(void);
MASU *GetMasu(void);
void SetMasu(D3DXVECTOR3 pos, MASUTYPE Type);
bool CollisionMasu(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MASU **pMasu);

D3DXVECTOR3 PlayerDistance(void);
#endif