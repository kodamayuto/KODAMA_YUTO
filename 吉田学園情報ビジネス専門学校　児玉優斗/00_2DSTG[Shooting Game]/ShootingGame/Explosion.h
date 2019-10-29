//=============================================================================
//
// 爆発処理 [Explosion.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_EXPLOSION		(MAX_BULLET)						//爆発の最大数
#define EXPLOSION_SIZE		(BULLET_SIZE * 3.5f)				//爆発のサイズ

#define EXPLOSION_TEXTURE "data/TEXTURE/explosion000.png"		//爆発のテクスチャ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col);

#endif
