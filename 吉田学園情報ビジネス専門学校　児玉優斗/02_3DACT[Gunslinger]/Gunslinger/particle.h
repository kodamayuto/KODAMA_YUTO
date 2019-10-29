//=============================================================================
//
// 爆発エフェクト処理[particle.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//角度
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//色
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	float fWidth;	//幅
	float Haight;	//奥行
	bool bUse;		//使用の可否
	int nLife;		//弾の表示時間
}PARTICLE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col,float fWidth ,float haight);
#endif
