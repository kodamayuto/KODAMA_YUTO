#pragma once
//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#include "Player.h"		//�v���C���[�̏���
#include "bg.h"			//�w�i�̏���
#include "enemy.h"		//�G�L�����̏���
#include "block.h"		//�u���b�N�̏���
#include "item.h"		//�A�C�e���̏���
#include "score.h"		//�X�R�A�̏���
#include "time.h"		//�������Ԃ̏���

//=============================================================================
//	�}�N����`
//=============================================================================
#define GRAVITY (0.7f)					//�d��

//=============================================================================
//	�Q�[���̏��
//=============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,	//�������ĂȂ����
	GAMESTATE_NORMAL,	//�ʏ���
	GAMESTATE_END,		//�I�����
	GAMESTATE_MAX
}GAMESTATE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(int nNumStage);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void MakeStageSet(int nNumStage);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

void PauseModeChange(void);
#endif
