//=============================================================================
//
// モデル処理 [model.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _DICE_H_
#define _DICE_H_

#include "main.h"
//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	DICEMOTION_NONE = 0,
	DICEMOTION_MOVE,
	DICEMOTION_THROW,
	DICEMOTION_STOP,
	DICEMOTION_MAX
}DICEMOTION;
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 oldPos;		//初期位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//回転角度
	D3DXVECTOR3 rotMove;	//回転量
	D3DXMATRIX  mtxWorld;	//モデルのマトリックス
	bool bUse;				//使用フラグ
	D3DXVECTOR3 VtxMin;		//モデルの当たり判定の最小
	D3DXVECTOR3 VtxMax;		//モデルの当たり判定の最大
	DWORD NumMatDice;		//マテリアル情報の数
	int nCntDiceMove;		//モデルの回転速度
	int nNumDice;			//サイコロの出目
	DICEMOTION DiceMotion;	//サイコロの状態
}DICE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDice(void);
void UninitDice(void);
void UpdateDice(void);
void DrawDice(void);

int  GetNumDice(void);	//ダイスの数字を取得
void SetDice(int nNumDice);
void DeleteDice(int nNumDice);

#endif
