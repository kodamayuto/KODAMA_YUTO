//=============================================================================
//
// 壁処理[wall.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	WALLTYPE_1,
	WALLTYPE_MAX
}WALLTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX g_mtxWorld;//ポリゴンのマトリックス
	WALLTYPE type;
	float fWidth;	//幅
	float Haight;	//奥行
	bool bUse;

	D3DXVECTOR3 aPos;
	D3DXVECTOR3 bPos;

}WALL;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,WALLTYPE type, float fWidth ,float haight);
bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);

#endif
