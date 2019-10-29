//=============================================================================
//
// 障害物の処理 [obstacle.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	OBSTACLE_TYPE_LOG_S = 0, // 丸太(S)
	OBSTACLE_TYPE_LOG_M,	 // 丸太(M)
	OBSTACLE_TYPE_LOG_L,     // 丸太(L)
	OBSTACLE_TYPE_MOVE,
	OBSTACLE_TYPE_HALFMOVE,
	OBSTACLE_TYPE_UPDOWNLOG,
	OBSTACLE_TYPE_BASE,
	OBSTACLE_TYPE_LOGMOVE,
	OBSTACLE_TYPE_LOGFAT,
	OBSTACLE_TYPE_ROLL_LEFT,
	OBSTACLE_TYPE_ROLL_RIGHT,
	OBSTACLE_TYPE_STAIRS_S,
	OBSTACLE_TYPE_STAIRS_M,
	OBSTACLE_TYPE_STAIRS_L,
	OBSTACLE_TYPE_HALFSTAIRS_S,
	OBSTACLE_TYPE_HALFSTAIRS_M,
	OBSTACLE_TYPE_HALFSTAIRS_L,
	OBSTACLE_TYPE_MAX
}OBSTACLE_TYPE;

typedef struct
{
	D3DXMATRIX mtxWorld;    // ワールドマトリックス
	D3DXVECTOR3 pos;        // 座標
	D3DXVECTOR3 rot;        // 向き
}Vertex_Obstacle;


typedef struct
{
	D3DXVECTOR3 pos;	              // 現在の位置
	D3DXVECTOR3 posold;	              // 前回の位置
	D3DXVECTOR3 rot;	              // 向き
	D3DXVECTOR3 move;	              // 移動量
	int			nInxShadow;           // 影
	OBSTACLE_TYPE	nType;            // 種類
	D3DXMATRIX	mtxWorld;	          // ワールドマトリックス
	bool		bUse;                 // 使用しているかどうか
	D3DXVECTOR3	vtxMinObstacle, vtxMaxObstacle;	// モデルの最小値、最大値
	D3DXMATRIX  mtxWorldMaxCol;       // 当たり判定を取るワールド座標用(最大値)
	D3DXMATRIX  mtxWorldMinCol;       // 当たり判定を取るワールド座標用(最小値)
	Vertex_Obstacle Vertex[4];        // 頂点のワールドマトリックス
}OBSTACLE;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;        // 向き
	D3DXVECTOR3 move;		// 移動量
	OBSTACLE_TYPE nType;	// 種類
}OBSTACLE_INFO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitObstacle(void);
void UninitObstacle(void);
void UpdateObstacle(void);
void DrawObstacle(void);
OBSTACLE *GetObstacle(void);
void SetObstacle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, OBSTACLE_TYPE nType);
bool CollisionObstacle(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif
