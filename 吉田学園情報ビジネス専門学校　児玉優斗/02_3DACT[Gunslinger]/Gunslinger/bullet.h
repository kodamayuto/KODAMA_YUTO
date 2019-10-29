//=============================================================================
//
// 弾処理[bullet.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	BULLETTYPE_NONE = 0,
	BULLETTYPE_PLAYER,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 Oldpos;	//旧位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//角度
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	float fWidth;	//幅
	float Haight;	//奥行
	bool bUse;		//使用の可否
	int nIdxShadow;	//影のインデックス
	int nLife;		//弾の表示時間
	int nDeleteIdxNpc; //消すnpcのインデックス
	BULLETTYPE type;	//弾の属性
}BULLET;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move,float fWidth ,float haight, BULLETTYPE type);
void BulletErese(void);
#endif
