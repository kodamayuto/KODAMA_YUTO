//=============================================================================
//
// ボス処理 [boss_option.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BOSS_OPTION_H_
#define _BOSS_OPTION_H_

#include "main.h"
#include"game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define BOSS_OPTION_TEXTURE "data/TEXTURE/Draw005Fryer1.png"

#define BOSS_OPTION_POLYGON_SIZE (20)

#define BOSS_OPTION_COLOR_RED (255)
#define BOSS_OPTION_COLOR_GREEN (255)
#define BOSS_OPTION_COLOR_BLUE (255)
#define BOSS_OPTION_COLOR_ALPHA (255)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	bool bUse;				//使用の可否
	int nCounterBullet;		//敵の弾処理用
}BOSS_OPTION;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBossOption(void);
void UninitBossOption(void);
void UpdateBossOption(void);
void DrawBossOption(void);
void SetBossOption(D3DXVECTOR3 pos,D3DXVECTOR3 move);

#endif
