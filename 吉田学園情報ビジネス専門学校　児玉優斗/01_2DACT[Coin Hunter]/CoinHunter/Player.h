#pragma once
//*****************************************************************************
//
//	DirectX プレイヤーの処理 [player.h]
//	Author : Kodama Yuto
//
//*****************************************************************************
#ifndef _PLAYER_H_	//二重インクルード防止のマクロ定義
#define _PLAYER_H_

#include "block.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define PLAYER_TEXTURE "data/TEXTURE/player000.png"	//プレイヤーの貼るテクスチャの名前

#define PLAYER_SIZE_X (20)						//プレイヤーのサイズ.X
#define PLAYER_SIZE_Y (20)						//プレイヤーのサイズ.Y

#define PLAYER_POS_X (150)						//プレイヤーの座標.X
#define PLAYER_POS_Y (650)						//プレイヤーの座標.Y

#define PLAYER_MOVE_SPEED (2.0f)				//プレイヤーのXの移動速度(デフォルト)
#define PLAYER_JUMPMOVE_SPEED (1.5f)			//プレイヤーのXの移動速度(ジャンプ中)

#define PLAYER_DASH_SPEED	  (1.2f)			//プレイヤーのダッシュ中に掛ける係数

#define PLAYER_MOVE_COEFFICIENT (0.3f)			//プレイヤーの減速係数
#define PLAYER_JUMP_MOVE (14.5f)				//プレイヤーのジャンプ力(デフォルト)			

#define PLAYER_COLOR_R (1.0f)				//プレイヤーの色.r
#define PLAYER_COLOR_G (1.0f)				//プレイヤーの色.g
#define PLAYER_COLOR_B (1.0f)				//プレイヤーの色.b
#define PLAYER_COLOR_A (1.0f)				//プレイヤーの色.a(α)

#define PLAYER_ANIM_INTERVAL (8)		//アニメーションの間隔

//=============================================================================
//	構造体の定義
//=============================================================================
typedef enum
{//プレイヤーの状態列挙
	PLAYERSTATE_NORMAL = 0,	//通常時
	PLAYERSTATE_MAX,
}PLAYERSTATE;

typedef struct
{//プレイヤーの構造体
	PLAYERSTATE state;		//状態
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 oldPos;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;
	int nTexAnim;			//テクスチャーのアニメーション
	int nCntAnim;			//アニメーション用のカウンター
	float fJump;			//ジャンプ力
	float fGravity;			//重力
	bool bDirection;		//向き				false == 右
	bool bUse;				//生きているか		false == 死
	bool bJump;				//飛んでいるか		false == 飛んでいない
	bool bLand;				//接地しているか	false == 接地してない
}Player;

//-----------------------------------------------------------------------------
//	プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void CollisionItem(void);

Player *GetPlayer(void);

#endif // !_PLAYER_H_

