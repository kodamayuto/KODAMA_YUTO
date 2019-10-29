//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
// �Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,   // �������Ă��Ȃ����
	GAMESTATE_NONE_RETRY, // �������Ă��Ȃ����(���g���C)
	GAMESTATE_NORMAL,     // �ʏ�(�v���C)���
	GAMESTATE_RETRY,      // ��蒼�����
	GAMESTATE_CLEAR,
	GAMESTATE_OVER,
	GAMESTATE_MAX
}GAMESTATE;

typedef enum
{
	TURNSTATE_NONE,				//�������
	TURNSTATE_DICE,				//�_�C�X��U��鎞��
	TURNSTATE_MAP,				//�}�b�v�m�F�̎���
	TURNSTATE_COUNTDOWN,		//�_�C�X�U���̑҂�����
	TURNSTATE_MOVEandATTACK,	//�ړ�and�W�Q���ł��鎞��
	TURNSTATE_ABILITY,			//�}�X�̔\�͑��������̎���
	TURNSTATE_END,				//�^�[���I�����A���̐l�ɑ���܂ł̎���
	TURNSTATE_MAX
}TURNSTATE;

//***************************************************************************** 
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

void SetTurnState(TURNSTATE Tstate);
TURNSTATE GetTurnState(void);

#endif