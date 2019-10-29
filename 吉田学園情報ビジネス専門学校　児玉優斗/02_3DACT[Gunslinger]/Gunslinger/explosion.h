//=============================================================================
//
// 爆発エフェクト処理[explosion.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//角度
	D3DXCOLOR col;			//色
	D3DXMATRIX g_mtxWorld;	//ポリゴンのマトリックス
	float fWidth;			//幅
	float Haight;			//奥行
	bool bUse;				//使用の可否
	int nAnim;				//弾の表示時間 
	int nCntAnimation;		//アニメーションのカウント
}EXPLOSION;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col,float fWidth ,float haight);
#endif
