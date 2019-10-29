//=============================================================================
//
// 弾処理 [bullet.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(1024)						// 弾の最大数
#define BULLET_SIZE		(9)							//弾のサイズ

#define BULLET_TEXTURE "data/TEXTURE/bullet000.png"	//弾のテクスチャ

#define MAX_BULLET_LIFE (300)						//弾の寿命

#define BULLET_COEFFICIENT (0.4f)					//弾角度の係数
//*****************************************************************************
// 構造体定義
//*****************************************************************************
//状態列挙
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//自分
	BULLETTYPE_ENEMY,		//敵
	BULLETTYPE_ENEMY_HOMING,//敵追尾弾
	BULLETTYPE_BOSS,		//ボス
	BULLETTYPE_BOSS_OPTION,	//ボスのオプション
	BULLETTYPE_MAX
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	BULLETTYPE type;
	D3DXCOLOR col;
	float fAngle;
	int nLife;
	bool bUse;
}Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type,D3DXCOLOR col ,float angle);
Bullet *GetBullet(void);
void BulletErese(void);
#endif
