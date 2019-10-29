//=============================================================================
//
// アイテム処理 [item.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM		(256)						//アイテムの最大数

#define ITEM_TEXTURE "data/TEXTURE/coin000.png"		//アイテムのテクスチャ
#define NUM_TEXTURE (1)
#define ITEM_SIZE (20)

#define TEX_PATTERN (4)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	ITEM_SCOREUP_COIN = 0,//コイン
	ITEM_GROWUP_POTION,	  //成長薬
	ITEM_MAX
}ITEM_PROPERTY;//アイテムの属性

typedef struct
{
	D3DXVECTOR3 pos;	   //位置
	D3DXCOLOR col;		   //色
	float fWidth;		   //幅
	float fHeight;		   //高さ
	int nScore;			   //スコア
	float fAngle;		   //回転角
	float fLength;		   //長さ
	int nCounterAnim;	   //カウンター	
	int nPatternAnim;	   //テクスチャのアニメーション
	bool bUse;			   //使用しているか		false == 使ってない
	bool bDisp;			   //見えているか
	bool bDeleteFlag;	   //取られたか			false == 取られてない
	ITEM_PROPERTY Property;//アイテムの属性
}ITEM;//アイテムの構造体

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos,D3DXCOLOR col,int Score,ITEM_PROPERTY Property);

ITEM *GetItem(void);
int GetNumCoin(void);
void NumCoinReduce(void);

#endif
