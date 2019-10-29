//=============================================================================
//
// 爆発エフェクト処理[effect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//角度
	D3DXCOLOR col;		//色
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	float fWidth;	//幅
	float Haight;	//奥行
	bool bUse;		//使用の可否
	int nLife;		//弾の表示時間
}EFFECT;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col,float fWidth ,float haight);
#endif
