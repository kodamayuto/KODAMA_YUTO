//=============================================================================
//
// 操作キャラ処理 [player.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_FILENAME0 "data/MODEL/3d_001_body2.x"
#define PLAYER_FILENAME1 "data/MODEL/3d_001_head3.x"
#define PLAYER_FILENAME2 "data/MODEL/3d_001_armR1.x"
#define PLAYER_FILENAME3 "data/MODEL/3d_001_handR.x"
#define PLAYER_FILENAME4 "data/MODEL/3d_001_armL1.x"
#define PLAYER_FILENAME5 "data/MODEL/3d_001_handL.x"
#define PLAYER_FILENAME6 "data/MODEL/3d_001_legR1.x"
#define PLAYER_FILENAME7 "data/MODEL/3d_001_footR1.x"
#define PLAYER_FILENAME8 "data/MODEL/3d_001_legL1.x"
#define PLAYER_FILENAME9 "data/MODEL/3d_001_footL1.x"
#define PLAYER_FILENAME10 "data/MODEL/3d_001_Gun002.x"

#define PLAYER_MOVE_SPEED (0.17f)
#define PLAYER_ROTMOVE_COEFFICIENT (0.10f)
#define MAX_NUM_PLAYER (1)
#define PARTS_NUM_PLAYER (11)

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 motion0[2];
	int nKeyFrame;
}PLAYERMOTION;

typedef struct
{
	LPD3DXMESH pMesh = NULL;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat = NULL;//マテリアル情報へのポインタ
	DWORD		 nNumMat = 0;	//マテリアル情報の数
	D3DXMATRIX  mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nIdxModelParent;		//親モデルのインデックス
	LPCSTR FireName;
	PLAYERMOTION motion;
	int nMotionCount = 0;			//モーションの時間計測用
	int nMotionNum = 0;				//モーションの管理用
}PLAYERMODEL;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 OldPos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMove;
	D3DXVECTOR3 difPos;
	D3DXVECTOR3 difAngle;
	D3DXMATRIX  mtxWorld;
	int nIdxShadow;
	D3DXVECTOR3 VtxMin;	//モデルの当たり判定の最小
	D3DXVECTOR3 VtxMax;	//モデルの当たり判定の最大
	PLAYERMODEL aModel[PARTS_NUM_PLAYER];
	int nChargeTime;
	bool bUse;
}PLAYER;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

void SetPlayerVertex(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);

void DeletePlayer(void);
#endif
