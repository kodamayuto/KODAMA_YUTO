//=============================================================================
//
// 軌道の処理 [orbit.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _ORBIT_H_
#define _ORBIT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ORBIT_BLOCK      (100)
#define MAX_ORBIT        (2)

//*****************************************************************************
// 軌道の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posUp;      // 現在の座標情報
	D3DXVECTOR3 posoldUp;   // 前回の座標情報
	D3DXVECTOR3 posDown;    // 現在の座標情報
	D3DXVECTOR3 posoldDown; // 前回の座標情報
	D3DXCOLOR   colUp;      // 色(上側)
	D3DXCOLOR   colDown;    // 色(下側)
	D3DXVECTOR3 radius;     // 幅
}VerOrbit;

typedef struct
{
	D3DXVECTOR3 pos;        // 座標
	D3DXVECTOR3 rot;        // 向き
	D3DXMATRIX  mtxWorld;   // ワールドマトリックス
	VerOrbit    orbit[ORBIT_BLOCK + 1];      // 頂点情報
	float       Length;     // 長さ
	int         XBlock;     // 横の分割数
	int         YBlock;     // 縦の分割数
	int         nNumVertex; // 頂点数
	int         nNumIndex;  // インデックス数
	int         nNumPolygon;// ポリゴン数
}Orbit;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitOrbit(void);
void UninitOrbit(void);
void UpdateOrbit(void);
void DrawOrbit(void);
void SetOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, D3DXCOLOR colUp, D3DXCOLOR colDown, int nIdxOrbit);
void SetPosiotionOrbit(D3DXVECTOR3 mtx1, D3DXVECTOR3 mtx2, int nIdxOrbit);
#endif
