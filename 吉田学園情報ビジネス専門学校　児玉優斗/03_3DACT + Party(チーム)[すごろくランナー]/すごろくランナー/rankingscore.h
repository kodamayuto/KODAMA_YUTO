//=============================================================================
//
// �����L���O�X�R�A���� [rankingscore.h]
// Author : �������D
// Editor : Yuto Kodama
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"

//
//
//

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int g_aRankingscore;
	D3DXMATRIX g_aRankingMatrix;
}Ranking;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRankingscore(void);
void UninitRankingscore(void);
void UpdateRankingscore(void);
void DrawRankingscore(void);

void SetHighScore(int nScore);

void SetDrawScore(int nNumScore);
#endif
