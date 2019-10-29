//=============================================================================
//
// �����L���O��� [ranking.h]
// Author : �������D
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MODEL	(10)		// ���f���̍ő吔

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMesh;			// ���b�V�����ւ̃|�C���^(���_���)
	LPD3DXBUFFER pBuffMat;		// �}�e���A�����ւ̃|�C���^(�F)
	DWORD nNumMat;				// �}�e���A�����̐�
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X
}RankingModel;

typedef enum
{
	RANKINGOLD_TITLE = 0,
	RANKINGOLD_SELECT,
	RANKINGOLD_MAX
} RankingOld;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRankingOld(RankingOld ranking);

#endif