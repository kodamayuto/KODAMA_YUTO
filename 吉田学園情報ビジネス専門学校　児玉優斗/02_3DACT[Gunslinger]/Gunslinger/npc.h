//=============================================================================
//
// モデル処理 [npc.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _NPC_H_
#define _NPC_H_

#include "main.h"

//
//
//
#define NPC_FILENAME0 "data/MODEL/3d_001_body4.x"
#define NPC_FILENAME1 "data/MODEL/3d_001_head4.x"
#define NPC_FILENAME2 "data/MODEL/3d_001_armR1.x"
#define NPC_FILENAME3 "data/MODEL/3d_001_handR.x"
#define NPC_FILENAME4 "data/MODEL/3d_001_armL1.x"
#define NPC_FILENAME5 "data/MODEL/3d_001_handL.x"
#define NPC_FILENAME6 "data/MODEL/3d_001_legR2.x"
#define NPC_FILENAME7 "data/MODEL/3d_001_footR1.x"
#define NPC_FILENAME8 "data/MODEL/3d_001_legL2.x"
#define NPC_FILENAME9 "data/MODEL/3d_001_footL1.x"
#define NPC_FILENAME10 "data/MODEL/3d_001_Weppon_sword2.x"

#define PARTS_NUM_NPC (11)

#define NPC_MOVE_SPEED (1.95f)
#define NPC_ROTMOVE_COEFFICIENT (0.11f)
#define MAX_NUM_NPC (4)
#define CHASE_RANGE (100.0f)			//追跡範囲

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	AI_RANDOM = 0,//ランダム移動
	AI_CHASE,	  //追跡
	AI_TERRITORY, //領域内追跡
	AI_ESCAPE,	  //逃走
	AI_PATOROL,   //巡回
	AI_MAX
}NPC_AI;//NPCの行動アルゴリズム

typedef enum
{
	NPCSTATE_NONE = 0,
	NPCSTATE_MOVE,
	NPCSTATE_DAMAGE,
	NPCSTATE_MAX
}NPC_STATE;
typedef struct
{
	D3DXVECTOR3 motion0[2];
	int nKeyFrame;
}NPCMOTION;

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
	NPCMOTION motion;
	int nMotionCount = 0;			//モーションの時間計測用
	int nMotionNum = 0;				//モーションの管理用

}NPCMODEL;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMove;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 difAngle;
	D3DXMATRIX  mtxWorld;
	int nIdxShadow;
	DWORD nNumMatNPC = 0;		//マテリアル情報の数
	bool bUse;
	D3DXVECTOR3 VtxMin;	//モデルの当たり判定の最小
	D3DXVECTOR3 VtxMax;	//モデルの当たり判定の最大
	int nMoveCount;		//NPCの移動時間管理用
	NPCMODEL aModel[PARTS_NUM_NPC];
	NPC_AI npcAI;		//NPCの行動アルゴリズム
	NPC_STATE state;	//NPCの状態
	int nCntMove;		//ダメージ後の停止時間
	int nCntBullet = 0;
	D3DLIGHT9 light;		//ライトの情報

}NPC;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitNpc(void);
void UninitNpc(void);
void UpdateNpc(void);
void DrawNpc(void);
bool CollisionNpc(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);

int CollisionBullet(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax,
	int *pDeleteIdxNpc);

void SetNpcVertex(int nCntNpc);
void DeleteNpc(int nIdxNpc);

bool CountUseNpc(void);

NPC *GetNPC(void);

#endif
