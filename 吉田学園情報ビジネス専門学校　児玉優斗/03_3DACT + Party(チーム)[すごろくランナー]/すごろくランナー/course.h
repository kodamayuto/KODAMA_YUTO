//=============================================================================
//
// コースの処理 [course.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _COURSE_H_
#define _COURSE_H_

#include "main.h"

//*****************************************************************************
// ポリゴンの構造体
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;    // ワールドマトリックス
	D3DXVECTOR3 pos;        // 座標
	D3DXVECTOR3 rot;        // 向き
}Vertex_Course;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 move;			// 移動量
	float		fWidth;			// 幅
	float		fDepth;			// 奥行
	bool		bUse;			// 使用しているかどうか
	D3DXMATRIX	mtxWorldCourse; // コースのワールドマトリックス
	Vertex_Course Vertex[4];    // 頂点のワールドマトリックス
} COURSE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCourse(void);
void UninitCourse(void);
void UpdateCourse(void);
void DrawCourse(void);
void SetCourse(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth);
bool CollisionCourse(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif