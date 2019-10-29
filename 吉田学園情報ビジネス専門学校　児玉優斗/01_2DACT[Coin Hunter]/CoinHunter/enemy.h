//=============================================================================
//
// 敵処理 [enemy.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(256)	// 敵の最大数

#define ENEMY_TEXTURE_00 "data/TEXTURE/Draw006Enemy1.png"
#define ENEMY_TEXTURE_01 "data/TEXTURE/Draw005Fryer2.png"

#define ENEMY_POLYGON_SIZE (30)

#define ENEMY_COLOR_RED (255)
#define ENEMY_COLOR_GREEN (255)
#define ENEMY_COLOR_BLUE (255)
#define ENEMY_COLOR_ALPHA (255)

#define	MAX_TYPE_ENEMY		(2)						// 敵の種類

//*****************************************************************************
// 構造体定義
//*****************************************************************************
//状態列挙
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常
	ENEMYSTATE_DAMAGE,		//ダメージ
	ENEMYSTATE_MAX			
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nType;				//敵のタイプ
	bool bUse;				//使用の可否
	int nLife;				//体力
	ENEMYSTATE state;		//敵の状態
	int nCounterState;		//状態管理用カウンター
	bool bDirection;		//向き		false == 右
}ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nType);
ENEMY *GetEnemy(void);
int GetNumEnemy(void);
void HitEnemy(int nCntEnemy,int nDamage);
void DebugEnemyLifeDown(void);

#endif
