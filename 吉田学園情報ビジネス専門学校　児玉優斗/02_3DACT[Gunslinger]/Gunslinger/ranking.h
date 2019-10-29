#pragma once
//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "game.h"
//#include "score.h"
//=============================================================================
//	�}�N����`
//=============================================================================
#define	TEXTURE_RANKING_01	"data/TEXTURE/press_enter.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING_02	"data/TEXTURE/HighScore.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define MAX_RANKING_DIGIT (10)									//����
#define MAX_RANKING_TEXTURE (2)
#define RANKING_SIZE      (30.0f)								//�X�R�A�̑傫��

#define RANKING_POS_X (400)									//�X�R�A��X��
#define RANKING_POS_Y (370)									//�X�R�A��Y��

//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);

void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);
void SetRankScore(int nScore);
#endif
