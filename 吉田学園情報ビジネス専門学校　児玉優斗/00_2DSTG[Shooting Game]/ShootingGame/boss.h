//=============================================================================
//
// ボス処理 [boss.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include"game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define BOSS_TEXTURE "data/TEXTURE/Draw005Fryer1.png"
#define BOSS_DAMAGE_TEXTURE "data/TEXTURE/Draw005Fryer1_damage.png"

#define BOSS_POLYGON_SIZE (60)

#define BOSS_COLOR_RED (255)
#define BOSS_COLOR_GREEN (255)
#define BOSS_COLOR_BLUE (255)
#define BOSS_COLOR_ALPHA (255)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//状態列挙
typedef enum
{
	BOSSSTATE_NORMAL = 0,	//通常
	BOSSSTATE_DAMAGE,		//ダメージ
	BOSSSTATE_DEATH,		//死
	BOSSSTATE_MAX
}BOSSSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	bool bUse;				//使用の可否
	int nLife;				//体力
	BOSSSTATE state;		//敵の状態
	int nCounterState;		//状態管理用カウンター
	int nCounterBullet;		//敵の弾処理用
}BOSS;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos,D3DXVECTOR3 move);
BOSS *GetBoss(void);
void HitBoss(int nDamage);

#endif
