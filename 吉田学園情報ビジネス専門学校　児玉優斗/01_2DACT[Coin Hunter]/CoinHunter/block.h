//=============================================================================
//
// ブロックの処理 [block.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
//=============================================================================
//	マクロ定義
//=============================================================================
// 読み込むテクスチャファイル名
#define	TEXTURE_BLOCK		"data/TEXTURE/block000.jpg"
#define TEXTURE_BLOCK_1		"data/TEXTURE/block001.jpg"
#define TEXTURE_BLOCK_2		"data/TEXTURE/block002.jpg"
#define TEXTURE_BLOCK_3		"data/TEXTURE/block003.jpg"
#define TEXTURE_BLOCK_4		"data/TEXTURE/Tile001.png"
#define TEXTURE_BLOCK_5		"data/TEXTURE/block005.jpg"
#define TEXTURE_BLOCK_6		"data/TEXTURE/block006.jpg"
#define TEXTURE_BLOCK_7		"data/TEXTURE/rESET.png"

#define	MAX_BLOCK			(512)							// ブロックの最大数

#define MAX_BLOCK_TEXTURE	(8)

#define BLOCK_INV_SPEED (0.015f)	//ブロックの消える速度

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	BLOCKTYPE_NORMAL = 0, //通常
	BLOCKTYPE_MOVE,		  //動く
	BLOCKTYPE_FALL,		  //乗ると落ちる
	BLOCKTYPE_INV,		  //乗ると消える
	BLOCKTYPE_ATTACK_MOVE,//たたくと動く
	BLOCKTYPE_WARP_IN,	  //乗るとOUTまでワープする
	BLOCKTYPE_WARP_OUT,
	BLOCKTYPE_RESET,	  //AttckMoveの移動量をリセットする
	BLOCKTYPE_MAX
}BLOCKTYPE;

typedef enum
{
	BLOCKCONTACT_NONE = 0,//接触していない
	BLOCKCONTACT_ON,	  //上に接触している
	BLOCKCONTACT_UNDER,	  //下に接触している
	BLOCKCONTACT_LEFT,	  //左に接触している
	BLOCKCONTACT_RIGHT,	  //下に接触している
	BLOCKCONTACT_MAX
}BLOCKCONTACT;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 OldPos;		// 元の位置
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// カラー
	float fWidth;			// 幅
	float fHeight;			// 高さ
	bool bUse;				// 使用しているかどうか
	bool bFlag;
	int nWarpCount;
	BLOCKTYPE type;
	BLOCKCONTACT ContBlock;
} Block;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	float fWidth;
	float fHeight;
	BLOCKTYPE type;
}BlockInfo;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);

void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth,float fHeight, BLOCKTYPE type);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldPos, D3DXVECTOR3 *pMove);
int ReturnBlockIndex(int nIndex);
void ResetAttackMoveBlock(void);
#endif
